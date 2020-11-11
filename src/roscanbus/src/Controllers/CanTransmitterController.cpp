#include "CanTransmitterController.hpp"

CanTransmitterController::CanTransmitterController( CanSignalList* canSignalList, 
                                                    CanPublishTimerModel* canPublishTimerModel) : 
    canSignalList_(canSignalList),
    canPublishTimerModel_(canPublishTimerModel)
{

}

void CanTransmitterController::updateAndPublish()
{
    const unsigned publishInterval = .005; 
    if( canSignalList_->empty() ) return;
    
    FrameData dataPackage = canSignalList_->at(0);
    //collect data information

    //send it
    Interfaces::CAN::writeCanFrame(dataPackage);

    //erase it from list
    //signalList->erase(signalList->at(0));

    //update timer    
}