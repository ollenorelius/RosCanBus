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
    std::map<int, SignalDecoder::signal> getSignalPositions(int frameId) const;
    std::map<int, double> getSignalValues(const std::map<int, SignalDecoder::signal>& signalPositions, const FrameData& framedata) const;
    Interfaces::CAN* canInterface_;
    CanSignalCollectionModel* signalCollectionModel_;
    std::map<int, Frame>* rxCanFramesCollectionModel_;
    std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel_;
};