#include <Wire.h>

int camTensorLog = A5;
int GPSPin = 3;
int microTensorLog = A4;
int hautParleurPin = 5;
int ledPin = 6;
int camData;
int GPSData;
float microData;

String inputString = "";
boolean lowBatteryTest = false;
boolean baladeModeTest = false;

int timerLed = 0;
int timerInformation = 0;

void lowBattery()
{
  if(inputString == "high battery"){
  	digitalWrite(ledPin, LOW);
    lowBatteryTest = false;
  }else{
    if(timerLed >= 100){	
      if(digitalRead(ledPin) == HIGH){digitalWrite(ledPin, LOW);}
      else{digitalWrite(ledPin, HIGH);}
      timerLed = 0;
    } 
  } 
}

void baladeMode()
{
  if(inputString == "stop balade"){
    baladeModeTest = false;
  }else{
    if(timerInformation >= 500){
      camData = analogRead(camTensorLog);
      GPSData = digitalRead(GPSPin);
      microData = analogRead(microTensorLog);

      Serial.print("Recuperation et envoi de l'audio, taille: ");
      Serial.print(microData);
      Serial.println(" Ko"); 

      Serial.print("Recuperation et envoi de l'image, taille: ");
      Serial.print(camData);
      Serial.println(" Ko"); 
      
      Serial.print("Recuperation et envoi du GPS, taille: ");
      Serial.print(GPSData);
      Serial.println(" Ko"); 
      timerInformation = 0;
  	}
  } 
}


void soundSetup(){tone(hautParleurPin,1020,100);}


void setup()
{
  pinMode(GPSPin, INPUT); 
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
	
  inputString = Serial.readString(); 
  
  if(inputString == "low battery"){lowBatteryTest = true;}
  if(lowBatteryTest == true){lowBattery();}
  
  if(inputString == "go balade"){baladeModeTest = true;}
  if(baladeModeTest == true){baladeMode();}
  
  if(inputString == "synchronized" || inputString == "deSynchronized"){
    soundSetup();
  }
  	
  
  timerLed += millis();
  timerInformation += millis();
}