#pragma once

#include <memory>
#include <map>

#include "CanDB/Frame.hpp"
#include "CanDB/SignalDefinition.hpp"
#include "Models/CommandLineModel.hpp"
#include "Models/CanSignalModel.hpp"
#include "Models/CanSignalCollectionModel.hpp"


class CanGwModel
{
public:
    CanGwModel();
    CanGwModel(int argc, char** argv);
    ~CanGwModel() {};
    CanSignalCollectionModel* getCanSignalCollectionModel();
    std::map<int, Frame>* getRxCanFramesCollectionModel();
    std::map<int, Frame>* getTxCanFramesCollectionModel();
    std::map<int, SignalDefinition>* getCanSignalDefinitionCollectionModel();
    CommandLineModel* getCommandLineModel();

private:
    std::unique_ptr<CanSignalCollectionModel> canSignalCollectionModel_;
    std::unique_ptr<std::map<int, Frame>> rxCanFramesCollectionModel_;
    std::unique_ptr<std::map<int, Frame>> txCanFramesCollectionModel_;
    std::unique_ptr<std::map<int, SignalDefinition>> canSignalDefinitionCollectionModel_;
    std::unique_ptr<CommandLineModel> commandLineModel_;

};
