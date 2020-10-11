#include "FrameToSignalsController.hpp"
#include "../Interfaces/CAN.hpp"
#include "../Interfaces/FrameData.hpp"
#include "../CanDB/Frame.hpp"
#include "../CanDB/SignalDefinition.hpp"
#include <iostream>
#include "../EventSignal.hpp"
#include "../CanSignalModel.hpp"

FrameToSignalsController::FrameToSignalsController(Interfaces::CAN* canInterface,
                             std::map<int, CanSignalModel*>* signalCollectionModel,
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
            signalCollectionModel_->emplace();
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
    Frame frameDefinition = rxCanFramesCollectionModel_->at(frameData.id);
    std::vector<int>* signals = frameDefinition.getSignals();

    long long int data = *(long long int*)(frameData.data);
    for (int signalId : *signals)
    {
        SignalDefinition signalDefinition = canSignalDefinitionCollectionModel_->at(signalId);
        int length = signalDefinition.getLength();
        /* Get only the last <length> bits */
        long long int signalBits = data & ((1 << length)-1);        
        data = data >> length; // Then shift out those bits

        if (signalDefinition.getSignalType() == SIGNAL_TYPE::SIGNED)
        {
            auto s = *reinterpret_cast<short*>(&signalBits);
            signalValues.insert(std::pair<int, double>(signalId, s));
        }
        if (signalDefinition.getSignalType() == SIGNAL_TYPE::UNSIGNED)
            signalValues.insert(std::pair<int, double>(signalId, *reinterpret_cast<unsigned long long int*>(&signalBits)));
        if (signalDefinition.getSignalType() == SIGNAL_TYPE::BOOL)
            signalValues.insert(std::pair<int, double>(signalId, static_cast<bool>(signalBits)));

    }
    return signalValues;
}
