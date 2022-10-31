
#include "Wire.h"

#define meuEnd 0x100


#define pinMot1A 5
#define pinMot1B 6
#define pinMot2A 9
#define pinMot2B 10

#define velocidade 100



void setup() {
  // put your setup code here, to run once:

  Wire.begin(meuEnd);
  Wire.onReceive(receptor);

  Serial.begin(9600);
  
  pinMode(pinMot1A, OUTPUT);
  pinMode(pinMot1B, OUTPUT);
  pinMode(pinMot2A, OUTPUT);
  pinMode(pinMot2B, OUTPUT);
  
  pinMode(3, OUTPUT);
  analogWrite(3, velocidade);
}

void loop() {
  }

void receptor(int quantidade ) {

  if(Wire.available()){
    char recebido = Wire.read();

    if(recebido == "rf" && recebido == "ult"){ 
      
      digitalWrite(pinMot1A, HIGH);
      delay(2000);
      digitalWrite(pinMot1A, LOW);
    
      digitalWrite(pinMot2A, HIGH);
      delay(2000);
      digitalWrite(pinMot2A, LOW);
    
      digitalWrite(pinMot1B, HIGH);
      delay(2000);
      digitalWrite(pinMot1B, LOW);
    
      digitalWrite(pinMot2B, HIGH);
      delay(2000);
      digitalWrite(pinMot2B, LOW);
    }
  }

}
