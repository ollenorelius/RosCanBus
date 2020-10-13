#include "RosPublisher.hpp"
#include "../Models/RosNodeModel.hpp"

#include "ros/ros.h"
#include "std_msgs/String.h"

Interfaces::RosPublisher::RosPublisher(RosNodeModel* rosNodeModel) 
{
    //ros::init(commandLineModel->getArgc(), commandLineModel->getArgv(), "CanPublisher");

    ros::NodeHandle* n = rosNodeModel->getNodeHandle();

    ros::Publisher chatter_pub = n->advertise<std_msgs::String>("CanFrames", 1000);

    std_msgs::String msg;
 
    std::stringstream ss;
    ss << "hello world " << 1;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    //ros::spin();
}
