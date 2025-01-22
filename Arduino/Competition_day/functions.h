//Servo motors
#include<Servo.h>
Servo r1; Servo r2; Servo l1; Servo l2;
#define servo_r1 5   //forward - 
#define servo_r2 7   //forward -
#define servo_l1 4    //forward +
#define servo_l2 6   //forward +

// slonides
#define R_relay 10
#define L_relay 9

#define led 8 // for detection

//UltraSonic
#define C_Trig A1
#define C_Echo A2
#define C_vcc A0
#define C_gnd A3
#define R_Trig 51
#define R_Echo 53
#define R_vcc 49
#define L_Trig 22
#define L_Echo 24
#define L_gnd 26
float L_Distance, R_Distance, C_Distance;

//Color sensor
#define S0 31
#define S1 33
#define cled 35
#define Out 37
#define co_vcc 39
#define co_gnd 41
#define S2 43
#define S3  45
int Freq, Red, Green, Blue;
char Detected_Color;

#define start  A4 // start button

//raspi
#define rRH A5
#define rYS A6
#define rGU A7
#define rrp A9
#define lrp A10 
#define lRH A11
#define lYS A12 
#define lGU A13

//Gyro
#include <Wire.h> 
float GyroZ,angle, elapsedTime, currentTime, previousTime;
#define g_vcc 19
#define g_gnd 18

char reason='N'; //To stop the while
char rescue='N'; 
int rQu=6;
int lQu=6;
long C_Time=0;
long R_Time=0;

void Move(int L, int R , int T) 
{
        if(L>0){
              int sp=map(L,1,100,91,180);
              l1.write(sp);
              l2.write(sp);
               }
   else if(L<0){
              int sp=map(L,-1,-100,89,0);
              l1.write(sp);
              l2.write(sp);
               }
  else if(L==0){
              int sp=90;
              l1.write(sp);
              l2.write(sp);
               }
       if(R>0) {
              int rsp=map(R,1,100,89,0);
              r1.write(rsp);
              r2.write(rsp);
              }else if(R<0){
              int rsp=map(R,-1,-100,91,180);
              r1.write(rsp);
              r2.write(rsp);
               }
  else if(R==0){
              int rsp=90;
              r1.write(rsp);
              r2.write(rsp);
               }
              delay(T);             
}

void gyro()
{
  previousTime = currentTime;  
  currentTime = millis();         
  elapsedTime = (currentTime - previousTime) / 1000;
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 6, true);
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
  angle =  (angle + GyroZ * elapsedTime)+(elapsedTime*1.1);
}

void turn(float degree)
{
  int Speed =30;
  //degree=degree*0.97;
  gyro();
  float currentangle=angle;
        if(degree>0)
          {
           Move(Speed,-Speed,250);
           while((angle-currentangle)<degree)
            {
             gyro();
             Move(Speed,-Speed,10);
            }
           Move(0,0,1);
          }
  else if(degree<0)
         {
          degree=degree*-1;
          Move(-Speed,Speed,250);
          while((currentangle-angle)<degree)
           {
            gyro();
            Move(-Speed,Speed,10);
           }
          Move(0,0,1);
         }
}

float ultra()
{
  float Time;
  digitalWrite(L_Trig,1);
  delayMicroseconds(10);
  digitalWrite(L_Trig,0);
  Time = pulseIn(L_Echo, 1, 6070);
  L_Distance = Time * 0.034 / 2;
  digitalWrite(R_Trig,1);
  delayMicroseconds(10);
  digitalWrite(R_Trig,0);
  Time = pulseIn(R_Echo, 1, 6070);
  R_Distance = Time * 0.034 / 2;
  digitalWrite(C_Trig,1);
  delayMicroseconds(10);
  digitalWrite(C_Trig,0);
  Time = pulseIn(C_Echo, 1, 6070);
  C_Distance = Time * 0.034 / 2;

  if(L_Distance==0){L_Distance=50.00;}
  if(R_Distance==0){R_Distance=50.00;}
  if(C_Distance==0){C_Distance=50.00;}
}

void test_ultra()
{
 ultra();
 Serial.print(L_Distance);
 Serial.print("      ");
 Serial.print(C_Distance);
 Serial.print("      ");
 Serial.println(R_Distance);
}

void initiate_Gyro()
{
  pinMode(g_vcc, OUTPUT);
  pinMode(g_gnd, OUTPUT);
  digitalWrite(g_vcc, 1);
  digitalWrite(g_gnd, 0);
  delay(10);
  Wire.begin(); 
  delay(50);              
  Wire.beginTransmission(0x68);       
  Wire.write(0x6B);                  
  Wire.write(0x00);                 
  Wire.endTransmission(true);
}

void color()
{
//Setting red filtered photodiodes to be read
digitalWrite(S2,0);
digitalWrite(S3,0);
//Reading the output frequency
Red = pulseIn(Out, 0,6000);
if(Red==0){Red=6000;}
//Setting Green filtered photodiodes to be read
digitalWrite(S2,1);
digitalWrite(S3,1);
//Reading the output frequency
Green = pulseIn(Out, 0,6000);
if(Green==0){Green=6000;}
//Setting Blue filtered photodiodes to be read
digitalWrite(S2,0);
digitalWrite(S3,1);
//Reading the output frequency
Blue = pulseIn(Out, 0,6000);
if(Blue==0){Blue=6000;}
//Determine the color
if(Red>1600)                 { Detected_Color='B'; }
else if(Red>500&&Red<1000)  { Detected_Color='A'; }
else                         { Detected_Color='W'; }
}

