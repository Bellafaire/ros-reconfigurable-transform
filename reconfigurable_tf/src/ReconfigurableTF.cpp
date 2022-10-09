#include "ReconfigurableTF.hpp"

// Namespace matches ROS package name
namespace reconfigurable_tf
{
  // Constructor with global and private node handle arguments
  ReconfigurableTF::ReconfigurableTF(ros::NodeHandle &n, ros::NodeHandle &pn)
  {
    srv_.setCallback(boost::bind(&ReconfigurableTF::reconfig, this, _1, _2));

    bool child_found = pn.getParam("child_frame", child_frame);
    bool parent_found = pn.getParam("parent_frame", parent_frame);

    // if we're not provided the parent and child frames then there's nothing we can really do except exit.
    if (!child_found || !parent_found)
    {
      ROS_FATAL("Either parent or child frame not provided in launch parameters, reconfigurable_tf failed to launch!");
      exit(0);
    }

    //publish the transform on a timer at rate of 100hz TODO - make this a param.
    transform_pub = n.createTimer(ros::Duration(0.001),  &ReconfigurableTF::timerCallback, this);
  }

  void ReconfigurableTF::timerCallback(const ros::TimerEvent &event)
  {

    //now publish the tf transform with the information from the reconfigure server. 
    geometry_msgs::TransformStamped transform;

    //use child and parent frames from the launch params
    transform.header.frame_id = parent_frame;
    transform.child_frame_id = child_frame;

    //load the translation from the config server
    transform.transform.translation.x = cfg.x;
    transform.transform.translation.y = cfg.y;
    transform.transform.translation.z = cfg.z;


    //rotation of reconfiguration is in RPY, conver to quaternion for 
    tf2::Quaternion rotation;
    rotation.setRPY(cfg.roll, cfg.pitch, cfg.yaw);

    //load rotation into transform
    transform.transform.rotation.x = rotation.getX();
    transform.transform.rotation.y = rotation.getY();
    transform.transform.rotation.z = rotation.getZ();
    transform.transform.rotation.w = rotation.getW();

    //send the transform
    transform_broadcaster.sendTransform(transform);
  }

  //reconfigure server, takes in the dynamic reconfigure parameters for xyz and rpy and saves them. 
  //also print out when there's a change
  void ReconfigurableTF::reconfig(ReconfigurableTFConfig &config, uint32_t level)
  {
    cfg = config;
    ROS_INFO("TF Reconfigured xyz (%0.1f, %0.1f, %0.1f) rpy (%0.2f, %0.2f, %0.2f)", cfg.x, cfg.y, cfg.x, cfg.roll, cfg.pitch, cfg.yaw);
  }

}