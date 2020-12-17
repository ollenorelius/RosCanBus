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
    //assert(txCanFramesCollectionModel_.find(subSignalId_) != txCanFramesCollectionModel_.end() && "not a valid transmission frame");   

    auto updateAndPublishCallback = [this] ()
    {
        this->updateAndPublish();
    }; 
    
    dummyTickModel->getSignal()->connect(updateAndPublishCallback);
}

//split this up into better method names and filling value from signalValues
void CanTransmitterController::updateAndPublish()
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
        std::vector<int> slengths;
        unionCanData ucd;


        for(const auto & signalId : *signalValueIds) 
        {
            std::cout << "sending frame id : " << frameId << " with signals " << signalId <<  std::endl;                                  
            
            auto signal = canSignalCollectionModel_->getCanSignal(signalId);          
            double signalValue = signal->getValue();
           
            //put it in correct place in framedata                        
            SignalDefinition signalDefinition = canSignalDefinitionCollectionModel_->at(signalId);    
            
            fd.dlc += signalDefinition.getLength();
            
            int signalLength = signalDefinition.getLength();
            slengths.emplace_back(signalLength);
            uint64_t sv_64 = static_cast<uint64_t>(signalValue);

            data_64 |= SignalDecoder::two_complement(sv_64, signalLength) << step;
            step += signalLength;
            //std::cout << sv_64 << " in pos " << step << std::endl;

        }
        //send to canbus
        fd.dlc = ceil(fd.dlc/8.0);

        int step0 = 0;
   
        //*fd.data = data_64;
        //*fd.data = 0x000A000B;
        
               
        
        ucd.intcandata = data_64;
        memcpy(fd.data, ucd.candata, fd.dlc);
        
        


        // for(int i = 0; i < 8; ++i)
        // {
        //     std::cout << (int)fd.data[i] << std::endl;
        // }

        // *fd.data = data_64;
     
        canInterface_->writeCanFrame(fd);

        //update frame timer model
        canFrameEmitTimerModel_->updateFrameTimer(frameId);
    }  
    
}