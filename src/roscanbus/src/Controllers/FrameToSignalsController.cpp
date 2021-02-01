#include "FrameToSignalsController.hpp"
#include "../Interfaces/CAN.hpp"
#include "../Interfaces/FrameData.hpp"
#include "../CanDB/Frame.hpp"
#include "../CanDB/SignalDefinition.hpp"
#include <iostream>
#include "../EventSignal.hpp"
#include "../Models/CanSignalModel.hpp"
#include "../Models/CanSignalCollectionModel.hpp"
#include <string.h> // memcpy

FrameToSignalsController::FrameToSignalsController(Interfaces::CAN* canInterface,
                             CanSignalCollectionModel* signalCollectionModel,
                             std::map<int, Frame>* rxCanFramesCollectionModel,
                             std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel) :
    canInterface_(canInterface),
    signalCollectionModel_(signalCollectionModel),
    rxCanFramesCollectionModel_(rxCanFramesCollectionModel),
    canSignalDefinitionCollectionModel_(canSignalDefinitionCollectionModel)
{
    auto decodeCanFrameCallback = [this]()
    {
        std::map<int, double> signalValues = decodeCanFrame(canInterface_->getLatestCanFrame());
        for (std::pair<int, double> signal : signalValues)
        {
            signalCollectionModel_->setCanSignalValue(signal.first, signal.second);
        }
    };
    canInterface_->getRxCanEvent()->connect(decodeCanFrameCallback);
}

std::map<int, double> FrameToSignalsController::decodeCanFrame(FrameData frameData) 
{
    /* As it stands, I've only tested this method for byte aligned ints and floats.
     * It seems to work for these, but I need to make test cases using arbitrary 
     * data before I can make sure it works generally.
     */
    std::map<int, double> signalValues;

    
    try
    {
        Frame frameDefinition = rxCanFramesCollectionModel_->at(frameData.id);
        if (frameData.dlc != frameDefinition.getDlc())
        {
            std::cout << "Bad DLC received! " << frameData.dlc << " != " << frameDefinition.getDlc() << "\n";
            return std::map<int, double>();
        }
    }
    catch (std::out_of_range e)
    {
        return std::map<int, double>();
    }


    // pull out signalvalue for each

    std::map<int, SignalDecoder::signal> signalPositions = getSignalPositions(frameData.id);
    return getSignalValues(signalPositions, frameData);
}

std::map<int, SignalDecoder::signal> FrameToSignalsController::getSignalPositions(int frameId) const
{
    std::map<int, SignalDecoder::signal> signalPositions;
    Frame frameDefinition = rxCanFramesCollectionModel_->at(frameId);

    

    const std::vector<int>* signals = frameDefinition.getSignals();    

    // Create map of SignalDecoder::signal-s
    int rolling_start = 0;
    for (int signalId : *signals)
    {   // Could be cached for performance
        SignalDefinition signalDefinition = canSignalDefinitionCollectionModel_->at(signalId);
        int length = signalDefinition.getLength();  

        SignalDecoder::signal canSignal;       
        canSignal.byte_order = SignalDecoder::byte_order::INTEL;
        canSignal.len        = length;
        canSignal.signal_type = signalDefinition.getSignalType();

        canSignal.start_bit = rolling_start;
        signalPositions[signalId] = canSignal;
        rolling_start += length;
    }
}

std::map<int, double> FrameToSignalsController::getSignalValues(const std::map<int, SignalDecoder::signal>& signalPositions, const FrameData& frameData) const
{
    SignalDecoder signalDecoder;
    memcpy(signalDecoder.data, frameData.data, frameData.dlc);
    std::map<int, double> signalValues;

    for (std::pair<int, SignalDecoder::signal> signalPosition : signalPositions)
    {
        if (signalPosition.second.signal_type == SIGNAL_TYPE::SIGNED)
        {
            int64_t val = 0;
            signalDecoder.get_signal_signed(&signalPosition.second, &val);
            signalValues[signalPosition.first] = static_cast<double>(val);
        }
        else if (signalPosition.second.signal_type == SIGNAL_TYPE::UNSIGNED)
        {
            uint64_t val = 0;
            signalDecoder.get_signal(&signalPosition.second, &val);
            signalValues[signalPosition.first] = static_cast<double>(val);
        }
    }
    return signalValues;
}
