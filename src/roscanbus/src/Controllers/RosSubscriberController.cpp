#include "RosSubscriberController.hpp"
#include "../Models/RosNodeModel.hpp"
#include "../Models/CanSignalCollectionModel.hpp"

RosSubscriberController::RosSubscriberController(CanSignalCollectionModel* canSignalCollectionModel,
                         RosNodeModel* rosNodeModel,
                         std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel)
{
    for (auto& signal : canSignalCollectionModel->getTxSignals())
    {
        signalSubscribers_.push_back(std::make_unique<RosSignalSubscriber>(signal, rosNodeModel, canSignalDefinitionCollectionModel));
    }
}