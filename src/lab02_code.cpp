#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <stdlib.h> //this one is from the canvas site as well

//#include "stdr_simulator/robot0/cmd_vel.h"
//Do one of the above lines for every topic you subscribe to
//figure out what to type for topics published by a different package/node

//Please be nice to me Dr. Lee i have 0 idea what i am doing - Naomi Hourihane



int main(int argc, char **argv){

	//the following is the code i copied off of the canvas website
	// Process command line parameter looking for a -n string name
	// and should be placed after the ros::init() invocation.
	// rosrun <package_name> <executable_name> -n <new_name>
	// or
	// rosrun subscriber_package subscriber_node -n alternate_topic
	int opt;
	while ((opt = getopt(argc, (argv), "n:")) != -1) {
	  switch (opt) {
	    case 'n':
	      topic_name = optarg;
	      break;
	    default:
	      printf("The -%c is not a recognized parameter\n", opt);
	      break; 
	  }
	}
	int refresh_rate = 1000;
	ros :: init(argc, argv, topic_name);
	ros :: NodeHandle n;
	ros :: Subscriber des_vel = n . subscribe ( "des_vel" , refresh_rate);
	ros :: Subscriber laser_data = n . subscribe ( "robot0/laser_1", refresh_rate);
	ros :: Publisher cmd_vel_update = n . advertise ( "robot0/cmd_vel" , refresh_rate);

	//quick and dirty pseudocode:
	//have a while loop spinning at a certain rate
	//each timestep, have it check the distances around it and identify the minimum distance
		//get this info by subscribing to robot0/laser_1??
	//steer the robot away from the minimum distance
	//if no distances are below a minimum, continue straight
	//i.e. calculate velocity and heading??? look at stdr simulator code to figure out how
		//that works
	//note that cmd_vel is the linear velocity in XYZ, and then the angular velocity about
		//XYZ axes.
	//publish to "robot_0/cmd_vel"
	//?????
	ros::spin();
return 0;
}
