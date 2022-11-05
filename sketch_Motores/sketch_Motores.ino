

#define pinMot1A 5
#define pinMot1B 6
#define pinMot2A 9
#define pinMot2B 10

#define velocidade 100


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  pinMode(pinMot1A, OUTPUT);
  pinMode(pinMot1B, OUTPUT);
  pinMode(pinMot2A, OUTPUT);
  pinMode(pinMot2B, OUTPUT);
  
  pinMode(3, OUTPUT);
  analogWrite(3, velocidade);
}

void loop() {
 
      if(Serial.available()>0){
        char c = Serial.read();
        if(c == 'A'){
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
        Serial.println("motores on");
     
        }
      }
     
   
 

}
