#!/usr/bin/env python
# license removed for brevity
import rospy
import sys
import time 
from std_msgs.msg import Float32
from Phidget22.Devices.VoltageInput import *
from Phidget22.PhidgetException import *
from Phidget22.Phidget import *
from Phidget22.Net import *

try:
    pub = rospy.Publisher('obstacle_distance', Float32, queue_size=10)
    rospy.init_node('phidgets_sharp', anonymous=True)
    ch1 = VoltageInput()
   
   
except RuntimeError as e:
    print("Runtime Exception %s" % e.details)
    print("Press Enter to Exit...\n")
    readin = sys.stdin.read(1)
    exit(1)

def VoltageInputAttached(self):
    try:
        attached = self
        print("\nAttach Event Detected (Information Below)")
        print("===========================================")
        #print("Library Version: %s" % attached.getLibraryVersion())
        #print("Serial Number: %d" % attached.getDeviceSerialNumber())
        print("Channel: %d" % attached.getChannel())
        print("Channel Class: %s" % attached.getChannelClass())
        print("Channel Name: %s" % attached.getChannelName())
        print("Device ID: %d" % attached.getDeviceID())
        #print("Device Version: %d" % attached.getDeviceVersion())
        print("Device Name: %s" % attached.getDeviceName())
        print("Device Class: %d" % attached.getDeviceClass())
        print("\n")
        
        
    except PhidgetException as e:
        print("Phidget Exception %i: %s" % (e.code, e.details))
        print("Press Enter to Exit...\n")
        readin = sys.stdin.read(1)
        exit(1)   
        
        

    
def VoltageInputDetached(self):
    detached = self
    try:
        print("\nDetach event on Port %d Channel %d" % (detached.getHubPort(), detached.getChannel()))
    except PhidgetException as e:
        print("Phidget Exception %i: %s" % (e.code, e.details))
        print("Press Enter to Exit...\n")
        readin = sys.stdin.read(1)
        exit(1)   


        
def ErrorEvent(self, eCode, description):
    print("Error %i : %s" % (eCode, description))

def VoltageChangeHandler(self, voltage):
    #print("Voltage1: %f" % voltage)
    dist=519/((voltage*50)+(11/4))
    pub.publish(dist)
  

def SensorChangeHandler(self, sensorValue, sensorUnit):
    print("Sensor Value: %f" % sensorValue)

try:
    ch1.setOnAttachHandler(VoltageInputAttached)
    ch1.setOnDetachHandler(VoltageInputDetached)
    ch1.setOnErrorHandler(ErrorEvent)
    ch1.setOnVoltageChangeHandler(VoltageChangeHandler)
    ch1.setOnSensorChangeHandler(SensorChangeHandler)
    
    print("Waiting for the Phidget VoltageInput Object to be attached...")
    ch1.openWaitForAttachment(5000)
    
except PhidgetException as e:
    print("Phidget Exception %i: %s" % (e.code, e.details))
    print("Press Enter to Exit...\n")
    readin = sys.stdin.read(1)
    exit(1)

print("Gathering data for 100 seconds...")

#time.sleep(100)
while True: pass



try:
    ch1.close()
    
except PhidgetException as e:
    print("Phidget Exception %i: %s" % (e.code, e.details))
    print("Press Enter to Exit...\n")
    readin = sys.stdin.read(1)
    exit(1) 
print("Closed VoltageInput device")
exit(0)



