#pragma once

#include <vector>
#include <chrono>

#include "../Interfaces/CAN.hpp"
#include "../Interfaces/FrameData.hpp"
#include "../Models/CanPublishTimerModel.hpp"

typedef std::vector<FrameData> CanSignalList;

class CanTransmitterController
{
    
public:
    CanTransmitterController( Interfaces::CAN* canInterface,
                              CanSignalList* canSignalList, 
                              CanPublishTimerModel* canPublishTimerModel);

void updateAndPublish();

private:
    Interfaces::CAN*        canInterface_;
    CanSignalList*          canSignalList_;
    CanPublishTimerModel*   canPublishTimerModel_;
};