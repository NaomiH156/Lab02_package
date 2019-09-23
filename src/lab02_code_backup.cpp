#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <stdlib.h> //this one is from the canvas site as well
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "stdr_simulator/robot0/cmd_vel.h"

// some "global" variables
float lin_vel = 0;
float ang_vel = 0; //linear and angular velocity
std::vector<float> lidar_data;
	//LIDAR data is a vector


//Please be nice to me Dr. Lee i have 0 idea what i am doing - Naomi Hourihane

//write a callBackFunction up here

int main(int argc, char **argv){

	ROS_INFO("Node has started!!\n");
	
	int refresh_rate = 1000;
	ros :: init(argc, argv, topic_name);
	ros :: NodeHandle handle;
	ros :: Subscriber des_vel = handle . subscribe ( "des_vel" , refresh_rate, callBackFunction);
	ros :: Subscriber laser_data = handle . subscribe ( "robot0/laser_1", refresh_rate, callBackFunction);
	ros :: Publisher cmd_vel_update = handle . advertise ( "robot0/cmd_vel" , refresh_rate);


	
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
