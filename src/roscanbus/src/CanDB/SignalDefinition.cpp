#include "SignalDefinition.hpp"

SignalDefinition::SignalDefinition(SIGNAL_TYPE signalType,
                          int length,
                          double scaler,
                          double offset,
                          std::string unit,
                          std::string name,
                          std::string description,
                          std::string source) :
    signalType_(signalType),
    length_(length),
    scaler_(scaler),
    offset_(offset),
    unit_(unit),
    name_(name),
    description_(description),
    source_(source)
{

}

SIGNAL_TYPE SignalDefinition::getSignalType() 
{
    return signalType_;
}

int SignalDefinition::getLength() 
{
    return length_;    
}

double SignalDefinition::getScaler() 
{
    return scaler_;    
}

double SignalDefinition::getOffset() 
{
    return offset_;
}

std::string SignalDefinition::getUnit() 
{
    return unit_;
}

std::string SignalDefinition::getName() 
{
    return name_;
}

std::string SignalDefinition::getDescription() 
{
    return description_;
}

std::string SignalDefinition::getSource()
{
    return source_;
}

