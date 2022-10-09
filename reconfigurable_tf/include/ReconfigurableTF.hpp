#pragma once

#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <reconfigurable_tf/ReconfigurableTFConfig.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>
#include <string>

// Namespace matches ROS package name
namespace reconfigurable_tf
{

  class ReconfigurableTF
  {
  public:
    ReconfigurableTF(ros::NodeHandle &n, ros::NodeHandle &pn);

  private:
    void reconfig(ReconfigurableTFConfig &config, uint32_t level);
    void timerCallback(const ros::TimerEvent &event);

    ros::Timer transform_pub;
    dynamic_reconfigure::Server<ReconfigurableTFConfig> srv_;
    ReconfigurableTFConfig cfg;
    tf2_ros::TransformBroadcaster transform_broadcaster;

    std::string parent_frame;
    std::string child_frame;
  };

}