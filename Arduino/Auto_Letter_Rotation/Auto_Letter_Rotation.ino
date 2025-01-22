#include <Servo.h>

// create servo objects to control a servo
Servo lServo;  
Servo rServo;   

void setup() 
{
  // attach the left servo on pin 3
  lServo.attach(3);  
  // attach the right servo on pin 5
  rServo.attach(5);
}

void loop() 
{
lServo.write(120);
rServo.write(86);
}
