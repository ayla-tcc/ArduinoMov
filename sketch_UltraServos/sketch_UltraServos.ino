/*TCC parte movimento*/


#include <NewPing.h> //Biblioteca para o sensor ultrassonico
#include <Servo.h> //Biblioteca para o servo motor

#include "Wire.h"

#define EndMotor 0x100

int ult = 1;




//#define velocidade 100

//Esses pinos são conectados do A0 ao A3 respectivamente, utilizamos desse metodo devido a falta de portas digitais 
#define pinServo1A A0 //Utilizamos o servo para rotacionar o sensor ultrassonico, assim tendo um maior campo de visão, sendo A na parte frontal
#define pinServo2A A1 //Utilizamos o servo para rotacionar o sensor ultrassonico, assim tendo um maior campo de visão, sendo A na parte frontal  
#define pinServo3B A2 //Utilizamos o servo para rotacionar o sensor ultrassonico, assim tendo um maior campo de visão, sendo B na parte de tras  
#define pinServo4B A3 //Utilizamos o servo para rotacionar o sensor ultrassonico, assim tendo um maior campo de visão, sendo B na parte de tras  

//Parte referentes ao sensor ultrassonico  
#define SONAR_NUM     4  //Define o numero de sensores utilizados 
#define MAX_DISTANCE 200 //Maxima distancia (em cm)
#define PING_INTERVAL 33 //Milissegundos entre os pings do sensor (29ms é aproximadamente o minuto para evitar eco cruzado do sensor).

unsigned long pingTimer[SONAR_NUM]; //Armazena os horários em que o próximo ping deve ocorrer para cada sensor.
unsigned int cm[SONAR_NUM];         //Onde as distâncias de ping são armazenadas.
uint8_t currentSensor = 0;          //Mantém o controle de qual sensor está ativo.

NewPing sonar[SONAR_NUM] = {     //Matriz de objetos do sensor, "um varal" com os sensores
  NewPing(13, 12, MAX_DISTANCE), //Configura o sensor, pino e distancia maxima).
  NewPing(11, 8, MAX_DISTANCE),   //Configura o sensor, pino e distancia maxima).
  NewPing(7, 4, MAX_DISTANCE),   //Configura o sensor, pino e distancia maxima).
  NewPing(3, 2, MAX_DISTANCE),   //Configura o sensor, pino e distancia maxima). 
};
 
 void echoCheck() {                                                           //Se o ping for recebido, defina a distância do sensor para array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}


   

void oneSensorCycle() {                          //Ciclo de ping do sensor completo, faça algo com os resultados.
                                                 //O código a seguir seria substituído pelo seu código que faz algo com os resultados do ping.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.print("cm ");
  }
  //Serial1.println();
}
Servo serv1,serv2,serv3,serv4; // nomeia os servos

int angulo = 0; // Ajusta o ângulo inicial do Servo 



void setup() {

  
  
  // atribui pinos dos servos
  serv1.attach(pinServo1A);
  serv2.attach(pinServo2A);
  serv3.attach(pinServo3B);
  serv4.attach(pinServo4B);


  Wire.begin();
  
  //Parte para o sensor ultrassonico  Serial1.begin(115200);
  Serial.begin(9600);

 
  
  pingTimer[0] = millis() + 75;                          //O primeiro ping começa em 75ms, dá tempo para o Arduino esfriar antes de iniciar.
  for (uint8_t i = 1; i < SONAR_NUM; i++){                //Defina a hora de início para cada sensor.
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;  
  }

}


void loop() {


//Parte para os servos se moverem

  for (angulo = 0; angulo < 180; angulo += 1) { // Comando que muda a posição do servo de 0 para 180°
    serv1.write(angulo); // Comando para angulo específico
    serv2.write(angulo); // Comando para angulo específico
    serv3.write(angulo); // Comando para angulo específico
    serv4.write(angulo); // Comando para angulo específico
    delay(15); 
}
 
  delay(1000); // Tempo de espera para próximo movimento
  for (angulo = 180; angulo >= 1; angulo -= 1) { // Comando que muda a posição do servo de 180 para 0°
    serv1.write(angulo); // Comando para angulo específico
    serv2.write(angulo); // Comando para angulo específico
    serv3.write(angulo); // Comando para angulo específico
    serv4.write(angulo); // Comando para angulo específico
    delay(15);
}
  //Parte para o sesnor ultrassonico
  for (uint8_t i = 0; i < SONAR_NUM; i++) {                            //Faz um loop em todos os sensores.
    if (millis() >= pingTimer[i]) {                                    //Se pergunta "É hora deste sensor fazer ping?"
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;                       //Defina na próxima vez que este sensor será pingado.
      if (i == 0 && currentSensor == SONAR_NUM - 1) oneSensorCycle();  //Ciclo de ping do sensor completo, faça algo com os resultados.
      sonar[currentSensor].timer_stop();                               //Certifique-se de que o temporizador anterior foi cancelado antes de iniciar um novo ping (seguro)
      currentSensor = i;                                               //Sensor sendo acessado.
      cm[currentSensor] = 0;                                           //Faça a distância zero caso não haja eco de ping para este sensor.
      sonar[currentSensor].ping_timer(echoCheck);                      //Faça o ping (o processamento continua, a interrupção chamará o echoCheck para procurar o eco).
    }
  }

  //if(cm < 30){
   Wire.beginTransmission(EndMotor);
   Wire.write(ult);
   Wire.endTransmission();

   Serial.print("batata");
 // }
   
  
}
