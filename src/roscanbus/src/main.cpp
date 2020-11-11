#include <iostream>
#include "xlnt/xlnt.hpp"
#include "CanGwModel.hpp"
#include "CanGwInterfaces.hpp"
#include "CanGwController.hpp"
#include <memory>
#include "ros/ros.h"

#include "Controllers/CanTransmitterController.hpp"
#include "Models/CanPublishTimerModel.hpp"

int main(int argc, char** argv)
{
    std::cout << "Can GW v0.0\n";


    std::unique_ptr<CanGwModel> canGwModel;
    try 
    {
        canGwModel = std::make_unique<CanGwModel>(argc, argv);
    }
    catch (xlnt::exception e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
    CanGwInterfaces canGwInterfaces(canGwModel.get());
    CanGwController canGwController(canGwModel.get(), &canGwInterfaces);

    //canGwInterfaces.getCanInterface()->getRxCanEvent()->connect([&canGwInterfaces](){
        //std::cout << canGwInterfaces.getCanInterface()->getLatestCanFrame().data[0] << std::endl;
    //});
//    ros::spin();

    std::unique_ptr<CanPublishTimerModel> canPublishtimerModel = 
        std::make_unique<CanPublishTimerModel> ();
    std::unique_ptr<CanSignalList> canSignalList = std::make_unique<CanSignalList> (); 

    FrameData fd;
    fd.id = 5;
    fd.dlc = 8;  
    fd.data[0] = 0xFF;
    
    canSignalList->emplace_back(fd); //insert a random frame data to publish

    std::unique_ptr<CanTransmitterController> canTransmitterController = 
        std::make_unique<CanTransmitterController> (
            canGwInterfaces.getCanInterface(),
            canSignalList.get(), 
            canPublishtimerModel.get());

    while (1)
    {
        //canGwInterfaces.getCanInterface()->readCanFrame();
	    
        canTransmitterController->updateAndPublish();
        ros::spinOnce();
           
    }

    return 0;
}
