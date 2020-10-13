#pragma once

#include <memory>
#include <vector>
#include <map>
#include "CanSignalModel.hpp"
#include "../EventSignal.hpp"


class CanSignalCollectionModel
{
    public:
    CanSignalCollectionModel();

    CanSignalModel* getCanSignal(int signalId);
    void setCanSignalValue(int signalId, double value);
    void addCanSignal(int signalId, CanSignalDirection direction);

    std::vector<CanSignalModel*> getTxSignals();
    std::vector<CanSignalModel*> getRxSignals();

    EventSignal* getSignalAddedEvent();
    CanSignalModel* getLastSignalAdded();

private:
    std::map<int, std::unique_ptr<CanSignalModel>> canSignals_;
    std::unique_ptr<EventSignal> signalAdded_;
    CanSignalModel* lastSignalAdded_;
};