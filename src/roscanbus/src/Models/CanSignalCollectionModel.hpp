#pragma once

#include <memory>
#include <vector>
#include <map>
#include "CanSignalModel.hpp"


class CanSignalCollectionModel
{
    public:
    CanSignalCollectionModel();

    CanSignalModel* getCanSignal(int signalId);
    void setCanSignalValue(int signalId, double value);
    void addCanSignal(int signalId, CanSignalDirection direction);

    std::vector<CanSignalModel*> getTxSignals();
    std::vector<CanSignalModel*> getRxSignals();

private:
    std::map<int, std::unique_ptr<CanSignalModel>> canSignals_;
};