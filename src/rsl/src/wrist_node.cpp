#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int16MultiArray.h"
#include "iostream"
#include "math.h"
#include <sstream>
//#include "leapmotion/leapros.h"
#include "Leap.h"

ros::Publisher pub_match;
std_msgs::Float32MultiArray position_wrist;
std_msgs::Int16MultiArray enable;
double pi = 3.14159, roll, motor_value, ang_max = 180, ang_min = -180, quad_max = 90, quad_min = -90;

void get_twist(const std_msgs::Float32MultiArray msg)
{
    Leap::Listener listenerSubclass;
    Leap::Controller controller; //= Controller();  
    
    Leap::Frame frame = controller.frame();
    Leap::Hand hand = frame.hands().frontmost();
    double rollRad = hand.palmNormal().roll();
    roll = (180*rollRad)/pi;
    if(-180 < roll && roll < 180)
    {
      std::cout<<"[ Angulo sendo impresso: "<<roll<<"º ]"<<"\n\n";
    }
    if (-90 < roll && roll < 90)
    {
      motor_value = fabs( 1 - (roll - (-90))/(90 - (-90)));
      position_wrist.data.push_back(motor_value);
      pub_match.publish (position_wrist);
      position_wrist.data.clear();
      ros::spin();
    }
  }
  

/*void match_twist(const std_msgs::Float32MultiArray)
{
  
}*/

int main(int argc, char **argv)
{
  ros::init(argc, argv, "match_Twist_node");
  ros::NodeHandle node;
  int var_enable = 1;
  enable.data.push_back(var_enable);
  ros::Publisher enable_motors = node.advertise<std_msgs::Int16MultiArray>("/enable_motors_wrist", 1000);
  enable_motors.publish(enable);
  //ros::Subscriber sub_match = node.subscribe("/NODE NAME", 1000, match_twist);
  pub_match = node.advertise<std_msgs::Float32MultiArray>("/position_wrist", 1000);
  
  while (ros::ok())
  {
    
    Leap::Listener listenerSubclass;
    Leap::Controller controller; //= Controller();  
    
    Leap::Frame frame = controller.frame();
    Leap::Hand hand = frame.hands().frontmost();
    double rollRad = hand.palmNormal().roll();
    roll = (180*rollRad)/pi;
    if(ang_min < roll && roll < ang_max)
    {
      std::cout<<"[ Angle: "<<roll<<"º ]"<<"\n\n";
    }
    if (quad_min < roll && roll < quad_max)
    {
      motor_value = fabs( 1 - (roll - (-90))/(90 - (-90)));
      position_wrist.data.push_back(motor_value);
      pub_match.publish (position_wrist);
      position_wrist.data.clear();
      
    }
  }
 
  
  return 0;
}