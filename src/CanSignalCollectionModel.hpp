#pragma once

#include <memory>
#include <vector>
#include <map>
#include "CanSignal.hpp"


class CanSignalCollectionModel
{
    public:
    CanSignalCollectionModel() {};
    CanSignalCollectionModel(std::unique_ptr<std::map<int, CanSignal>> canSignalMap);
    CanSignalCollectionModel(int signalCount);
    CanSignalCollectionModel(std::vector<int> signalIds);
    double getCanSignal(int signalId);
    void setCanSignal(int signalId, std::unique_ptr<CanSignal> signal);

private:
    std::unique_ptr<std::map<int, double>> canSignals_;
};