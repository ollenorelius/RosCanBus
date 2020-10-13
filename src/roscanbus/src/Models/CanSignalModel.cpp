#include "CanSignalModel.hpp"

CanSignalModel::CanSignalModel(double value, CanSignalDirection direction) :
    value_(0),
    timestamp_(0),
    valueChanged_(std::make_unique<EventSignal>()),
    canSignalDirection_(direction)

{
    
}

void CanSignalModel::setValue(double value) 
{
    if (value != value_)
    {
        value_ = value;
        valueChanged_->emit();
    }
}

double CanSignalModel::getValue() 
{
    return value_;
}

EventSignal* CanSignalModel::getValueChanged() 
{
    return valueChanged_.get();
}

CanSignalDirection CanSignalModel::getCanSignalDirection() 
{
    return canSignalDirection_;
}
