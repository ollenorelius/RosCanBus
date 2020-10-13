#pragma once

#include "../EventSignal.hpp"
#include <memory>

class CanSignalModel
{
public:
    CanSignalModel();

    void setValue(double value);

    double getValue();
    EventSignal* getValueChanged();

private:
    double value_;
    long timestamp_;

    std::unique_ptr<EventSignal> valueChanged_;
};