#include "CanFrameEmitTimerModel.hpp"

#include <chrono>

CanFrameEmitTimerModel::CanFrameEmitTimerModel(std::map<int, Frame>* frameDefinitions) : 
    frameDefinitions_(frameDefinitions)
{
    for(const auto & fd : *frameDefinitions) frameTimers_[fd.first] = std::make_unique<CanPublishTimerModel>();
}

void CanFrameEmitTimerModel::updateFrameTimer(const int & frameId)
{
    frameTimers_.at(frameId)->setCurrentTime();
}

bool  CanFrameEmitTimerModel::isFrameReadyToSend(const int & frameId) const
{
    float framePeriod = frameDefinitions_->at(frameId).getPeriod();   

    auto t = std::chrono::system_clock::now();

    return frameTimers_.at(frameId)->compare(t) > framePeriod;
}