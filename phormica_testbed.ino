
/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */

/* LEDs includes and Global variables */
#include <Wire.h>
#include <lp55231.h>

Lp55231 ledChip;

/* Motor includes and Global variables */
#include <Servo.h>

Servo servo; 

/* ROS includes and Global variables */
#include <ros.h>
#include <std_msgs/Bool.h>

ros::NodeHandle  nh;

/* Global variables */

bool isMovingToEnd  = false;
bool isMovingToInit = false;

/* ROS callback functions */

void messageControl( const std_msgs::Bool& scan_control)
{
  if (scan_control.data == true)
  {
    int stopInit = digitalRead(13);
    int stopEnd  = digitalRead(12);
    
    if (stopEnd == HIGH && stopInit == HIGH)
    {
      set_leds(0);
      servo.write(72); 
      isMovingToEnd  = false;  
      isMovingToInit = true;
     }
    else if (stopEnd == LOW && stopInit == HIGH)
    {
      set_leds(0);
      servo.write(72);
      isMovingToEnd  = false;  
      isMovingToInit = true;  
    }
    else if (stopEnd == HIGH && stopInit == LOW)
    {
      set_leds(255);
      servo.write(112);
      isMovingToEnd  = true;  
      isMovingToInit = false;  
    }  
  }
  else
  {
    servo.write(92);
    set_leds(0);
    isMovingToEnd  = false;  
    isMovingToInit = false;
  } 
}

/* ROS suscribers and publishers */

ros::Subscriber<std_msgs::Bool> subControl("arduino_control", messageControl );

/* Init configuration */

void setup()
{
  nh.initNode();
  nh.subscribe(subControl);

  ledChip.Begin();
  ledChip.Enable();

  servo.attach(9);

  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  set_leds(0);
  servo.write(92);

  delay(500); 
}

/* Control loop */

void loop()
{  
  nh.spinOnce();
  
  if(isMovingToInit == true)
  {
    int stopInit = digitalRead(13);
    if (stopInit == LOW)
    {
      servo.write(92);
      set_leds(0);      
      isMovingToInit == false;
    }
  }
  
  if(isMovingToEnd == true)
  {
    int stopEnd = digitalRead(12);
    if (stopEnd == LOW)
    {
      servo.write(92);
      set_leds(0);      
      isMovingToEnd == false;
    }
  }
  delay(100);
}

/* Auxiliary functions */

void set_leds(int inPWM)
{  
  ledChip.SetChannelPWM(0, inPWM);
  ledChip.SetChannelPWM(1, inPWM);
  ledChip.SetChannelPWM(2, inPWM);
  ledChip.SetChannelPWM(3, inPWM);
  ledChip.SetChannelPWM(4, inPWM);
  ledChip.SetChannelPWM(5, inPWM);
  ledChip.SetChannelPWM(6, inPWM);
  ledChip.SetChannelPWM(7, inPWM);
  ledChip.SetChannelPWM(8, inPWM);
}
