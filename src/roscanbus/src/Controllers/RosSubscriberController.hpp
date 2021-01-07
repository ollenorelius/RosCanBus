#pragma once
#include <memory>
#include "../Interfaces/RosSignalSubscriber.hpp"
#include <map>
#include "../CanDB/SignalDefinition.hpp"

class RosNodeModel;
class CanSignalCollectionModel;

class RosSubscriberController
{
public:
    RosSubscriberController(CanSignalCollectionModel* canSignalCollectionModel,
                         RosNodeModel* rosNodeModel,
                         std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel);
private:
    std::vector<std::unique_ptr<RosSignalSubscriber>> signalSubscribers_;
};