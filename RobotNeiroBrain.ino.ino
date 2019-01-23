#include "pin_config.h"
#include "Sensor.h"
#include "motor.h"
#include "Bamp.h"
#include "Start.h"
int rez =0;
int trurezult[5];

float output;
int rezult =0;
int In;
float Error;
float w[11][7];
float NeiroSum[6];
int NeiroIn; 
float NeiroOut[4][6];
int net=0;
float ErrorG;

float Lerning = 0.8;
int Set = 1 ;
int q = 1;
const uint8_t distansStop = 30;// Дистанция до препядствия в сантиметрах при которой робот едет назад и на право


void setup() {
SensorIn();
MotorIn();
SensorDistans();
IntStart();
Serial.begin(9600);
}


void IntStart(){
   for(int i=0;i<5;i++){
    int j = 5;
     for(int p=0;p<4;p++){
    w[i][p] +=0.1;
    w[j][p] +=0.1;
    }
    j++;
  }
    }
long Start(){  
long In = SensorDistans();

  NeiroIn = In;

 //-------------------------------------------------------------------
//Cумируем веса 1го слоя в перменную NeiroSum[n] где [1]сумма(вход) первого нейрона, [2]сумма(вход) 2го нейрона итд.
//Serial.println("Cумируем веса 1го слоя");
 
   
  for(int i=0;i<5;i++){
    NeiroSum[i] += w[0][i]*NeiroIn;
    } 


// Serial.println("Сохраняем результат первого слоя");
  for(int n =0;n<5;n++){
    NeiroOut[1][n] =1/(1+exp(-NeiroSum[n]));
   
}
//-----------------------------------------------------------------------
//Сохранили результат первого слоя в переменной Neiro1Out[n] где [1]выход первого нейрона, [2]выход 2го нейрона итд.

// for(int n =0;n<3;n++){
//Serial.print("Результат первого слоя");Serial.print(n);Serial.print("  ");
//Serial.println(NeiroOut[1][n] );
// }
 // Очищаем переменную NeiroSum[n]
 for(int i = 0;i<5;i++){
 NeiroSum[i] = 0 ;
 }
//------------------------------------------------------------------------
//Cумируем веса 2го слоя в перменную NeiroSum[n] где [1]сумма(вход(Neiro1Out[1])) первого нейрона, [2]сумма(вход(Neiro1Out[2])) 2го нейрона итд.
//Serial.println("Cумируем веса 2го слоя");
for(int n =1;n<6;n++){
net=0;
  for(int i=0;i<5;i++){
    NeiroSum[net] += w[n][i]*NeiroOut[1][i];
    } net++;
    }
    net=0;
 //----------------------------------------------------------------------
 for(int n =0;n<5;n++){
    NeiroOut[2][n] =1/(1+exp(-NeiroSum[n]));
 
  //Serial.print("Результат 2го слоя");Serial.print(n);Serial.print("  ");
//Serial.println(NeiroOut[2][n]);
 }
 //------------------------------------------------------------------------
//Сохранили результат 2го слоя в переменной Neiro2Out[n] где [1]выход первого нейрона, [2]выход 2го нейрона итд.
 // Очищаем переменную NeiroSum[n]
for(int i = 0;i<5;i++){
 NeiroSum[i] = 0 ;
 }
//------------------------------------------------------------------------
//Cумируем веса 3го слоя в перменную NeiroSum[n] где [1]сумма(вход(Neiro2Out[1])) первого нейрона, [2]сумма(вход(Neiro1Out[2])) 2го нейрона итд.   
  for(int n =6;n<9;n++){
    net=0;
  for(int i=0;i<5;i++){
    NeiroSum[net] += w[n][i]*NeiroOut[2][i];
    } net++;
    } net=0;
//-------------------------------------------------------------------------------
 for(int n =0;n<3;n++){
    NeiroOut[3][n] =1/(1+exp(-NeiroSum[n]));
  
 Serial.print("Результат 3го слоя");Serial.print(n);Serial.print("  ");
Serial.println(NeiroOut[3][n]);
 }
 //------------------------------------------------------------------------
 //Сохранили результат 3го слоя в переменной Neiro2Out[n] где [1]выход первого нейрона, [2]выход 2го нейрона итд.
 // Очищаем переменную NeiroSum[n]
for(int i = 0;i<5;i++){
 NeiroSum[i] = 0 ;
 }
  
   //------------------------------------------------------------------------
if(NeiroOut[3][0]=NeiroOut[3][1]){
 rezult= 1;
    }if(NeiroOut[3][0]>NeiroOut[3][1]){
      rezult= 2;
    }if(NeiroOut[3][0]<NeiroOut[3][1]){
      rezult= 3;
    }if(NeiroOut[3][2]>0.8){
      rezult= 4;
    }

    return rezult; 
}

void WesCor(){

float sigmoid_dx;
float Sdvig;

//Вычисляем ошибку и меняем веса 3го слоя
for(int i =0;i<3;i++){
  int y= 6;
Error = trurezult[i] - NeiroOut[3][i];
for(int q = 0;q<5;q++){
sigmoid_dx = NeiroOut[2][q] *(1- NeiroOut[2][q]);
Sdvig= Error * sigmoid_dx;

  w[y][q] = w[y][q] - Sdvig* Lerning;
}y++;
}
//Вычисляем ошибку и меняем веса 2го слоя i го нейрона
for(int i=0;i<5;i++){
  int j =1;
   sigmoid_dx = NeiroOut[1][i]*(1- NeiroOut[1][i]);
   for(int l=0;l<5;l++){
   Error = w[j][l]*Sdvig;
   Sdvig = Error * sigmoid_dx;
   w[j][l] = w[j][l] - Sdvig * Lerning;
}
j++;
}
//Вычисляем ошибку и меняем веса 1го слоя iго нейрона


sigmoid_dx = NeiroIn*(1- NeiroIn);
   for(int l=0;l<5;l++){
   Error = w[0][l]*Sdvig;
   Sdvig = Error * sigmoid_dx;
   w[0][l] = w[0][l] - Sdvig * Lerning;
}


}





void loop() {

long sm = SensorDistans();
 Serial.print("sm ");  Serial.print(" ");Serial.println(sm);
 long rez =Start();
 if( sm < distansStop ){
          trurezult[0] = 0;
          trurezult[1] = 1;
          trurezult[2] = 1;
          MotorLeftBakcward();
       MotorRightBakcward();
        }
 if( sm > 150){
          trurezult[0] = 1;
          trurezult[1] = 1;
          trurezult[2] = 0;
}


  //const uint8_t bampClikc = 0;// Если есть бампер выключить
  //Serial.println(sm, DEC);
    
   if ( rez = 1) {
      Serial.println("вперед");
      MotorRightForward();\]
      MotorLeftForward();
      delay(40);
   }if ( rez = 2) { 
    Serial.println("Правое колесо назад");
     MotorRightBakcward();
     MotorLeftForward();
      delay(50);
     trurezult[0] = 1;
     trurezult[1] = 0;
    
    }if ( rez = 3) { 
    Serial.println("Левое колесо назад");
     MotorRightForward();
     MotorLeftBakcward();
      delay(40);
     trurezult[0] = 0;
     trurezult[1] = 1;
    }if (rez = 4) {
      Serial.println("Назад");
       MotorLeftBakcward();
       MotorRightBakcward();
      delay(40);
      }
   
        
        
       WesCor();
    
}
  




