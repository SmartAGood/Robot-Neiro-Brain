#include "pin_config.h"

void MotorIn(){
pinMode(in1, OUTPUT); // выход на L298n
pinMode(in2, OUTPUT); // выход на L298n
pinMode(in3, OUTPUT); // выход на L298n
pinMode(in4, OUTPUT); // выход на L298n
}
void MotorLeftForward(){
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
}
void MotorLeftBakcward(){
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
}
void MotorRightForward(){
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
}
void MotorRightBakcward(){
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}
void MotorStop() {
  digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
}

