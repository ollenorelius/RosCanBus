#include "../src/CanGwModel.hpp"
#include "../src/Controllers/FrameToSignalsController.hpp"
#include "../src/CanDB/SignalDefinition.hpp"
#include "../src/CanDB/Frame.hpp"
#include <memory>

#include "../src/Controllers/FrameToSignalsController.hpp"

#include "../src/CanGwModel.hpp"
#include "../src/Controllers/FrameToSignalsController.hpp"
#include "../src/CanDB/SignalDefinition.hpp"
#include "../src/CanDB/Frame.hpp"
#include "../src/CanDB/SignalDecoder.hpp"
#include <memory>

#include "../src/Controllers/FrameToSignalsController.hpp"

#include "../src/CanGwInterfaces.hpp"
#include "../src/CanGwController.hpp"

#include <iostream>
#include <stdio.h>
#include <string.h>

std::unique_ptr<CanGwInterfaces> canGwInterfaces;
std::unique_ptr<CanGwModel> canGwModel;
std::unique_ptr<CanGwController> canGwController;

bool testCreateFramesToSignalsController();
void reinit();
bool testDecodeCanFrame();

bool testDecodeSonarCanFrame();
bool testDecodeWheelSpeedCanFrame();
bool testDecodeMotorCanFrame();
bool testDecodePowerStatusCanFrame();
bool testDecodeNonByteAlignment();

const static std::string DB = "signaldb.xlsx";
const static std::string NODE = "ADAS";

int main()
{
    testCreateFramesToSignalsController();
    testDecodeCanFrame();

    return 0;
}

bool testCreateFramesToSignalsController()
{
    reinit();
    std::unique_ptr<CanGwModel> canGwModel = std::make_unique<CanGwModel>(DB, NODE);
    auto ft2s = FrameToSignalsController(canGwInterfaces->getCanInterface(),
                                         canGwModel->getCanSignalCollectionModel(),
                                         canGwModel->getRxCanFramesCollectionModel(),
                                         canGwModel->getCanSignalDefinitionCollectionModel());
    
}

bool testDecodeOnSonarCanFrame()
{       
    reinit();

    std::unique_ptr<CanGwModel> canGwModel = std::make_unique<CanGwModel>(DB, NODE);
    auto ft2s = FrameToSignalsController(canGwInterfaces->getCanInterface(),
                                         canGwModel->getCanSignalCollectionModel(),
                                         canGwModel->getRxCanFramesCollectionModel(),
                                         canGwModel->getCanSignalDefinitionCollectionModel());
    
    bool test_pass = true;
    FrameData fd;
    fd.id = 0x11;
    fd.dlc = 16;

    uint16_t realdata_0[4]; 
    realdata_0[0] = 0xffff;
    realdata_0[1] = 0x3515;
    realdata_0[2] = 0x2616;
    realdata_0[3] = 0xED14;

    fd.data[0] = 0xff;
    fd.data[1] = 0xff;
    fd.data[2] = 0x15;
    fd.data[3] = 0x35;
    fd.data[4] = 0x16;
    fd.data[5] = 0x26;
    fd.data[6] = 0x14;
    fd.data[7] = 0xed;
   
    auto signals = ft2s.decodeCanFrame(fd);
    int i = 0;
    for (auto data : signals)
    {
        // fprintf(stdout, "%X \n", static_cast<int>(data.second));
        // std::cout.precision(17);      
        std::cout << "id: " << data.first << " data: " << data.second << " expected " << (int)realdata_0[i] << "\n";
        if(realdata_0[i] != data.second) test_pass = false;
        
        ++i;
    }

    return test_pass;
}

