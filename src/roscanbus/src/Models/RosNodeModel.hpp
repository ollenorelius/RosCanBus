#pragma once
#include "ros/ros.h"
#include <memory>

class RosNodeModel
{
public:
    RosNodeModel(int argc, char** argv);

    ros::NodeHandle* getNodeHandle();

private:
    std::unique_ptr<ros::NodeHandle> nodeHandle_;
};