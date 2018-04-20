# phidgets_project
Control a motor using a Phidgets IR Sensor and a Joystick

How it works
-----------

The motor is controlled by a joystick in normal operation. The IR sensor SHARP 0A41SK is monitoring obstacles all the time, when an obstacle is detected the joystick looses the motor control and a stop command is sent to the motor. 

Hardware: 
----------

* SHARP 0A41SK is connected to Phidgets through a Phidgets IR Adapter.
* Phidgets, Joystick and Dynamixel are connected to the computer through a USB Port


What you need before running it
-----------------------------------

Phidgets library: https://www.phidgets.com/docs/OS_-_Linux

Phidgets Python module: https://www.phidgets.com/docs/Language_-_Python

joy_controller package: https://github.com/brschettini/joy_controller

dynamixel_controller package: http://wiki.ros.org/dynamixel_controllers/Tutorials/ConnectingToDynamixelBus

Run it !
------------------------------
Open the terminal and type:

```
roslaunch phidgets_project joy_phid_controller.launch
```

