#include "EventSignal.hpp"

EventSignal::EventSignal() 
{
    
}

void EventSignal::connect(std::function<void()> callback) 
{
    receivers_.push_back(callback);
}

void EventSignal::emit() 
{
    for (auto callback : receivers_)
    {
        callback();
    }
}
