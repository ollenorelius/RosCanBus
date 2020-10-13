#pragma once
#include "ros/ros.h"

class RosNodeModel
{
public:
    RosNodeModel(int argc, char** argv);

    ros::NodeHandle* getNodeHandle();

private:
    ros::NodeHandle nodeHandle_;
};