bool testDecodeWheelSpeedCanFrame()
{
    reinit();

    std::unique_ptr<CanGwModel> canGwModel = std::make_unique<CanGwModel>(DB, NODE);
    auto ft2s = FrameToSignalsController(canGwInterfaces->getCanInterface(),
                                         canGwModel->getCanSignalCollectionModel(),
                                         canGwModel->getRxCanFramesCollectionModel(),
                                         canGwModel->getCanSignalDefinitionCollectionModel());
    bool test_pass = true;
    FrameData fd;
    fd.id = 0x06;
    fd.dlc = 16;

    uint16_t realdata_0[4]; 
    realdata_0[0] = 0xFFFF;
    realdata_0[1] = 0x3515;

    fd.data[0] = 0xff;
    fd.data[1] = 0xff;
    fd.data[2] = 0x15;
    fd.data[3] = 0x35;

    auto signals = ft2s.decodeCanFrame(fd);
    int i = 0;
    for (auto data : signals)
    {
        uint64_t lv = realdata_0[i];   
        std::cout << "id: " << data.first << " data: " << data.second << " expected " << SignalDecoder::two_complement(lv, fd.dlc) << "\n";
        if(SignalDecoder::two_complement(lv, fd.dlc) != data.second) test_pass = false;
        
        ++i;
    }

    return test_pass;  
}

bool testDecodeMotorCanFrame()
{
    reinit();

    std::unique_ptr<CanGwModel> canGwModel = std::make_unique<CanGwModel>(DB, NODE);
    auto ft2s = FrameToSignalsController(canGwInterfaces->getCanInterface(),
                                         canGwModel->getCanSignalCollectionModel(),
                                         canGwModel->getRxCanFramesCollectionModel(),
                                         canGwModel->getCanSignalDefinitionCollectionModel());
    bool test_pass = true;
    FrameData fd;
    fd.id = 0x02;
    fd.dlc = 16;

    uint16_t realdata_0[4]; 
    realdata_0[0] = 0xFFFF;
    realdata_0[1] = 0x15;

    fd.data[0] = 0xff;
    fd.data[1] = 0xff;
    fd.data[2] = 0x15;
    
    auto signals = ft2s.decodeCanFrame(fd);
    int i = 0;
    for (auto data : signals)
    {
        uint64_t lv = realdata_0[i];      
        std::cout << "id: " << data.first << " data: " << data.second << " expected " << lv << "\n";
        if(lv != data.second) test_pass = false;
        
        ++i;
    }

    return test_pass;
}

bool testDecodePowerStatusCanFrame()
{
    reinit();

    std::unique_ptr<CanGwModel> canGwModel = std::make_unique<CanGwModel>(DB, NODE);
    auto ft2s = FrameToSignalsController(canGwInterfaces->getCanInterface(),
                                         canGwModel->getCanSignalCollectionModel(),
                                         canGwModel->getRxCanFramesCollectionModel(),
                                         canGwModel->getCanSignalDefinitionCollectionModel());
    
    bool test_pass = true;
    FrameData fd;
    fd.id = 0x03;
    fd.dlc = 1;

    uint16_t realdata_0[4]; 
    realdata_0[0] = 0x0;
    realdata_0[1] = 0x1;
    realdata_0[2] = 0x0;
    realdata_0[3] = 0x1;

    fd.data[0] = 0b00001010; //0x0A;
   
    auto signals = ft2s.decodeCanFrame(fd);
    int i = 0;
    for (auto data : signals)
    {            
        std::cout << "id: " << data.first << " data: " << data.second << " expected " << (int)realdata_0[i] << "\n";
        if(realdata_0[i] != data.second) test_pass = false;
        
        ++i;
    }

    return test_pass;
}

