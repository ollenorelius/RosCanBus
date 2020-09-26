#include "CanSignalCollectionModel.hpp"

CanSignalCollectionModel::CanSignalCollectionModel() 
{
}

CanSignalCollectionModel::CanSignalCollectionModel(std::vector<int> signalIds) 
{
}

CanSignal* CanSignalCollectionModel::getCanSignal(int signalId) 
{
    return canSignals_.at(signalId).get();
}

void CanSignalCollectionModel::setCanSignal(int signalId, std::unique_ptr<CanSignal> signal) 
{
    canSignals_[signalId] = std::move(signal);
}

