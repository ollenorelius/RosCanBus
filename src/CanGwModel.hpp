#pragma once

#include <memory>
#include <map>

#include "CanDB/Frame.hpp"
#include "CanDB/SignalDefinition.hpp"

class CanGwModel
{
public:
    CanGwModel();
    ~CanGwModel() {};
    std::map<int, double>* getCanSignalCollectionModel();
    std::map<int, Frame>* getRxCanFramesCollectionModel();
    std::map<int, Frame>* getTxCanFramesCollectionModel();
    std::map<int, SignalDefinition>* getCanSignalDefinitionCollectionModel();

private:
    std::unique_ptr<std::map<int, double>> canSignalCollectionModel_;
    std::unique_ptr<std::map<int, Frame>> rxCanFramesCollectionModel_;
    std::unique_ptr<std::map<int, Frame>> txCanFramesCollectionModel_;
    std::unique_ptr<std::map<int, SignalDefinition>> canSignalDefinitionCollectionModel_;

};