bool testDecodeNonByteAlignment()
{    
    reinit();

    std::unique_ptr<CanGwModel> canGwModel = std::make_unique<CanGwModel>(DB, NODE);
    auto ft2s = FrameToSignalsController(canGwInterfaces->getCanInterface(),
                                         canGwModel->getCanSignalCollectionModel(),
                                         canGwModel->getRxCanFramesCollectionModel(),
                                         canGwModel->getCanSignalDefinitionCollectionModel());
    
    FrameData fd;
    fd.id = 0x11;
    fd.dlc = 8;
    Frame frameDefinition = canGwModel->getRxCanFramesCollectionModel()->at(fd.id); 
    const std::vector<int>* signals = frameDefinition.getSignals();
    int nrSignals = signals->size(); 

    SignalDecoder canDataPackage;
    canDataPackage.id  = fd.id;
    canDataPackage.dlc = fd.dlc;

    //test messages   
    uint64_t canDumpInput[nrSignals] = {1,0xFF,0xE1,0x33};
    int startBitPosition[nrSignals] = {0};

    bool    testPass = true;  
    uint64_t  tmpValueOutput = 0;   

    for(int idx = 0; idx < signals->size(); ++idx ) 
    {       
        SignalDefinition signalDefinition = canGwModel->getCanSignalDefinitionCollectionModel()->at(signals->at(idx));

        SignalDecoder::signal canSignal;
        canSignal.start_bit = startBitPosition[idx];
        canSignal.byte_order = SignalDecoder::byte_order::INTEL;
        canSignal.len  = canDataPackage.dlc;
        
        int tmpValueInput = canDumpInput[idx];
        auto signalType = signalDefinition.getSignalType();        
                 
        tmpValueOutput = 0;
        canDataPackage.set_signal(&canSignal, tmpValueInput);   
        canDataPackage.get_signal(&canSignal, &tmpValueOutput);               
           
        std::cout.precision(17);
        // fprintf(stdout, "%X \n", static_cast<int>(canDumpInput[idx]));
        if(signalType == SIGNAL_TYPE::SIGNED)  
        {   
            std::cout << "id: " << canDataPackage.id << " data : " << canDataPackage.data << " decoded value: " 
            <<  SignalDecoder::two_complement(tmpValueOutput, 8) << " expected : " << SignalDecoder::two_complement(canDumpInput[idx], 8)  << "\n";   

            if(SignalDecoder::two_complement(tmpValueOutput, canSignal.len) != SignalDecoder::two_complement(canDumpInput[idx], canSignal.len))testPass = false;  
        }
        else
        {  
            std::cout << "id: " << canDataPackage.id << " data : " <<  canDataPackage.data << " decoded value: " 
            <<  tmpValueOutput << " expected : " <<  tmpValueOutput << "\n";  

            if(tmpValueOutput != canDumpInput[idx]) testPass = false; 
        }
    }

    return testPass; 
}

bool testDecodeCanFrame()
{
    if(testDecodeOnSonarCanFrame()) std::cout << "testDecodeOnSonarCanFrame()" << "::PASS::" << std::endl;
    else std::cout << "testDecodeOnSonarCanFrame()" << "::FAILED::" << std::endl;

    if(testDecodeWheelSpeedCanFrame()) std::cout << "testDecodeWheelSpeedCanFrame()" << "::PASS::" << std::endl;
    else std::cout << "testDecodeWheelSpeedCanFrame()" << "::FAILED::" << std::endl;

    if(testDecodeMotorCanFrame()) std::cout << "testDecodeMotorCanFrame()" << "::PASS::" << std::endl;
    else std::cout << "testDecodeMotorCanFrame()" << "::FAILED::" << std::endl;

    if(testDecodePowerStatusCanFrame()) std::cout << "testDecodePowerStatusCanFrame()" << "::PASS::" << std::endl;
    else std::cout << "testDecodePowerStatusCanFrame()" << "::FAILED::" << std::endl;

    if(testDecodeNonByteAlignment()) std::cout << "testDecodeNonByteAlignment()" << "::PASS::" << std::endl;
    else std::cout << "testDecodeNonByteAlignment()" << "::FAILED::" << std::endl;
          
}

void reinit()
{
    canGwModel = std::make_unique<CanGwModel>(DB, NODE);
    canGwInterfaces = std::make_unique<CanGwInterfaces>(canGwModel.get());
}
