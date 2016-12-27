#include <IRLremote.h>

int enA = 10; //Conexion con motor izquierdo
int enB = 5;
int in1 = 9;
int in2 = 8;
int in3 = 7;
int in4 = 6; //Conexion con motor derecho


void setup() {
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  avanzar(200);
  delay(2000);
  retroceder(200);
  delay(2000);
  izquierda(200);
  delay(2000);
  derecha(200);
  delay(2000);
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














