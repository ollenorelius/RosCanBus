#pragma once

#include <map>
#include <memory>

class Frame;
class SignalDefinition;
class FrameData;
class CanSignalModel;

namespace Interfaces
{
    class CAN;
}

class FrameToSignalsController
{
    public:
    FrameToSignalsController(Interfaces::CAN* canInterface,
                             std::map<int, CanSignalModel*>* signalCollectionModel,
                             std::map<int, Frame>* rxCanFramesCollectionModel,
                             std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel);


    std::map<int, double> decodeCanFrame(FrameData frameData);
private:

    Interfaces::CAN* canInterface_;
    std::map<int, CanSignalModel*>* signalCollectionModel_;
    std::map<int, Frame>* rxCanFramesCollectionModel_;
    std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel_;
};