void test_color()
{
  color();
  //Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(Red);//printing RED color frequency
  Serial.print("  ");
  //Printing the value on the serial monitor
  Serial.print("G= ");
  Serial.print(Green);
  Serial.print("  ");
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(Blue);
  Serial.println("  ");
  if      (Detected_Color=='B') { Serial.print("Black"); }
  else if (Detected_Color=='A') { Serial.print("Blue"); }
  else if (Detected_Color=='W') { Serial.print("White");}
}

void deploy(char where, int num)
{
  Move(0,0,1);
  for(int i=0; i<5; i++)
   {digitalWrite(led,1);delay(500);digitalWrite(led,0);delay(500);}  

   if(where=='r')
    {    
     if (num==2)
      {
       if (rQu>=2)
        {
         digitalWrite(R_relay,0);
         delay(250);
         digitalWrite(R_relay,1);
         delay(250);
         digitalWrite(R_relay,0);
         delay(250);
         digitalWrite(R_relay,1);
         delay(250);
         rQu=rQu-2;
        }
       else if(lQu>=2)
         {
          turn(180);          
          digitalWrite(L_relay,0);
          delay(250);
          digitalWrite(L_relay,1);
          delay(250);
          digitalWrite(L_relay,0);
          delay(250);
          digitalWrite(L_relay,1);
          delay(250); 
          lQu=lQu-2;
         }
       }  
 else if (num==1)
          {
            if (rQu>=1)
            {
            digitalWrite(R_relay,0);
            delay(250);
            digitalWrite(R_relay,1);
            delay(250);
            rQu=rQu-1;
            }else if(lQu>=1)
              {
          turn(180);          
          digitalWrite(L_relay,0);
          delay(250);
          digitalWrite(L_relay,1);
          delay(250); 
          lQu=lQu-1;
         }  
       } 
      }else if(where=='l')
         {
        if (num==2)
          {if (lQu>=2){
            digitalWrite(L_relay,0);
            delay(250);
            digitalWrite(L_relay,1);
            delay(250);
            digitalWrite(L_relay,0);
            delay(250);
            digitalWrite(L_relay,1);
            delay(250);
            lQu=lQu-2;
            }
            else if(rQu>=2){
            turn(-180);          
            digitalWrite(R_relay,0);
            delay(250);
            digitalWrite(R_relay,1);
            delay(250);
            digitalWrite(R_relay,0);
            delay(250);
            digitalWrite(R_relay,1);
            delay(250); 
            rQu=rQu-2;
               }  
                 }
   else if (num==1)
          {
            if (lQu>=1){
            digitalWrite(L_relay,0);
            delay(250);
            digitalWrite(L_relay,1);
            delay(250);
            lQu=lQu-1;
            }
            else if(rQu>=1){
            turn(-180);          
            digitalWrite(R_relay,0);
            delay(250);
            digitalWrite(R_relay,1);
            delay(250); 
            rQu=rQu-1;
                     } 
                 }
          } 
     Move(100,100,250);
     R_Time=millis();
}
void test_raspi(){
Serial.print(" rRH:");
Serial.print(digitalRead(A5));
Serial.print(" rYS:");
Serial.print(digitalRead(A6));
Serial.print(" rGU:");
Serial.print(digitalRead(A7));
Serial.print(" rrp:");// make it input
Serial.print(digitalRead(A9));
Serial.print(" lrp:");
Serial.print(digitalRead(A10));
Serial.print(" lRH:");
Serial.print(digitalRead(A11));
Serial.print(" lYS:");
Serial.print(digitalRead(A12));
Serial.print(" lGU:");
Serial.println(digitalRead(A13));
}

void setup() {
// Motors 
r1.attach(servo_r1);
r2.attach(servo_r2);
l1.attach(servo_l1);
l2.attach(servo_l2);

//ultrasonics
pinMode(L_Trig, OUTPUT);
pinMode(R_Trig, OUTPUT);
pinMode(C_Trig, OUTPUT);
pinMode(L_Echo, INPUT);
pinMode(R_Echo, INPUT);
pinMode(C_Echo, INPUT);
pinMode(R_vcc, OUTPUT);
pinMode(L_gnd, OUTPUT);
pinMode(C_vcc, OUTPUT);
pinMode(C_gnd, OUTPUT);
digitalWrite(R_vcc, 1);
digitalWrite(L_gnd, 0);
digitalWrite(C_vcc, 1);
digitalWrite(C_gnd, 0);

pinMode(led, OUTPUT);

pinMode(R_relay, OUTPUT);
pinMode(L_relay, OUTPUT);
digitalWrite(R_relay,1);
digitalWrite(L_relay,1);

//Color sensor
pinMode(Out, INPUT);
pinMode(S0, OUTPUT);
pinMode(S1, OUTPUT);
pinMode(S2, OUTPUT);
pinMode(S3, OUTPUT);
pinMode(cled, OUTPUT);
pinMode(co_vcc, OUTPUT);
pinMode(co_gnd, OUTPUT);
digitalWrite(S0, 1);
digitalWrite(S1, 0);
digitalWrite(cled, 1);
digitalWrite(co_vcc, 1);
digitalWrite(co_gnd, 0);

pinMode(start, INPUT_PULLUP);

//raspi
pinMode(rrp, OUTPUT);
pinMode(lrp, OUTPUT);
pinMode(rRH, INPUT);
pinMode(rYS, INPUT);
pinMode(rGU, INPUT);
pinMode(lRH, INPUT);
pinMode(lYS, INPUT);
pinMode(lGU, INPUT);

initiate_Gyro(); 

Serial.begin(9600);

while (digitalRead(start)==1)
  {
    Move(0,0,1);
  }
delay(500);

C_Time=millis();
R_Time=millis();

}
