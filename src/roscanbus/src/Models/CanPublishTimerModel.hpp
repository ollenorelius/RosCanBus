#pragma once

#include <memory>
#include <chrono>

#include "../EventSignal.hpp"

class CanPublishTimerModel
{
public:
    CanPublishTimerModel();

    void setCurrentTime();   
    double compare(std::chrono::time_point<std::chrono::system_clock> & otherTime);

private:   

    std::chrono::time_point<std::chrono::system_clock> timeNow_;
    std::unique_ptr<EventSignal> valueChanged_;
};