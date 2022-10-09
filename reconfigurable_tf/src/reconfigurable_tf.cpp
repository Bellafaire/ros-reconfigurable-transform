// ROS and node class header file
#include <ros/ros.h>
#include "ReconfigurableTF.hpp"

int main(int argc, char** argv)
{
  // Initialize ROS and declare node handles
  ros::init(argc, argv, "reconfigurable");
  ros::NodeHandle n;
  ros::NodeHandle pn("~");
  
  // Instantiate node class
  reconfigurable_tf::ReconfigurableTF node(n, pn);

  // Spin and process callbacks
  ros::spin();
}