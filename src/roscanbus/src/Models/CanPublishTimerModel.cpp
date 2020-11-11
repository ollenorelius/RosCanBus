#include "CanPublishTimerModel.hpp"

CanPublishTimerModel::CanPublishTimerModel() : 
    timeNow_(std::chrono::system_clock::now()),     
    valueChanged_(std::make_unique<EventSignal>())
{

}

void CanPublishTimerModel::setCurrentTime()
{   
    timeNow_ = std::chrono::system_clock::now();
}

double CanPublishTimerModel::compare(std::chrono::time_point<std::chrono::system_clock> & otherTime)
{
    return std::chrono::duration<double> (otherTime - timeNow_).count();
}
