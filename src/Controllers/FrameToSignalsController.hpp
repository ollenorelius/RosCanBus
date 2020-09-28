#pragma once

#include <map>

class Frame;
class SignalDefinition;
class FrameData;
namespace Interfaces
{
    class CAN;
}

class FrameToSignalsController
{
    public:
    FrameToSignalsController(Interfaces::CAN* canInterface,
                             std::map<int, double>* signalCollectionModel,
                             std::map<int, Frame>* rxCanFramesCollectionModel,
                             std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel);


    std::map<int, double> decodeCanFrame(FrameData frameData);
private:

    Interfaces::CAN* canInterface_;
    std::map<int, double>* signalCollectionModel_;
    std::map<int, Frame>* rxCanFramesCollectionModel_;
    std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel_;
};