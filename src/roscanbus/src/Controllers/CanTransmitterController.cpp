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
    std::vector<CanSignalModel*> txCanSignalVector = canSignalCollectionModel_->getTxSignals();
    
    //nothing to send?
    if(txCanSignalVector.empty()) return;

    auto signal = txCanSignalVector.at(0);
    auto signalId = signal->getIndex();    
    
    for(auto & frame : *txCanFramesCollectionModel_) 
    { 
        //are we ready to send this frameId?  
        int frameId = frame.first;
        
        if(!canFrameEmitTimerModel_->isFrameReadyToSend(frameId)) continue;      
                
        //collect the signal connected to it
        std::vector<int>* signalValueIds = frame.second.getSignals();
                
        FrameData fd;
        int step = 0;
        fd.id = frameId; 
        fd.dlc = 0;
        
        uint64_t data_64 = 0;        
        unionCanData ucd;

        for(const auto & signalId : *signalValueIds) 
        {   
            auto signal = canSignalCollectionModel_->getCanSignal(signalId);          
            double signalValue = signal->getValue();
           
            //put it in correct place in framedata                        
            SignalDefinition signalDefinition = canSignalDefinitionCollectionModel_->at(signalId);    
            
            fd.dlc += signalDefinition.getLength();
            
            int signalLength = signalDefinition.getLength();
          
            uint64_t sv_64 = static_cast<uint64_t>(signalValue);
            data_64 |= SignalDecoder::two_complement(sv_64, signalLength) << step;
            step += signalLength;
        }
        //set datalength of full message in bytes, transfer data to framedata.data, send to canbus
        fd.dlc = ceil(fd.dlc/8.0);
        ucd.intcandata = data_64;
        memcpy(fd.data, ucd.candata, fd.dlc);
     
        canInterface_->writeCanFrame(fd);

        //update frame timer model
        canFrameEmitTimerModel_->updateFrameTimer(frameId);
    }  
    
}