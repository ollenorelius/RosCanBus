#include "CanTransmitterController.hpp"

#include <iostream>
#include <chrono>
#include <cassert>

#include "../Interfaces/CAN.hpp"
#include "../Interfaces/FrameData.hpp"
#include "../Models/CanPublishTimerModel.hpp"
#include "../Models/CanSignalCollectionModel.hpp"
#include "../Models/CanFrameEmitTimerModel.hpp"

CanTransmitterController::CanTransmitterController( Interfaces::CAN* canInterface,
                                                    CanSignalCollectionModel* canSignalCollectionModel,                                                 
                                                    std::map<int, Frame>* txCanFramesCollectionModel,
                                                    CanFrameEmitTimerModel* canFrameEmitTimerModel,
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
        for(const auto & signalId : *signalValueIds) 
        {
            std::cout << "sending frame id : " << frameId << " with signals " << signalId <<  std::endl;

            auto s = canSignalCollectionModel_->getCanSignal(signalId);          
   
            //put it in correct place in framedata                        
            SignalDefinition signalDefinition = canSignalDefinitionCollectionModel_->at(signalId);

            switch(signalDefinition.getSignalType())
            {
                case SIGNAL_TYPE::UNSIGNED : fd.data[step++] = static_cast<uint64_t>(s->getValue());break;
                case SIGNAL_TYPE::SIGNED :   fd.data[step++] = static_cast<int64_t>(s->getValue());break;
                case SIGNAL_TYPE::FLOAT :    fd.data[step++] = static_cast<float>(s->getValue());break;
                case SIGNAL_TYPE::BOOL :     fd.data[step++] = static_cast<bool>(s->getValue());break;
            }
        }

        //send to canbus
        canInterface_->writeCanFrame(fd);

        //update frame timer model
        canFrameEmitTimerModel_->updateFrameTimer(frameId);
    }  
    
}