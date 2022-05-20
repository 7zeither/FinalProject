#include <ros/ros.h>
#include <std_msgs/String.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects2 node
  ros::init(argc, argv, "pick_objects2");

  ros::NodeHandle n;
  ros::Publisher robot_loc_pub = n.advertise<std_msgs::String>("/pick_objects/robot_location", 1);
  std_msgs::String robot_loc_msg;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 3.0;
  goal.target_pose.pose.position.y = -2.0;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Hooray, the base reached the pickup zone");
    robot_loc_msg.data = "pick_up";
    robot_loc_pub.publish(robot_loc_msg);    
  }
  else {
    ROS_INFO("The base failed to reach the pickup zone");
  }

  // Pause 5 seconds after reaching the pickup zone
  ros::Duration(5.0).sleep();

  // Define a second goal
  move_base_msgs::MoveBaseGoal goal2;

  // set up the frame parameters
  goal2.target_pose.header.frame_id = "map";
  goal2.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal2.target_pose.pose.position.x = -5.0;
  goal2.target_pose.pose.position.y = 0.0;
  goal2.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ac.sendGoal(goal2);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Hooray, the base reached the drop off zone");
    robot_loc_msg.data = "drop_off";
    robot_loc_pub.publish(robot_loc_msg);    
  }
  else {
    ROS_INFO("The base failed to reach the drop off zone");
  }

  return 0;
}