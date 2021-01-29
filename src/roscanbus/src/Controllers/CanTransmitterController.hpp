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


private://testable
    void send();
    uint64_t packFrameData(const Frame& frame);
    int getDLC(const Frame& frame);

    Interfaces::CAN*            canInterface_;
    CanSignalCollectionModel*   canSignalCollectionModel_;
    std::map<int, Frame>*       txCanFramesCollectionModel_;
    CanFrameEmitTimerModel*     canFrameEmitTimerModel_; 
    std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel_;   
};