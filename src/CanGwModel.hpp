#pragma once

#include <memory>
#include <map>

#include "CanDB/Frame.hpp"
#include "CanDB/SignalDefinition.hpp"
#include "CommandLineModel.hpp"
#include "CanSignalModel.hpp"


class CanGwModel
{
public:
    CanGwModel();
    CanGwModel(int argc, char** argv);
    ~CanGwModel() {};
    std::map<int, CanSignalModel*>* getCanSignalCollectionModel();
    std::map<int, Frame>* getRxCanFramesCollectionModel();
    std::map<int, Frame>* getTxCanFramesCollectionModel();
    std::map<int, SignalDefinition>* getCanSignalDefinitionCollectionModel();
    CommandLineModel* getCommandLineModel();

private:
    std::unique_ptr<std::map<int, std::unique_ptr<CanSignalModel>>> canSignalCollectionModel_;
    std::unique_ptr<std::map<int, Frame>> rxCanFramesCollectionModel_;
    std::unique_ptr<std::map<int, Frame>> txCanFramesCollectionModel_;
    std::unique_ptr<std::map<int, SignalDefinition>> canSignalDefinitionCollectionModel_;
    std::unique_ptr<CommandLineModel> commandLineModel_;

};
