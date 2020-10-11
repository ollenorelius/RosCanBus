#include "CanGwModel.hpp"
#include "CanDB/FrameReader.hpp"
#include "CanDB/SignalReader.hpp"

CanGwModel::CanGwModel(int argc, char** argv) :
canSignalCollectionModel_(std::make_unique<std::map<int, std::unique_ptr<CanSignalModel>>>())
{
    FrameReader FrameReader("signaldb.xlsx");
    txCanFramesCollectionModel_ = std::move(FrameReader.getTxFrames("ADAS"));
    rxCanFramesCollectionModel_ = std::move(FrameReader.getRxFrames("ADAS"));

    SignalReader signalReader("signaldb.xlsx");
    canSignalDefinitionCollectionModel_ = std::move(signalReader.getSignalDefinitions());

    commandLineModel_ = std::make_unique<CommandLineModel>(argc, argv);
}

std::map<int,  std::unique_ptr<CanSignalModel>>* CanGwModel::getCanSignalCollectionModel() 
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

CanGwModel::CanGwModel() 
{
    FrameReader FrameReader("signaldb.xlsx");
    txCanFramesCollectionModel_ = std::move(FrameReader.getTxFrames("ADAS"));
    rxCanFramesCollectionModel_ = std::move(FrameReader.getRxFrames("ADAS"));

    SignalReader signalReader("signaldb.xlsx");
    canSignalDefinitionCollectionModel_ = std::move(signalReader.getSignalDefinitions());

    commandLineModel_ = std::make_unique<CommandLineModel>(0, nullptr);
}
