#include "RosNodeModel.hpp"
#include <iostream>

RosNodeModel::RosNodeModel(int argc, char** argv) 
{
    std::cout << "asdfas\n";
    ros::init(argc, argv,  "CanPublisher");
    nodeHandle_ = std::make_unique<ros::NodeHandle>();
}

ros::NodeHandle* RosNodeModel::getNodeHandle() 
{
    return nodeHandle_.get();
}
