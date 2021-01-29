#include "Frame.hpp"

std::string Frame::getName() const
{
    return name_;
}

int Frame::getFrameId() const
{
    return frameId_;
}

double Frame::getPeriod() const
{
    return period_;
}

const std::vector<int>* Frame::getSignals() const
{
    return &signals_;
}

std::string Frame::getDescription() const
{
    return description_;
}

int Frame::getDlc() const
{
    return dlc_;
}
void Frame::setDlc(int dlc)
{
    dlc_ = dlc;
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
    description_(description),
    dlc_(0)
{
    
}

Frame::Frame() 
{
    
}
