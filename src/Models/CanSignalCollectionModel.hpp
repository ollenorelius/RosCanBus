#pragma once

#include <memory>
#include <vector>
#include <map>
#include "CanSignalModel.hpp"


class CanSignalCollectionModel
{
    public:
    CanSignalCollectionModel() {};
    CanSignalCollectionModel(std::unique_ptr<std::map<int, CanSignalModel>> canSignalMap);
    CanSignalCollectionModel(int signalCount);
    CanSignalCollectionModel(std::vector<int> signalIds);
    double getCanSignal(int signalId);
    void setCanSignal(int signalId, std::unique_ptr<CanSignalModel> signal);

private:
    std::unique_ptr<std::map<int, CanSignalModel>> canSignals_;
};