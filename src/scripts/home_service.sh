#!/bin/sh
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/map/MyLibrary.world" &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/map/MyLibraryMap.yaml" &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation_with_marker.launch" &
sleep 5
xterm  -e  " source devel/setup.bash; rosrun add_markers add_markers2" &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch pick_objects pick_objects2.launch"