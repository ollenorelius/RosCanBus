#include "ImuPublishController.hpp"
#include "../Models/CanSignalCollectionModel.hpp"
#include "../Models/RosNodeModel.hpp"

#include "ros/ros.h"
#include "sensor_msgs/Imu.h"

ImuPublishController::ImuPublishController(std::map<ImuData, CanSignalModel*> signals, 
                 RosNodeModel* rosNodeModel) :
    signals_(signals),    
    rosNodeModel_(rosNodeModel)
{
    signal_pub_ = rosNodeModel_->getNodeHandle()->advertise<sensor_msgs::Imu>("imu", 100);

    auto callback = [this](){publish();};

    signals_[ImuData::ACC_X]->getValueChanged()->connect(callback);
}

void ImuPublishController::publish() 
{
    sensor_msgs::Imu imu_message;
    imu_message.orientation.x = 0;
    imu_message.orientation.y = 0;
    imu_message.orientation.z = 0;

    imu_message.orientation_covariance[0] = -1;

    imu_message.angular_velocity.x = signals_[ImuData::GYRO_X]->getValue();
    imu_message.angular_velocity.y = signals_[ImuData::GYRO_Y]->getValue();
    imu_message.angular_velocity.z = signals_[ImuData::GYRO_Z]->getValue();

    imu_message.linear_acceleration.x = signals_[ImuData::ACC_X]->getValue();
    imu_message.linear_acceleration.y = signals_[ImuData::ACC_Y]->getValue();
    imu_message.linear_acceleration.z = signals_[ImuData::ACC_Z]->getValue();


    
    signal_pub_.publish(imu_message);
 
}
