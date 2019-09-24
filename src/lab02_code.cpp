#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream> //I don't know what sstream is for but I had it earlier so I'm gonna keep it
#include <stdlib.h>
#include <string> //so that I can pass topic names as an argument as a string
#include "geometry_msgs/Twist.h" //different topics to include
#include "sensor_msgs/LaserScan.h"


//"global" variables:
float lin_vel = 0;
float ang_vel = 0;
std::vector<float> laser_data;

void LaserCallback(const sensor_msgs::LaserScan::ConstPtr& msg){
	laser_data = msg-> ranges;
	//ROS_INFO("Laser data received!\n");
	//This is working
}

void VelocityCallback(const geometry_msgs::Twist::ConstPtr& msg){
	lin_vel = msg->linear.x;
	ang_vel = msg->angular.z;
	//ROS_INFO("Desired Velocities are: linear: [%f]\n angular: [%f]\n", lin_vel, ang_vel);
	//This is working
}

int main(int argc, char **argv){

	ros::init(argc, argv, "lab02_package_node"); //does this have to match name of node in CMakeLists.txt?
	ros::NodeHandle handle;

	ROS_INFO("Main Node started!!\n");

//------------------------------------------------------------------------------------------
	//accepting the topic name as an argument. Copied from the assignment sheet
	int opt;
	char* topic_name;
	while ((opt = getopt(argc, (argv), "n:")) != -1){
		switch(opt){
			case 'n':
				topic_name = optarg;
				break;
			default:
				printf("The -%c is not a recognized parameter.\n", opt);
				break;
		}
	}



//-------------------------------------------------------------------------------------------	
	//"subscribe" notes:

	//subscribe() is how you tell ROS you wanna receive messages on a given topic
	//subscribe() returns a subscriber object that you hold on to until you want to unsubscribe
	//Messages are passed to the callback function
	//first argument - name of topic to subscribe to
	//second argument - size of message queue
	//third argument - name of callback function to call
	ros::Subscriber vel_sub = handle.subscribe("des_vel", 1, VelocityCallback);
	//ROS_INFO ("Handle for des_vel Subscription set!\n");
		//ros::Subscriber is like the variable type (like when you type "int x = 5;").
		//"hand;e" is the node handle we created above
		//subscribe() is a function (included in ros.h or something)
		//"vel_sub" = "velocity subscription"
	ros::Subscriber las_sub = handle.subscribe("/robot0/laser_1", 1, LaserCallback);
	//ROS_INFO ("Handle for laser data subscription set!\n");
		//"las_sub" = "laser subscription"
		//MODIFY THIS CALL FOR IF THERE IS MORE THAN ONE ROBOT IN THE SIMULATION??
//-------------------------------------------------------------------------------------------	
	//"publish" notes:
	
	//advertise() function tells ros to publish on a given topic.
	//advertise() returns a Publisher object which allows you to publish MESSAGES on a TOPIC by calling publish()
	//argument in <> tags is the message type. Note that you use :: instead of /
	//second argument to advertise is the name of the topic you are publishing to
	//third argument is size of message queue
	ros::Publisher vel_pub = handle.advertise<geometry_msgs::Twist>(topic_name, 1);
	//ROS_INFO("Published to robot0/cmd_vel!\n");
		//again, ros::Publisher is the variable type
		//"handle" is the nodehandle from earlier
		//advertise is a function. I guess you can have function<one_arg>(another_arg) in CPP?? idk
		//"vel_pub" = "velocity publish"
//-----------------------------------------------------------------------------------------
	//"spin" notes

	//ros::spin() will enter a loop, pumping callbacks. Will exit w ctrl+C, or shutdown by master.
	//ros::spin(); DON'T USE THIS
	ros::Rate loop_rate(10); //the loop rate is 10Hz

//-----------------------------------------------------------------------------------------
	//messages to be published

	//with publish() function. The paramater is the message object (in this case called "message")
	//must have same type as advertise<>() call earlier

	while (ros::ok()){ //while the node is running?
		geometry_msgs::Twist message;
		//ROS_INFO("Message created!\n");
			//creates a variable of type "geometry_msgs/Twist" called "message."
		message.linear.x = lin_vel;
		message.angular.z = ang_vel;
			//"message" is formatted this way to conform with the type geometry_msgs/Twist
			//recall that we included geometry_msgs/Twist in our header
		if(lin_vel > 0 && laser_data [270/2] < 2){
			//PUT MORE CODE HERE ABOUT HOW TO AVOID STUFF
			message.linear.x = 0;
			ROS_INFO("Robot stopped!\n");
		}
		vel_pub.publish(message);
		//ROS_INFO("Published to robot0/cmd_vel!\n Desired velocity = [%f]\n", lin_vel);
		ros::spinOnce();
		loop_rate.sleep();
		/* OKAY SO, WHEN YOU USE RQT_GUI to update des_vel, I get an error that says
		[lab02_node_main] process has died. IDK why */
		//I know why now, I forgot to put rqt_gui in the build dependencies in package.xml

	}
	return 0;
}//end of 'main' function
