#include "CanGwModel.hpp"
#include "CanDB/FrameReader.hpp"
#include "CanDB/SignalReader.hpp"

CanGwModel::CanGwModel(int argc, char** argv, std::string dbFileName, std::string nodeName) 
  
{
    CanGwModel(dbFileName, nodeName);
    rosNodeModel_ = std::make_unique<RosNodeModel>(argc, argv);
    commandLineModel_ = std::make_unique<CommandLineModel>(argc, argv);
}

CanSignalCollectionModel* CanGwModel::getCanSignalCollectionModel() 
{
    return canSignalCollectionModel_.get();
}

std::map<int, Frame>* CanGwModel::getRxCanFramesCollectionModel() 
{
    return rxCanFramesCollectionModel_.get();    
}

std::map<int, Frame>* CanGwModel::getTxCanFramesCollectionModel() 
{
    return txCanFramesCollectionModel_.get();
}

std::map<int, SignalDefinition>* CanGwModel::getCanSignalDefinitionCollectionModel() 
{
    return canSignalDefinitionCollectionModel_.get();
}

CommandLineModel* CanGwModel::getCommandLineModel() 
{
    return commandLineModel_.get();
}

RosNodeModel* CanGwModel::getRosNodeModel() 
{
    return rosNodeModel_.get();
}

CanFrameEmitTimerModel* CanGwModel::getCanFrameEmitTimerModel()
{
    return canFrameEmitTimerModel_.get();
}

DummyTickModel* CanGwModel::getDummyTickModel()
{
    return dummyTickModel_.get();
}

CanGwModel::CanGwModel(std::string dbFileName, std::string nodeName) 
{
    FrameReader FrameReader(dbFileName);
    txCanFramesCollectionModel_ = std::move(FrameReader.getTxFrames(nodeName));
    rxCanFramesCollectionModel_ = std::move(FrameReader.getRxFrames(nodeName));

    SignalReader signalReader(dbFileName);
    canSignalDefinitionCollectionModel_ = std::move(signalReader.getSignalDefinitions());

    commandLineModel_ = std::make_unique<CommandLineModel>(0, nullptr);

    canFrameEmitTimerModel_ = std::make_unique<CanFrameEmitTimerModel> (this->getTxCanFramesCollectionModel());
    dummyTickModel_ = std::make_unique<DummyTickModel>();
    canSignalCollectionModel_ = signalReader.createCanSignalCollectionModel();
}

