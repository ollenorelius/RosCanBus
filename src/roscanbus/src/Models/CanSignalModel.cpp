#include "CanSignalModel.hpp"

CanSignalModel::CanSignalModel(int index, double value, CanSignalDirection direction) :
    value_(0),
    index_(index),
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

int CanSignalModel::getIndex() 
{
    return index_;
}

EventSignal* CanSignalModel::getValueChanged() 
{
    return valueChanged_.get();
}

CanSignalDirection CanSignalModel::getCanSignalDirection() 
{
    return canSignalDirection_;
}
