#pragma once

#include <map>

#include "../CanDB/Frame.hpp"
#include "../Models/DummyTickModel.hpp"
#include "../CanDB/SignalDefinition.hpp"

class CanSignalCollectionModel;
class CanPublishTimerModel;
class CanFrameEmitTimerModel;

namespace Interfaces
{
    class CAN;
}

class CanTransmitterController
{
    
public:
    CanTransmitterController( Interfaces::CAN* canInterface,
                              CanSignalCollectionModel* canSignalCollectionModel, 
                              std::map<int, Frame>* txCanFramesCollectionModel,
                              CanFrameEmitTimerModel*     canFrameEmitTimerModel,
                              std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel,
                              DummyTickModel* dummyTickModel);

    void updateAndPublish();

private:     
    Interfaces::CAN*            canInterface_;
    CanSignalCollectionModel*   canSignalCollectionModel_;
    std::map<int, Frame>*       txCanFramesCollectionModel_;
    CanFrameEmitTimerModel*     canFrameEmitTimerModel_; 
    std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel_;   
};