#include "Servo.h"

Servo headHor;
Servo headVer;

int pos = 0;  

void headIn() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  headHor.attach(4); 
  headVer.attach(5);
  SensorIn();
}

long HeadLeftRight() {
int angle = 98;
 long dist = SensorDistans();
  headVer.write(60);
 for (pos = 15; pos <= 25; pos += 1) { 
  headHor.write(pos); 
  delay(2);}
 if(dist>30){
   angle = 25;
 return angle;
 }else{
   for (pos = 25; pos <= 35; pos += 1) { 
    headHor.write(pos);           
delay(2); 
}
if(dist>30){
   angle = 35;
 return angle;

}else{
    for (pos = 35; pos <= 45; pos += 1) { 
    headHor.write(pos);           
delay(2); 
}
 if(dist>30){ angle = 45;
 return angle; 
 }else{
headHor.write(90);
angle = 25;
return angle;
}
}


void Head0(){
headHor.write(100);
headVer.write(70);
}
