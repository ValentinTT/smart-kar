#include <SoftwareSerial.h>

SoftwareSerial serialBlue(11, 12); //Rx, Tx.
int command = 0;
int lastCommand = 0;
int carSpeed;

int enA = 10;
int in1 = 9;
int in2 = 8;
int in3 = 7;
int in4 = 6;
int enB = 5;


void setup() {
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

  serialBlue.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (serialBlue.available() > 0) {
    command = serialBlue.read();
    if (command == 'u') {
      up();
      changeCommand();
    } else if (command == 'd') {
      down();
      changeCommand();
    } else if (command == 'l') {
      if (lastCommand == 'd') {
        leftReverse();
      } else {
        left();
      }
      changeCommand();
    } else if (command == 'r') {
      if (lastCommand == 'd') {
        rightReverse();
      } else {
        right();
      }
      changeCommand();
    } else if (command == 's') {
      stopKar();
      changeCommand();
    }
  }
}

void changeCommand() {
  lastCommand = command;
  command = 0;
}

void up() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, 200);
  analogWrite(enB, 200);
}

void down() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, 200);
  analogWrite(enB, 200);
}

void left() {
  stopKar();
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enB, 180);
}

void leftReverse() {
  stopKar();
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enB, 180);
}

void right() {
  stopKar();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enA, 180);
}

void rightReverse() {
  stopKar();
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, 180);
}

void stopKar() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

