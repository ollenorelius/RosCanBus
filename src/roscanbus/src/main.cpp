#include <iostream>
#include "xlnt/xlnt.hpp"
#include "CanGwModel.hpp"
#include "CanGwInterfaces.hpp"
#include "CanGwController.hpp"
#include <memory>
#include "ros/ros.h"


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
    //    std::cout << canGwInterfaces.getCanInterface()->getLatestCanFrame().data[0] << std::endl;
    //});
//    ros::spin();
    while (1)
    {
        canGwInterfaces.getCanInterface()->readCanFrame();
	ros::spinOnce();
    }

    return 0;
}
