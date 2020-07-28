#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <autoware_msgs/VehicleCmd.h>
#include <string>

serial::Serial ser;

void write_callback_Accel(const autoware_msgs::AccelCmdConstPtr& msg){
    ROS_INFO_STREAM("Writing to serial port" << msg->accel);
    std::string accel_str = std::to_string(msg->accel);
    ser.write(accel_str);
}

void write_callback_Brake(const autoware_msgs::BrakeCmdConstPtr& msg){
    ROS_INFO_STREAM("Writing to serial port" << msg->brake);
    std::string brake_str = std::to_string(msg->brake);
    ser.write(brake_str);
}


void write_callback_Steer(const autoware_msgs::SteerCmdConstPtr& msg){
    ROS_INFO_STREAM("Writing to serial port" << msg->steer);
    std::string steer_str = std::to_string(msg->steer);
    ser.write(steer_str);
}


int main (int argc, char** argv){
    ros::init(argc, argv, "mava_serial_interface");
    ros::NodeHandle nh;
    ROS_INFO_STREAM("Initialized ");

    try
    {
        ser.setPort("/dev/ttyUSB0");
        ser.setBaudrate(9600);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
        ser.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
        return -1;
    }

    if(ser.isOpen()){
        ROS_INFO_STREAM("Serial Port initialized");
    }else{
        return -1;
    }

    while(ros::ok()){
    ros::Subscriber write_sub_Steer = nh.subscribe("steer_cmd", 1, write_callback_Steer);
    ros::Subscriber write_sub_Brake = nh.subscribe("brake_cmd", 1, write_callback_Brake);
    ros::Subscriber write_sub_Accel = nh.subscribe("accel_cmd", 1, write_callback_Accel);
    ROS_INFO_STREAM("Past function");
    ros::spin();

    }
    
}
