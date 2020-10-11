#include "../src/CanGwModel.hpp"
#include "../src/Controllers/FrameToSignalsController.hpp"
#include "../src/CanDB/SignalDefinition.hpp"
#include "../src/CanDB/Frame.hpp"
#include <memory>

#include "../src/Controllers/FrameToSignalsController.hpp"

#include "../src/CanGwInterfaces.hpp"
#include "../src/CanGwController.hpp"
#include "../src/CanSignalModel.hpp"

#include <iostream>


std::unique_ptr<CanGwInterfaces> canGwInterfaces;
std::unique_ptr<CanGwModel> canGwModel;
std::unique_ptr<CanGwController> canGwController;

bool testCreateFramesToSignalsController();
void reinit();
bool testDecodeCanFrame();

int main()
{
    testCreateFramesToSignalsController();
    testDecodeCanFrame();

    return 0;
}

bool testCreateFramesToSignalsController()
{
    reinit();
    std::unique_ptr<CanGwModel> canGwModel = std::make_unique<CanGwModel>();
    auto ft2s = FrameToSignalsController(canGwInterfaces->getCanInterface(),
                                         canGwModel->getCanSignalCollectionModel(),
                                         canGwModel->getRxCanFramesCollectionModel(),
                                         canGwModel->getCanSignalDefinitionCollectionModel());
    
}

bool testDecodeCanFrame()
{
    reinit();
    std::unique_ptr<CanGwModel> canGwModel = std::make_unique<CanGwModel>();
    auto ft2s = FrameToSignalsController(canGwInterfaces->getCanInterface(),
                                         canGwModel->getCanSignalCollectionModel(),
                                         canGwModel->getRxCanFramesCollectionModel(),
                                         canGwModel->getCanSignalDefinitionCollectionModel());
    
    FrameData fd;
    fd.id = 6;
    fd.dlc = 8;
    fd.data[0] = 0xff;
    fd.data[1] = 0xff;
    fd.data[2] = 0x15;
    fd.data[3] = 0x35;
    fd.data[4] = 0x16;
    fd.data[5] = 0x26;
    fd.data[6] = 0x14;
    fd.data[7] = 0xed;
    auto signals = ft2s.decodeCanFrame(fd);
    
    for (auto data : signals)
    {
        fprintf(stdout, "%X \n", static_cast<int>(data.second));
        std::cout.precision(17);
        std::cout << 4323.23;
        std::cout << "id: " << data.first << " data: " << data.second << "\n";
    }
}

void reinit()
{
    canGwModel = std::make_unique<CanGwModel>();
    canGwInterfaces = std::make_unique<CanGwInterfaces>(canGwModel.get());
}