#pragma once

#include <memory>
#include <map>
#include <string>

#include "CanDB/Frame.hpp"
#include "CanDB/SignalDefinition.hpp"
#include "Models/CommandLineModel.hpp"
#include "Models/CanSignalModel.hpp"
#include "Models/CanSignalCollectionModel.hpp"
#include "Models/RosNodeModel.hpp"
#include "Models/CanPublishTimerModel.hpp"
#include "Models/CanFrameEmitTimerModel.hpp"
#include "Models/DummyTickModel.hpp"

class CanGwModel
{
public:
    CanGwModel(std::string dbFileName, std::string nodeName);
    CanGwModel(int argc, char** argv, std::string dbFileName, std::string nodeName);
    ~CanGwModel() {};
    CanSignalCollectionModel* getCanSignalCollectionModel();
    std::map<int, Frame>* getRxCanFramesCollectionModel();
    std::map<int, Frame>* getTxCanFramesCollectionModel();
    std::map<int, SignalDefinition>* getCanSignalDefinitionCollectionModel();
    CommandLineModel* getCommandLineModel();
    RosNodeModel* getRosNodeModel();
    CanFrameEmitTimerModel* getCanFrameEmitTimerModel();
    DummyTickModel* getDummyTickModel();
    
private:
    std::unique_ptr<CanSignalCollectionModel> canSignalCollectionModel_;
    std::unique_ptr<std::map<int, Frame>> rxCanFramesCollectionModel_;
    std::unique_ptr<std::map<int, Frame>> txCanFramesCollectionModel_;
    std::unique_ptr<std::map<int, SignalDefinition>> canSignalDefinitionCollectionModel_;
    std::unique_ptr<CommandLineModel> commandLineModel_;
    std::unique_ptr<RosNodeModel> rosNodeModel_; 
    std::unique_ptr<CanFrameEmitTimerModel> canFrameEmitTimerModel_;
    std::unique_ptr<DummyTickModel> dummyTickModel_;
    
};
