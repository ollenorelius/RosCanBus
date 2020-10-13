#pragma once

#include "../EventSignal.hpp"
#include <memory>

enum class CanSignalDirection
{
    TX,
    RX
};

class CanSignalModel
{
public:
    CanSignalModel(int index, double value, CanSignalDirection direction);

    void setValue(double value);
    void setCanSignalDirection(CanSignalDirection canSignalDirection);

    double getValue();
    int getIndex();
    EventSignal* getValueChanged();
    CanSignalDirection getCanSignalDirection();



private:
    double value_;
    int index_;
    long timestamp_;
    CanSignalDirection canSignalDirection_;

    std::unique_ptr<EventSignal> valueChanged_;
};