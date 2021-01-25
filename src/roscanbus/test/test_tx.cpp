#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <memory>
#include <map>


#include "../src/Controllers/FrameToSignalsController.hpp"

#include "../src/CanDB/FrameReader.hpp"
#include "../src/CanDB/SignalReader.hpp"
#include "../src/CanGwModel.hpp"
#include "../src/Controllers/FrameToSignalsController.hpp"
#include "../src/CanDB/SignalDefinition.hpp"
#include "../src/CanDB/Frame.hpp"
#include "../src/CanDB/SignalDecoder.hpp"

#include "../src/Controllers/CanTransmitterController.hpp"

#include "../src/CanGwInterfaces.hpp"
#include "../src/CanGwController.hpp"

std::unique_ptr<CanGwInterfaces> canGwInterfaces;
std::unique_ptr<CanGwModel> canGwModel;
std::unique_ptr<CanGwController> canGwController;

std::vector<std::vector<int>> txFrameModes
{
    std::vector<int> {1,2,3,4},
    std::vector<int> {7,8},
};

void test_on_framex(const int & frameId, std::map<int,Frame>* frameCollections, CanSignalCollectionModel* signalCollectionModel)
{
    auto test_signals = frameCollections->at(frameId).getSignals();
    
    std::vector<double> testSignalValues;
    
    int cnt = 0;
    for(auto & signalId : *test_signals)
    {
        //random message test, not repeating
        double sv = 10 + cnt;
        testSignalValues.emplace_back(sv);        
        signalCollectionModel->getCanSignal(signalId)->setValue(sv);

        cnt++;
    }

    std::cout << "test on Frame id : " << frameId << ", use command candump vcan0 | grep " << frameId << std::endl;

    std::cout << "expected message : ";
    for(auto & sv : testSignalValues) std::cout << sv << " ";
    std::cout << std::endl;
}

bool test_signal_decoder_on_single_signal()
{
    SignalDecoder::signal s;
    s.byte_order = SignalDecoder::byte_order::INTEL;
    s.len = 8;
    s.start_bit = 0;
    SignalDecoder signalDecoder;
    signalDecoder.set_signal(s, 0x55);
    return signalDecoder.data == nullptr;
}

int main()
{
    std::cout << "init test env \n";

    auto txFrameMode = txFrameModes[0];    

    //start txFrameCollection with choosen mode
    //std::unique_ptr<std::map<int, Frame>> txFrames = std::make_unique<std::map<int, Frame>> ();

    FrameReader FrameReader("signaldb.xlsx");
    
    //std::map<int, Frame>    
    std::unique_ptr<std::map<int,Frame>> rxCanFramesCollectionModel = std::move(FrameReader.getRxFrames("ADAS"));
    std::unique_ptr<std::map<int,Frame>> txCanFramesCollectionModel = std::move(FrameReader.getTxFrames("ADAS"));
        
    //signal definitions 
    SignalReader signalReader("signaldb.xlsx");
    //definitions
    auto canSignalDefinitionCollectionModel = std::move(signalReader.getSignalDefinitions());
    auto canSignalCollectionModel = signalReader.createCanSignalCollectionModel();
 
    std::unique_ptr<Interfaces::CAN> vcan0Interface = std::make_unique<Interfaces::CAN> ("vcan0");
    std::unique_ptr<CanFrameEmitTimerModel> canFrameEmitTimerModel = std::make_unique<CanFrameEmitTimerModel> (txCanFramesCollectionModel.get());

    //and finally a stupid dummy tick to activate our transmitions

    std::unique_ptr<DummyTickModel> dummyTickingModel = std::make_unique<DummyTickModel> ();
    
    std::unique_ptr<CanTransmitterController> transmitterController = std::make_unique<CanTransmitterController>
    (   vcan0Interface.get(),
        canSignalCollectionModel.get(),
        txCanFramesCollectionModel.get(),
        canFrameEmitTimerModel.get(),
        canSignalDefinitionCollectionModel.get(),
        dummyTickingModel.get()
    );
    
    int testFrameId = 7;
    
    test_on_framex(testFrameId, txCanFramesCollectionModel.get(), canSignalCollectionModel.get());

    int test_duration = 1000000;
    for(int i = 0 ; i < test_duration; i++)
    {            
        dummyTickingModel->emit();
    }







    return 0;
}