#pragma once

#include <map>
#include <memory>

#include "../CanDB/SignalDecoder.hpp" //cant forward declare, why...

class Frame;
class SignalDefinition;
class FrameData;
class CanSignalModel;
class CanSignalCollectionModel;

namespace Interfaces
{
    class CAN;
}

class FrameToSignalsController
{
    public:
    FrameToSignalsController(Interfaces::CAN* canInterface,
                             CanSignalCollectionModel* signalCollectionModel,
                             std::map<int, Frame>* rxCanFramesCollectionModel,
                             std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel);


    std::map<int, double> decodeCanFrame(FrameData frameData);
private:

    Interfaces::CAN* canInterface_;
    CanSignalCollectionModel* signalCollectionModel_;
    std::map<int, Frame>* rxCanFramesCollectionModel_;
    std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel_;
    std::unique_ptr<SignalDecoder> signalDecoder_;
};