#include "CanSignalCollectionModel.hpp"
#include "CanSignalModel.hpp"

CanSignalCollectionModel::CanSignalCollectionModel() 
{
}

CanSignalModel* CanSignalCollectionModel::getCanSignal(int signalId) 
{
    return canSignals_.at(signalId).get();
}

void CanSignalCollectionModel::setCanSignalValue(int signalId, double value) 
{
    canSignals_.at(signalId)->setValue(value);
}


void CanSignalCollectionModel::addCanSignal(int signalId, CanSignalDirection direction) 
{
    CanSignalModel* canSignalModel = new CanSignalModel(0, direction);
    canSignals_[signalId] = std::unique_ptr<CanSignalModel>(canSignalModel);
}


