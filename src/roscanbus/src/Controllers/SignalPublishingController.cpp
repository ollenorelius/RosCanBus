#include "SignalPublishingController.hpp"
#include "../Models/CanSignalCollectionModel.hpp"
#include "../Models/RosNodeModel.hpp"
#include "../Interfaces/RosSignalPublisher.hpp"
#include "../CanDB/SignalDefinition.hpp"


SignalPublishingController::SignalPublishingController(CanSignalCollectionModel* canSignalCollectionModel,
                                                       RosNodeModel* rosNodeModel,
                                                       std::map<int, SignalDefinition>* canSignalDefinitionModel) :
    canSignalCollectionModel_(canSignalCollectionModel),
    rosNodeModel_(rosNodeModel),
    canSignalDefinitionModel_(canSignalDefinitionModel)
{

    auto txSignals = canSignalCollectionModel_->getRxSignals();

    for (auto& signal : txSignals)
    {
        RosSignalPublisher* signalPublisher = new RosSignalPublisher(signal,
                                                                     rosNodeModel_,
                                                                     canSignalDefinitionModel_);
        signalPublishers_.push_back(signalPublisher);
    }
}
