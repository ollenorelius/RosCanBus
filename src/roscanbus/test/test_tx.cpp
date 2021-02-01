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

#define private public
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


#define BEGIN_TEST(TestSuite, TestName)                                    \
   bool test__##TestSuite##__##TestName(void)                              \
{                                                                          \
      bool isTrue{true};

#define END_TEST                                                           \
   return isTrue;                                                          \
}

#define EXPECT_EQ(arg1, arg2) isTrue &= (arg1 == arg2); 

#define RUN_TEST(TestSuite, TestName)                                      \
{                                                                          \
   bool ret = test__##TestSuite##__##TestName();                           \
   std::cout << std::left << std::setfill('-')                             \
   << std::setw(50) << #TestSuite " --> " #TestName " ";                   \
                                                                           \
   if(ret)                                                                 \
   {                                                                       \
      std::cout << std::setw(10)                                           \
      << std::left << "\x1b[38;5;40m   OK \x1b[0m" /* colored in Green*/   \
      << std::endl;                                                        \
   }                                                                       \
   else                                                                    \
   {                                                                       \
      std::cout << std::setw(10)                                           \
      << std::left << "\x1b[38;5;160m   FAILED \x1b[0m" /* colored in Red*/\
      << std::endl;                                                        \
   }                                                                       \
} /* Coloring valid for *nix systems. */

BEGIN_TEST(signal_decoder, set_single_byte_signal)
{
    SignalDecoder::signal s;
    s.byte_order = SignalDecoder::byte_order::INTEL;
    s.len = 8;
    s.start_bit = 8;
    SignalDecoder signalDecoder;
    signalDecoder.set_signal(&s, (uint64_t)-1);
    EXPECT_EQ(signalDecoder.data_single, 0xFF<<8);

    signalDecoder.set_signal(&s, 0xAA);
    EXPECT_EQ(signalDecoder.data_single, 0xAA<<8);

}
END_TEST

BEGIN_TEST(signal_decoder, set_multi_byte_signal)
{
    SignalDecoder::signal s;
    s.byte_order = SignalDecoder::byte_order::INTEL;
    s.len = 15;
    s.start_bit = 6;
    SignalDecoder signalDecoder;
    signalDecoder.set_signal(&s, (uint64_t)-1);
    EXPECT_EQ(signalDecoder.data_single, 0x7FFF<<s.start_bit);

    signalDecoder.set_signal(&s, 0xAA);
    EXPECT_EQ(signalDecoder.data_single, 0xAA<<s.start_bit);

}
END_TEST

BEGIN_TEST(signal_decoder, get_multi_byte_signal)
{
    SignalDecoder::signal s;
    s.byte_order = SignalDecoder::byte_order::INTEL;
    s.len = 15;
    s.start_bit = 6;
    SignalDecoder signalDecoder;
    signalDecoder.data_single = 0x7FFF << s.start_bit;
    uint64_t val = 0;
    signalDecoder.get_signal(&s, &val);
    EXPECT_EQ(val, 0x7FFF);

    signalDecoder.set_signal(&s, 0xAA);
    EXPECT_EQ(signalDecoder.data_single, 0xAA<<s.start_bit);

}
END_TEST

BEGIN_TEST(signal_decoder, integration)
{
    SignalDecoder::signal s1;
    s1.byte_order = SignalDecoder::byte_order::INTEL;
    s1.len = 19;
    s1.start_bit = 6;

    SignalDecoder::signal s2;
    s2.byte_order = SignalDecoder::byte_order::INTEL;
    s2.len = 6;
    s2.start_bit = 0;

    SignalDecoder signalDecoder;
    int value1 = -55;
    signalDecoder.set_signal(&s1, value1);
    int value2 = 22;
    signalDecoder.set_signal(&s2, value2);

    int64_t out = 0;
    signalDecoder.get_signal_signed(&s1, &out);
    EXPECT_EQ(value1, out);
    signalDecoder.get_signal_signed(&s2, &out);
    EXPECT_EQ(value2, out);
}
END_TEST

