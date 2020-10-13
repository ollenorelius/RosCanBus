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
    CanSignalModel* canSignalModel = new CanSignalModel(signalId, 0, direction);
    canSignals_[signalId] = std::unique_ptr<CanSignalModel>(canSignalModel);
    lastSignalAdded_ = canSignals_[signalId].get();
}

std::vector<CanSignalModel*> CanSignalCollectionModel::getTxSignals() 
{
    std::vector<CanSignalModel*> txSignals;

    for (const auto& pair : canSignals_)
    {
        if (pair.second->getCanSignalDirection() == CanSignalDirection::TX)
        {
            txSignals.push_back(pair.second.get());
        }
    }
    return txSignals;
}

std::vector<CanSignalModel*> CanSignalCollectionModel::getRxSignals() 
{
    std::vector<CanSignalModel*> rxSignals;

    for (const auto& pair : canSignals_)
    {
        if (pair.second->getCanSignalDirection() == CanSignalDirection::RX)
        {
            rxSignals.push_back(pair.second.get());
        }
    }
    return rxSignals;
}

EventSignal* CanSignalCollectionModel::getSignalAddedEvent() 
{
    return signalAdded_.get();
}

CanSignalModel* CanSignalCollectionModel::getLastSignalAdded() 
{
    return lastSignalAdded_;
}


