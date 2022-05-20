#include <ros/ros.h>
#include <std_msgs/String.h>
#include <visualization_msgs/Marker.h>

// Define a global subscriber to listen to robot status
ros::Publisher marker_pub;
visualization_msgs::Marker marker;

void modify_marker_callback(const std_msgs::String msg)
{
  if (msg.data == "pick_up") {
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ROS_INFO("Object is picked up");
  } else if (msg.data == "drop_off") {
    marker.pose.position.x = -5.0;
    marker.pose.position.y = 0.0;
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("Object is dropped off");
  } else {
    ROS_ERROR("Invalid message received! The message should be either pick_up or drop_off!");
  }
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers2");
  ros::NodeHandle n;
  ros::Rate r(1);

  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1, true);

  // Set the shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "pick_up_object";
  marker.id = 0;

  // Set the marker type.
  marker.type = shape;

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = 3.0;
  marker.pose.position.y = -2.0;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.5;
  marker.scale.y = 0.5;
  marker.scale.z = 0.5;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();

  ROS_INFO("Object at the pickup zone");
  marker_pub.publish(marker);

  ros::Subscriber robot_loc_sub = n.subscribe("/pick_objects/robot_location", 1, modify_marker_callback);

  ros::spin();

  return 0;
}
