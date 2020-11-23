#include "FrameToSignalsController.hpp"
#include "../Interfaces/CAN.hpp"
#include "../Interfaces/FrameData.hpp"
#include "../CanDB/Frame.hpp"
#include "../CanDB/SignalDefinition.hpp"
#include <iostream>
#include "../EventSignal.hpp"
#include "../Models/CanSignalModel.hpp"
#include "../Models/CanSignalCollectionModel.hpp"

FrameToSignalsController::FrameToSignalsController(Interfaces::CAN* canInterface,
                             CanSignalCollectionModel* signalCollectionModel,
                             std::map<int, Frame>* rxCanFramesCollectionModel,
                             std::map<int, SignalDefinition>* canSignalDefinitionCollectionModel) :
    canInterface_(canInterface),
    signalCollectionModel_(signalCollectionModel),
    rxCanFramesCollectionModel_(rxCanFramesCollectionModel),
    canSignalDefinitionCollectionModel_(canSignalDefinitionCollectionModel),
    signalDecoder_(std::make_unique<SignalDecoder> ())
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
    }
    catch (std::out_of_range e)
    {
        return signalValues;
    }

    Frame frameDefinition = rxCanFramesCollectionModel_->at(frameData.id);

    if (frameDefinition.getDlc() == 0)
    {
        int dlc = 0;   
        auto signals = frameDefinition.getSignals();
        
        for (int signalIndex : *signals)
        {
            dlc += canSignalDefinitionCollectionModel_->at(signalIndex).getLength();
        }
        dlc = dlc / 8 + (dlc % 8 != 0); // divide by 8 and round up.
        Frame frameToEdit = rxCanFramesCollectionModel_->at(frameData.id);
        frameToEdit.setDlc(dlc);
        (*rxCanFramesCollectionModel_)[frameData.id] = frameToEdit;
    }

    if (frameData.dlc != frameDefinition.getDlc())
    {
        std::cout << "Bad DLC received! " << frameData.dlc << " != " << frameDefinition.getDlc() << "\n";
        return signalValues;
    }
    

    std::vector<int>* signals = frameDefinition.getSignals();    

    long long int data = *(long long int*)(frameData.data);

    int i = 0 ;
    for (int signalId : *signals)
    {
        SignalDefinition signalDefinition = canSignalDefinitionCollectionModel_->at(signalId);
        int length = signalDefinition.getLength();  

        SignalDecoder::signal canSignal;       
        canSignal.byte_order = SignalDecoder::byte_order::INTEL;
        canSignal.len        = length;     

        long long int signalBits = data & ((1 << length)-1);        
        data = data >> length; // Then shift out those bits

        canSignal.start_bit  = length * (i++); 
        
        signalDecoder_->set_signal(&canSignal, signalBits);
        
        uint64_t output = 0;
        signalDecoder_->get_signal(&canSignal, &output);

        if(signalDefinition.getSignalType() == SIGNAL_TYPE::SIGNED) 
        {
            //std::cout << "SIGNED VAL: " << signalDecoder_->two_complement(output, length) << std::endl;
            signalValues.insert(std::pair<int, double> (signalId, signalDefinition.getScaler() * signalDecoder_->two_complement(output, length)));
        }
        else signalValues.insert(std::pair<int, double> (signalId, signalDefinition.getScaler() * output));
    }

    return signalValues;
}
