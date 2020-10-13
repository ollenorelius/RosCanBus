#pragma once 

#include <vector>
#include <map>

class CanSignalCollectionModel;
class RosNodeModel;
class SignalDefinition;
class RosSignalPublisher;

class SignalPublishingController
{
    public:
    SignalPublishingController(CanSignalCollectionModel* canSignalCollectionModel,
                               RosNodeModel* rosNodeModel,
                               std::map<int, SignalDefinition>* canSignalDefinitionModel);

    private:

    CanSignalCollectionModel* canSignalCollectionModel_;
    RosNodeModel* rosNodeModel_;
    std::vector<RosSignalPublisher*> signalPublishers_;
    std::map<int, SignalDefinition>* canSignalDefinitionModel_;

};