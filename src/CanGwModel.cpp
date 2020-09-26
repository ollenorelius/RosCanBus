#include "CanGwModel.hpp"
#include "CanDB/FrameReader.hpp"
#include "CanDB/SignalReader.hpp"

CanGwModel::CanGwModel() :
canSignalCollectionModel_(std::make_unique<std::map<int, double>>())
{
    FrameReader FrameReader("signaldb.xlsx");
    txCanFramesCollectionModel_ = std::move(FrameReader.getTxFrames("ADAS"));
    rxCanFramesCollectionModel_ = std::move(FrameReader.getRxFrames("ADAS"));

    SignalReader signalReader("signaldb.xlsx");
    canSignalDefinitionCollectionModel_ = std::move(signalReader.getSignalDefinitions());
}

std::map<int, double>* CanGwModel::getCanSignalCollectionModel() 
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
