#include "Frame.hpp"

std::string Frame::getName() 
{
    return name_;
}

int Frame::getFrameId() 
{
    return frameId_;
}

double Frame::getPeriod() 
{
    return period_;
}

std::vector<int>* Frame::getSignals() 
{
    return &signals_;
}

std::string Frame::getDescription() 
{
    return description_;
}

Frame::Frame(std::string name,
               int frameId,
               std::vector<int> signals,
               double period,
               std::string description) :
    name_(name),
    frameId_(frameId),
    signals_(signals),
    period_(period),
    description_(description)
{
    
}
