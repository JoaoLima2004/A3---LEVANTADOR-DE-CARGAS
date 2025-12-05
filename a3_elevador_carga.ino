#include <Arduino.h>
#define RPWM 25 
#define LPWM 26 
#define REN 27 
#define LEN 14 

#define SF1 34
#define SM 35
#define SF0 32 

bool Sens1, SensM, Sens0;
char TestaRx;
char Rx;

void ConfigPlaca()
{
  pinMode(RPWM,OUTPUT);  
  pinMode(LPWM,OUTPUT);  
  pinMode(REN,OUTPUT);  
  pinMode(LEN,OUTPUT); 
  analogWrite(RPWM,0);  
  analogWrite(LPWM,0);  
  digitalWrite(REN,1);  
  digitalWrite(LEN,1);  
  pinMode(SM,INPUT);
  pinMode(SF1,INPUT);
  pinMode(SF0,INPUT);
  Serial.begin(115200);
}
void VerificaSensor()
{
 Sens1 = digitalRead(SF1); 
 SensM = digitalRead(SM);
 Sens0 = digitalRead(SF0);
}
void RxData()
{
  if(Serial.available() > 0)
  {
    Rx = Serial.read();
    switch (Rx)
    {
    case 'U':
    TestaRx = 'U';
    break;
    case 'D':
    TestaRx = 'D';
    break;
    case 'P':
    TestaRx = 'P';
    break;
    }
    
  }
}

void ControleMotor()
{
  if(TestaRx == 'D' && digitalRead(SF1) == 1 && digitalRead(SM) == 0  && digitalRead(SF0) == 0)
    {
      analogWrite(RPWM,0);  
      analogWrite(LPWM,127); 
      Serial.println("Dn"); 
      Serial.print(Sens1);Serial.print(SensM);Serial.println(Sens0);    
    } 
 if(TestaRx == 'D' && digitalRead(SF1) == 0 && digitalRead(SM) == 1  && digitalRead(SF0) == 0)
    {
      analogWrite(RPWM,0);  
      analogWrite(LPWM,127); 
      Serial.println("Dn");  
      Serial.print(Sens1);Serial.print(SensM);Serial.println(Sens0);   
    } 

if(TestaRx == 'D' && digitalRead(SF1) == 0 && digitalRead(SM) == 0  && digitalRead(SF0) == 1)
    {
      analogWrite(RPWM,0);  
      analogWrite(LPWM,0); 
      Serial.println("Parado"); 
      Serial.print(Sens1);Serial.print(SensM);Serial.println(Sens0); 
    }
    
  if(TestaRx == 'U' && digitalRead(SF1) == 0 && digitalRead(SM) == 0  && digitalRead(SF0) == 1)
    {
      analogWrite(RPWM,127);  
      analogWrite(LPWM,0); 
      Serial.println("Up");  
      Serial.print(Sens1);Serial.print(SensM);Serial.println(Sens0); 
    } 
 if(TestaRx == 'U' && digitalRead(SF1) == 0 && digitalRead(SM) == 1  && digitalRead(SF0) == 0)
    {
      analogWrite(RPWM,127);  
      analogWrite(LPWM,0); 
      Serial.println("Up"); 
      Serial.print(Sens1);Serial.print(SensM);Serial.println(Sens0);  
    } 

if(TestaRx == 'U' && digitalRead(SF1) == 1 && digitalRead(SM) == 0  && digitalRead(SF0) == 0)
    {
      analogWrite(RPWM,0);  
      analogWrite(LPWM,0); 
      Serial.println("Parado"); 
      Serial.print(Sens1);Serial.print(SensM);Serial.println(Sens0);   
    }
if(TestaRx == 'P')
{
      analogWrite(RPWM,0);  
      analogWrite(LPWM,0); 
      Serial.println("Parado");  
      Serial.print(Sens1);Serial.print(SensM);Serial.println(Sens0); 
}
}

void setup() 
{
  ConfigPlaca();
}

void loop() 
{
 VerificaSensor();
 RxData();
 ControleMotor();
}

