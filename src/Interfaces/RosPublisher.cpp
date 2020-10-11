#include "RosPublisher.hpp"

#include "ros/ros.h"

RosPublisher::RosPublisher(CommandLineModel* commandLineModel) 
{
    ros::init(commandLineModel->getArgc(), commandLineModel->getArgv(), "CanPublisher");

    ros::NodeHandle n;

    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("CanFrames", 1000);

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();
}
