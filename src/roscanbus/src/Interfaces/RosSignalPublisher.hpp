#pragma once

#include <string>
#include <map>
#include "../CanDB/SignalDefinition.hpp"
#include "ros/ros.h"

class CanSignalModel;
class RosNodeModel;

class RosSignalPublisher
{
    public:
    RosSignalPublisher(CanSignalModel* canSignalModel,
                       RosNodeModel* rosNodeModel,
                       std::map<int, SignalDefinition>* canSignalDefinitions);

    private:
    void publishRosMessage();
    CanSignalModel* canSignalModel_;
    RosNodeModel* rosNodeModel_;
    ros::Publisher signal_pub_;
};

