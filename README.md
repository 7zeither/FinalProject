# Home Service Robot
## Packages:
1. `turtlebot_gazebo`: this package can be used to deploy a turtlebot in a gazebo environment by linking the world file to it (in our case, the world file is `src/map/MyLibrary.world`).
2. `turtlebot_teleop`: this package can be used to manually control a robot using keyboard commands. 
3. `turtlebot_rviz_launchers`: the rviz workspace is used to visualize robot's activities in an environment. This package can be used to load a preconfigured rviz workspace.
4. `amcl`: this package implements Adaptive Monte Carlo Localization (AMCL), which is an effective localization algorithm which helps the robot to determine its location in an environment as it navigates around the map.
5. `gmapping`: this package performs Simultaneous Localization and Mapping (SLAM) and will help build a map of the environment.
6. ROS navigation stack is used for navigation. It implements Dijkstra's to plan the robot's trajectory, which is a variant of the Uniform Cost Search algorithm.
7. `pick_objects`: this package is used to send pre-defined navigation goals to ROS navigation stack. Once a goal is sent, the navigation stack will create a path for the robot to reach the goal. Node `pick_objects2` is slightly different from node `pick_objects`, which includes a publisher which will publish a message once the robot arrives at a goal.
8. `add_markers`: this package is used to mimic a virtual object (as a marker) being picked up and dropped off. The marker will be published to rviz. It will appear/disappear at different locations. Node `add_markers2` has a subscriber which subscribes to the publisher defined in `pick_objects2`. The marker will appear and disappear according to the messages received from the publisher.

## Usage
This repo can be used to accomplish the following tasks:
1. Test SLAM by running `./src/scripts/test_slam.sh`. It will deploy a turtlebot in a given environment and visualize in rviz. We could teleoperate the turtlebot to explore the environment and perform SLAM to build a map. The map is then saved for later use (`src/map/MyLibraryMap.pgm` and `src/map/MyLibraryMap.yaml`).
2. Test localization and navigation by running `./src/scripts/test_navigation.sh`. It will deploy a turtlebot in a given environment and visualize in rviz. We can set a 2D NAV Goal in rviz for the turtlebot to travel. AMCL will be implemented for localization and Dijkstra's algorithm will be implemented for path planning.
3. Test localization and navigation with pre-defined goals by running `./src/scripts/pick_objects.sh`. We pre-defined a pickup zone and a drop off zone in node `pick_objects`. The turtlebot will navigate to these two zones successively.
4. Test virtual object by running `./src/scripts/add_markers.sh`. A marker (virtual object) will first appear at the pickup zone, and then disappear for a while, and then show up at the drop off zone. 
5. Test home service robot by running `./src/scripts/home_service.sh`. A marker (virtual object) will first appear at the pickup zone. The turtlebot will navigate to the pickup zone. The marker will disappear for a while (as being picked up by the turtlebot). Then the turtlebot will navigate to the drop off zone, and the marker will appear at the drop off zone (as dropped off).
