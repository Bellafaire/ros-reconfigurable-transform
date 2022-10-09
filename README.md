# ROS Reconfigurable Transform

I'm sure this has been done before many times, but I wasn't able to find a package anyone had written to do it on the internet. 
This repo contains the reconfigurable_tf package which generates a dynamically reconfigurable transform. 
This is useful if you're testing the positioning of sensors on a robot and moving them around often. 

# Installation

To install this package simply clone this repo to your catkin workspace and build, the node can then be utilized as shown below. 

## Launching the Node 

Below is a sample of the launch file to run this node, the params 'parent_frame' and 'child_frame' must be provided or the node will exit. 
Once launched the transforms can be adjusted using your parameter adjustment method of choice. 
The node allows the configuration of XYZ translation values and Roll-Pitch-Yaw orientation.
```
<node pkg="reconfigurable_tf" type="reconfigurable_tf_publisher" name="reconfigurable_tf_publisher" output="screen">
    <param name="parent_frame" value="map" />
    <param name="child_frame" value="tf1" />
</node>
```

An example launch file is provided for a quick demo: 

```
roslaunch reconfigurable_tf reconfigurable_tf.launch 
```
