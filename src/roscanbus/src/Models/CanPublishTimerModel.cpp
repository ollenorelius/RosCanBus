#include "CanPublishTimerModel.hpp"

CanPublishTimerModel::CanPublishTimerModel() : 
    timeNow_(std::chrono::system_clock::now()),     
    valueChanged_(std::make_unique<EventSignal>())
{

}

void CanPublishTimerModel::setCurrentTime()
{
    auto t = std::chrono::system_clock::now();
    //dt_ = std::chrono::duration<double> (t - timeNow_).count();
    timeNow_ = t;
}
