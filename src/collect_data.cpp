#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float64.h"
#include "iostream"
#include "joy_controller/Joymsg.h"
class PhidgetsController
{

   
    public:
        
        PhidgetsController();
        
        std_msgs::Float32 sensor_distance;
        std_msgs::Float64 vel_zero;
        std_msgs::Float64 vel_antes;
        std_msgs::Float64 vel_joystick;
        int dir_joystick;
     

        ros::NodeHandle n;
        ros::Publisher pub;
        ros::Subscriber sub;
        ros::Subscriber sub2;
  
        float obstacle_distance,var;
        
        
        
        
        void chatterCallback (const std_msgs::Float32::ConstPtr& msg)
        {   
            obstacle_distance = 7.5;
            vel_zero.data = 0.0;
            sensor_distance = *msg;
            
       
            if (sensor_distance.data >= obstacle_distance)
            {    
                if (vel_antes.data != vel_joystick.data)
                {
               
                    pub.publish(vel_joystick);
                }
             
                vel_antes.data=vel_joystick.data;
            }
           
    
            else 
            {
                if (vel_antes.data != vel_zero.data)
                {
               
                    pub.publish(vel_zero);
                }
                vel_antes=vel_zero;
                
    
            }    
    
        }
       
       
       
       
       
       
       void chatterCallbackjoy (const joy_controller::Joymsg::ConstPtr& msg)
        { 
            vel_joystick.data = msg->vel;    
            dir_joystick=msg->dir;
            vel_joystick.data = vel_joystick.data*dir_joystick; 
  
        }
  
              
};

PhidgetsController::PhidgetsController()
        {   
            vel_antes.data = 3.0;
            pub = n.advertise<std_msgs::Float64>("pan_controller/command", 10);
            sub2 = n.subscribe("joy_cmd", 1000, &PhidgetsController::chatterCallbackjoy, this);
            sub = n.subscribe("obstacle_distance", 1000, &PhidgetsController::chatterCallback, this);
              
        }


int main(int argc, char **argv)
{ 

  ros::init(argc, argv, "motor_control");

  PhidgetsController phid_control;
 
  //ros::Rate loop_rate(100);
  ros::spin();
  return 0;
}
 
