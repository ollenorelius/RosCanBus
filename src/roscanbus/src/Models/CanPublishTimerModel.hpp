#pragma once

#include <memory>
#include <chrono>

#include "../EventSignal.hpp"

class CanPublishTimerModel
{
public:
    CanPublishTimerModel();
    void setCurrentTime();    

private:    
    //std::chrono::milliseconds dt_;
    std::chrono::time_point<std::chrono::system_clock> timeNow_;
    std::unique_ptr<EventSignal> valueChanged_;
};