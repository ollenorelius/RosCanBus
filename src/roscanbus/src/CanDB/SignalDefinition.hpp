#pragma once

#include "../Enumerators.hpp"
#include <string>

class SignalDefinition
{
public:
    SignalDefinition(SIGNAL_TYPE signalType,
                          int length,
                          double scaler,
                          double offset,
                          std::string unit,
                          std::string name,
                          std::string description);

    SIGNAL_TYPE getSignalType();
    int getLength();
    double getScaler();
    double getOffset();
    std::string getUnit();
    std::string getName();
    std::string getDescription();

private:
    SIGNAL_TYPE signalType_;
    int length_;
    double scaler_;
    double offset_;
    std::string unit_;
    std::string name_;
    std::string description_;
};