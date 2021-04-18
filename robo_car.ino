#include <Servo.h>
Servo myservo;
int in1=9;
int in2=10;
int in3=11;
int in4=12;
int readvalue;
int timerotate=800;
int l1=4;
int l2=5;
int l3=6;
int trig=8;
int echo=13;
int duration,randomnumber;
float distance;
int switch_direc=0;
int angle,limit=20;
int brush=7;
int servo=3;
int i=0;
void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(l1,OUTPUT);
  pinMode(l2,OUTPUT);
  pinMode(l3,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(brush,OUTPUT);
  myservo.attach(servo);
  pinMode(servo,OUTPUT);

  
  
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0)
  {
    readvalue=Serial.read();
    Serial.println(readvalue);
    
    switch(readvalue)
    {
      case 3: case 2://forward
     
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      break;
      case 150: case 134: case 149: case 148: case 132: case 144: case 20://right
     
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      break;
      case 7: case 6: case 4://reverse
     
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      break;
      case 253: case 252: case 241: case 224: case 249://left
      
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      break;
      case 120: case 119: case 112:// turn right and stop
      right_stop();
      break;
      
      case 200: case 199: case 192://turn left and stop
      left_stop();
      break;
      
      case 1: case 0://error in module 
      break;
      case 51: case 50: case 48: case 35://lights on
      digitalWrite(l1,HIGH);
      digitalWrite(l2,HIGH);
      digitalWrite(l3,HIGH);
      break;
      case 40: case 39: case 32://lights off
      digitalWrite(l1,LOW);
      digitalWrite(l2,LOW);
      digitalWrite(l3,LOW);
      break;
      case 90: case 89: case 82: case 88: case 66: case 80: case 26://Automatic
 while(Serial.read()!=15 || Serial.read()!=12 || Serial.read()!=14)
 {

                    if(i==180)
                    switch_direc=1;
                    if(i==0)
                    switch_direc=0;
                    myservo.write(i);
                    angle=myservo.read();
                    distance=caldistance();
                    if(distance<limit)//If there is any obstacle
                        {
                            if(angle>90)
                            right_stop();
                            else
                            left_stop();
                         }
                    else//If no obstacle move forward
                    {      digitalWrite(in1,HIGH);
                           digitalWrite(in2,LOW);
                           digitalWrite(in3,HIGH);
                           digitalWrite(in4,LOW);
                    }
                
              if(switch_direc==1)
              i-=1;
              else
              i+=1;
 }
 break;
 
 case 183: case 167: case 166: case 180: case 182: case 164: case 135://Brushes on
 digitalWrite(brush,HIGH);
 break;
 case 78: case 76: case 72://Brushes off
 digitalWrite(brush,LOW);
 break;
      
      default://stop
     
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      break;
    }
  }
  delayMicroseconds(50);
}
float caldistance()
{ float fdistance;
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  fdistance=(duration*0.0343)/2;
  return fdistance;
}
void right_stop()
{      
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      delay(timerotate);
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
     }
void left_stop()
{      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      delay(timerotate);
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      }
