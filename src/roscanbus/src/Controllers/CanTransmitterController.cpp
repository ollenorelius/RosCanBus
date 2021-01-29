#include "CanTransmitterController.hpp"

#include <iostream>
#include <chrono>
#include <cassert>
#include <math.h>       /* ceil */
#include <stdio.h>
#include <string.h>

#include "../Interfaces/CAN.hpp"
#include "../Interfaces/FrameData.hpp"
#include "../Models/CanPublishTimerModel.hpp"
#include "../Models/CanSignalCollectionModel.hpp"
#include "../Models/CanFrameEmitTimerModel.hpp"
#include "../CanDB/SignalDecoder.hpp"


//signal values are shifted into a uint64_t and memcpied over to a char[8] to be transmitted on the canbus
struct unionCanData
{
    union 
    {
        char candata[8];
        uint64_t intcandata;
    };

};

CanTransmitterController::CanTransmitterController( Interfaces::CAN* canInterface,
                                                    CanSignalCollectionModel* canSignalCollectionModel,                                                 
                                                    std::map<int, Frame>* txCanFramesCollectionModel,  
                                                    CanFrameEmitTimerModel*     canFrameEmitTimerModel,                                                 
                                                    std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel,
                                                    DummyTickModel* dummyTickModel
                                                    ) : 
    canInterface_(canInterface),
    canSignalCollectionModel_(canSignalCollectionModel),
    txCanFramesCollectionModel_(txCanFramesCollectionModel),    
    canFrameEmitTimerModel_(canFrameEmitTimerModel),
    canSignalDefinitionCollectionModel_(canSignalDefinitionCollectionModel)
{   
    auto updateCallback = [this] ()
    {
        this->send();
    }; 
    
    dummyTickModel->getSignal()->connect(updateCallback);
}

void CanTransmitterController::send()
{     
    
    for(auto & frame : *txCanFramesCollectionModel_) 
    { 
        //are we ready to send this frameId?  
        int frameId = frame.first;
        if(!canFrameEmitTimerModel_->isFrameReadyToSend(frameId)) continue;      
                
        FrameData fd;
        fd.id = frameId; 
        fd.dlc = getDLC(frame.second);
        
        unionCanData ucd;
        ucd.intcandata = packFrameData(frame.second);
        memcpy(fd.data, ucd.candata, fd.dlc);
     
        canInterface_->writeCanFrame(fd);

        //update frame timer model
        canFrameEmitTimerModel_->updateFrameTimer(frameId);
    }  
}

uint64_t CanTransmitterController::packFrameData(const Frame& frame)
{
        int step = 0;
        const std::vector<int>* signalIds = frame.getSignals();
        SignalDecoder signalDecoder;
        for(const auto & signalId : *signalIds) 
        {   
            SignalDefinition signalDefinition = canSignalDefinitionCollectionModel_->at(signalId);    
            
            SignalDecoder::signal s;
            s.start_bit = step;
            s.len = signalDefinition.getLength();
            s.byte_order = SignalDecoder::INTEL;

            if (signalDefinition.getSignalType() == SIGNAL_TYPE::SIGNED)
            {
                auto signal = canSignalCollectionModel_->getCanSignal(signalId);          
                int64_t signalValue = static_cast<int64_t>((signal->getValue() + signalDefinition.getOffset()) / signalDefinition.getScaler());
                signalDecoder.set_signal(&s, signalValue);
            }
            else if (signalDefinition.getSignalType() == SIGNAL_TYPE::UNSIGNED)
            {
                auto signal = canSignalCollectionModel_->getCanSignal(signalId);          
                uint64_t signalValue = static_cast<uint64_t>((signal->getValue() + signalDefinition.getOffset()) / signalDefinition.getScaler());
                signalDecoder.set_signal(&s, signalValue);
            }
            step += s.len;
        }
        return signalDecoder.data_single;
}

int CanTransmitterController::getDLC(const Frame& frame) 
{
    int bits_DLC = 0;
    const std::vector<int>* signalIds = frame.getSignals();
    for (int signalID : *signalIds)
    {
        SignalDefinition sd = canSignalDefinitionCollectionModel_->at(signalID);
        bits_DLC += sd.getLength();
    }
    return ceil(bits_DLC/8.0);
}



