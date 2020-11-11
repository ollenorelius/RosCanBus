#include "CanTransmitterController.hpp"

#include <iostream>

CanTransmitterController::CanTransmitterController( Interfaces::CAN* canInterface,
                                                    CanSignalList* canSignalList, 
                                                    CanPublishTimerModel* canPublishTimerModel) : 
    canInterface_(canInterface),
    canSignalList_(canSignalList),
    canPublishTimerModel_(canPublishTimerModel)
{

}

void CanTransmitterController::updateAndPublish()
{
    const float publishInterval = .005;
    auto timeStamp = std::chrono::system_clock::now();

    if( canSignalList_->empty() || canPublishTimerModel_->compare(timeStamp) < publishInterval) return;    
       
    FrameData dataPackage = canSignalList_->at(0);
    //collect data information

    //send it
    canInterface_->writeCanFrame(dataPackage);

    //erase it from list
    //

    //update timer 
    canPublishTimerModel_->setCurrentTime();   
}