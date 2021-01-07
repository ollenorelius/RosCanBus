#pragma once

#include <map>
#include "../CanDB/SignalDefinition.hpp"
#include "std_msgs/Float32.h"
#include "ros/ros.h"

class CanSignalModel;
class RosNodeModel;

class RosSignalSubscriber
{
public:
    RosSignalSubscriber(CanSignalModel* canSignalModel,
                        RosNodeModel* rosNodeModel,
                        std::map<int, SignalDefinition>* canSignalDefinitions);

    private:
    CanSignalModel* canSignalModel_;
    RosNodeModel* rosNodeModel_;
    ros::Subscriber signalSub_;
    void subCallback(const std_msgs::Float32::ConstPtr& msg);
};