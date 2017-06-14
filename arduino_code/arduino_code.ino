#include <IRLremote.h>

int enA = 10; //Conexion con motor izquierdo
int enB = 5;
int in1 = 9;
int in2 = 8;
int in3 = 7;
int in4 = 6; //Conexion con motor derecho


int interrupcion = 0; //pin 2
uint8_t protocolo = 0;
uint16_t direccion = 0;
uint32_t tecla = 0;
uint8_t oldSREG;
bool encendido;

long tiempo;
long distancia;
int echo = 11;
int trig = 12;


void setup() {
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  IRLbegin<IR_ALL>(interrupcion);
  encendido = 0;
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*oldSREG = SREG;
  cli(); 
  if(protocolo != 0){
    protocolo = 0; 
    Serial.print("Protocolo: ");
    Serial.print(protocolo);
    Serial.print("   Direccion: ");
    Serial.print(direccion, HEX);
    Serial.print("   Tecla: ");
    Serial.println(tecla);
    
    if(tecla == 53295){
      avanzar(200);
    } else if(tecla == 28815){
      retroceder(200);
    } else if(tecla == 2295){
      derecha(200);
    } else if(tecla == 34935){
      izquierda(200);  
    } else {    
      parar();
    }
  }

  SREG = oldSREG;    */
  digitalWrite(trig,LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);
  tiempo=pulseIn(echo, HIGH);
  distancia= int(0.017*tiempo);
  if(distancia < 5){
    avanzar(150);
    delay(500);
    izquierda(150);
    delay(1000);
  } else {
    retroceder(150);
  }
}

void parar(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  analogWrite(enA, 0);
  analogWrite(enB, 0);  
}

void avanzar(int velocidad){
  parar();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);
}

void retroceder(int velocidad){
  parar();  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);  
}

void izquierda(int velocidad){  //hacemos avanzar los motores derechos 
  parar();  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  analogWrite(enB, velocidad);
}

void derecha(int velocidad){
  parar();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enA, velocidad);
}

void IREvent(uint8_t protocol, uint16_t address, uint32_t command){
  protocolo = protocol;
  direccion = address;
  tecla = command;
}





