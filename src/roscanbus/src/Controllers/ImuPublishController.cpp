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
    signal_pub_ = rosNodeModel_->getNodeHandle()->advertise<sensor_msgs::Imu>("/imu", 100);

    auto callback = [this](){publish();};

    signals_[ImuData::ACC_X]->getValueChanged()->connect(callback);
    
}

void ImuPublishController::publish() 
{
    sensor_msgs::Imu imu_message;

    imu_message.header.frame_id = "imu_link";

    imu_message.header.stamp = ros::Time::now();

    imu_message.orientation.x = 0;
    imu_message.orientation.y = 0;
    imu_message.orientation.z = 0;

    imu_message.orientation_covariance[0] = -1;


    const float gyro_scaler = 1000*3.1415/180.0;
    imu_message.angular_velocity.x = signals_[ImuData::GYRO_X]->getValue()/32768.0*gyro_scaler;
    imu_message.angular_velocity.y = signals_[ImuData::GYRO_Y]->getValue()/32768.0*gyro_scaler;
    imu_message.angular_velocity.z = signals_[ImuData::GYRO_Z]->getValue()/32768.0*gyro_scaler;

    const float g = 9.82;
    const float acc_scaler = 2*g;
    imu_message.linear_acceleration.x = signals_[ImuData::ACC_X]->getValue()/32768.0*acc_scaler;
    imu_message.linear_acceleration.y = signals_[ImuData::ACC_Y]->getValue()/32768.0*acc_scaler;
    imu_message.linear_acceleration.z = signals_[ImuData::ACC_Z]->getValue()/32768.0*acc_scaler;


    
    signal_pub_.publish(imu_message);
 
}