BEGIN_TEST(signal_decoder, unsigned_integration)
{
    SignalDecoder::signal s;
    s.byte_order = SignalDecoder::byte_order::INTEL;
    s.len = 15;
    s.start_bit = 6;
    SignalDecoder signalDecoder;
    int value = 5553;
    signalDecoder.set_signal(&s, value);
    uint64_t out = 0;
    signalDecoder.get_signal(&s, &out);
    EXPECT_EQ(value, out);

    SignalDecoder::signal s1;
    s1.byte_order = SignalDecoder::byte_order::INTEL;
    s1.len = 19;
    s1.start_bit = 9;

    SignalDecoder::signal s2;
    s2.byte_order = SignalDecoder::byte_order::INTEL;
    s2.len = 6;
    s2.start_bit = 0;

    int value1 = 55412;
    signalDecoder.set_signal(&s1, value1);
    int value2 = 22;
    signalDecoder.set_signal(&s2, value2);

    signalDecoder.get_signal(&s1, &out);
    EXPECT_EQ(value1, out);
    signalDecoder.get_signal(&s2, &out);
    EXPECT_EQ(value2, out);
}
END_TEST

BEGIN_TEST(can_transmitter_controller, pack_data)
{
    std::unique_ptr<Interfaces::CAN> vcan0Interface = std::make_unique<Interfaces::CAN> ("vcan0");
    CanTransmitterController canTransmitterController(vcan0Interface.get(),
                                                       canGwModel->getCanSignalCollectionModel(),
                                                       canGwModel->getTxCanFramesCollectionModel(),
                                                       canGwModel->getCanFrameEmitTimerModel(),
                                                       canGwModel->getCanSignalDefinitionCollectionModel(),
                                                       canGwModel->getDummyTickModel());

    canGwModel->getCanSignalCollectionModel()->getCanSignal(34)->setValue(0xAA);
    canGwModel->getCanSignalCollectionModel()->getCanSignal(35)->setValue(0x55);
    Frame frame = canGwModel->getTxCanFramesCollectionModel()->at(9);
    uint64_t data = canTransmitterController.packFrameData(frame);
    std::cout << data << "\n";
    EXPECT_EQ(data,0x55AA);
}
END_TEST

BEGIN_TEST(can_transmitter_controller, calc_dlc)
{
    std::unique_ptr<Interfaces::CAN> vcan0Interface = std::make_unique<Interfaces::CAN> ("vcan0");
    CanTransmitterController canTransmitterController(vcan0Interface.get(),
                                                       canGwModel->getCanSignalCollectionModel(),
                                                       canGwModel->getTxCanFramesCollectionModel(),
                                                       canGwModel->getCanFrameEmitTimerModel(),
                                                       canGwModel->getCanSignalDefinitionCollectionModel(),
                                                       canGwModel->getDummyTickModel());

    canGwModel->getCanSignalCollectionModel()->getCanSignal(34)->setValue(0xAA);
    canGwModel->getCanSignalCollectionModel()->getCanSignal(35)->setValue(0x55);
    Frame frame = canGwModel->getTxCanFramesCollectionModel()->at(9);
    
    EXPECT_EQ(canTransmitterController.getDLC(frame),2);
}
END_TEST



int main()
{

    RUN_TEST(signal_decoder, set_single_byte_signal);
    RUN_TEST(signal_decoder, set_multi_byte_signal);
    RUN_TEST(signal_decoder, get_multi_byte_signal);
    RUN_TEST(signal_decoder, integration);
    RUN_TEST(signal_decoder, unsigned_integration);
    
    canGwModel = std::make_unique<CanGwModel>("test_signaldb.xlsx", "ADAS");
    canGwInterfaces = std::make_unique<CanGwInterfaces>(canGwModel.get());
    std::cout << "asd4f\n";
    RUN_TEST(can_transmitter_controller, pack_data)
    RUN_TEST(can_transmitter_controller, calc_dlc)

    //test_signal_decoder_on_single_signal();
    std::cout << "init test env \n";

    auto txFrameMode = txFrameModes[0];    

    //start txFrameCollection with choosen mode
    //std::unique_ptr<std::map<int, Frame>> txFrames = std::make_unique<std::map<int, Frame>> ();
    //signal definitions 
    SignalReader signalReader("signaldb.xlsx");
    //definitions
    auto canSignalDefinitionCollectionModel = std::move(signalReader.getSignalDefinitions());
    auto canSignalCollectionModel = signalReader.createCanSignalCollectionModel();

    FrameReader FrameReader("signaldb.xlsx", canSignalDefinitionCollectionModel.get());
    
    //std::map<int, Frame>    
    std::unique_ptr<std::map<int,Frame>> rxCanFramesCollectionModel = std::move(FrameReader.getRxFrames("ADAS"));
    std::unique_ptr<std::map<int,Frame>> txCanFramesCollectionModel = std::move(FrameReader.getTxFrames("ADAS"));
        
 
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
