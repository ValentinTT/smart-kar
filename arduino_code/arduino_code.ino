#include <IRLremote.h>

int enA = 10;
int enB = 5;
int in1 = 9;
int in2 = 8;
int in3 = 7;
int in4 = 6;


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
  adelante();
  delay(300);
}

void adelante(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  analogWrite(enA, 250);
  analogWrite(enB, 250);
}

