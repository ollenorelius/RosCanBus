#pragma once

#include <memory>
#include <map>

#include "../CanDB/Frame.hpp"
#include "../Models/CanPublishTimerModel.hpp"

class CanFrameEmitTimerModel
{
public:
    CanFrameEmitTimerModel(std::map<int, Frame>* frameDefinitions);
    
    void updateFrameTimer(const int & frameId);
    bool isFrameReadyToSend(const int & frameId) const;

private:
    //frame id, timer since last message was sent out
    std::map<int, std::unique_ptr<CanPublishTimerModel>> frameTimers_;
    std::map<int, Frame>* frameDefinitions_;        
};