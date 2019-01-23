

#include "pin_config.h"

void SensorIn() {
pinMode(Trig, OUTPUT); // выход
pinMode(Echo, INPUT); // вход
}
long SensorDistans(){

digitalWrite(Trig, HIGH);
delayMicroseconds(10); // 10 микросекунд
digitalWrite(Trig, LOW);
 long impulseTime = pulseIn(Echo, HIGH); // замеряем длину импульса
 long distans = impulseTime/58; // переводим в сантиметры

return distans;
}
