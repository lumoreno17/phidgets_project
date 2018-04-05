#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "iostream"
#include "phidgets_project/JoyPhid.h"
class Luciana
{

   
    public:
        
        Luciana();
        
        std_msgs::Float32 value;
        
        phidgets_project::JoyPhid joyphid;
   
    
        phidgets_project::JoyPhid y;
        ros::NodeHandle n;
        ros::Publisher pub;
        ros::Subscriber sub;
        ros::Subscriber sub2;
  
        float set_dist;
        int count;
        
        
        
        void chatterCallback (const std_msgs::Float32::ConstPtr& msg)
        { 
            value = *msg;
              std::cout <<value.data << "  - else\n";
    
        }
       
       
       
       
       
       
       void chatterCallbackjoy (const phidgets_project::JoyPhid::ConstPtr& msg)
        { 
            y.vel=0;
            y.dir=1;
            
            joyphid = *msg;
            set_dist=7.5;
              
            ROS_INFO("[%d]",count); 
            if (value.data >= set_dist)
            {    
                pub.publish(joyphid);
                count=1;
                std::cout << "if\n";
        
            }
            
    
            else
            {
                pub.publish(y);
                count=0;
                ROS_INFO("HERE");
                
            }      
  
       }
  
              
};

Luciana::Luciana()
        {   
           
            pub = n.advertise<phidgets_project::JoyPhid>("motor_topic", 10);
            sub = n.subscribe("obstacle_distance", 1000, &Luciana::chatterCallback, this);
            sub2 = n.subscribe("joy_cmd", 1000, &Luciana::chatterCallbackjoy, this);
            
        }


int main(int argc, char **argv)
{ 

  ros::init(argc, argv, "motor_control");

  Luciana l;
 
  //ros::Rate loop_rate(100);
  ros::spin();
  return 0;
}
 
