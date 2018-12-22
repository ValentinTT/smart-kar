#include <SoftwareSerial.h>
#define pinSeguidorI A2
#define pinSeguidorD A0
SoftwareSerial serialBlue(11, 12); //Rx, Tx.
int command = 0;
int lastCommand = 0;
int carSpeed = 150;

bool automatic = false;
bool followLine = false;
int trig = 3;
int echo = 2;
int duration = 0;
int distance = 10;

int enA = 10;
int in1 = 9;
int in2 = 8;
int in3 = 7;
int in4 = 6;
int enB = 0;

void setup() {
  // put your setup code here, to run once:
  serialBlue.begin(38400);
  Serial.begin(38400);
  pinMode(pinSeguidorI, INPUT);
  pinMode(pinSeguidorD, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (serialBlue.available() > 0) {
    command = serialBlue.read();
    Serial.println((char)command);
    executeAction();
  }
  if (automatic) {
    automaticDriving();
  } else if (followLine) {
    followLineDriving();
  }
}

void automaticDriving() {
  getDistance();
  if (distance >= 10) {
    up();
  } else {
    leftReverse();
    delay(100);
    stopKar();
  }
}

void followLineDriving() {
  carSpeed = 120;
  int izq = analogRead(pinSeguidorI);
  int der = analogRead(pinSeguidorD);
  if (der <= 100) {
    der = 0;
  } else {
    der = 1;
  }
  if (izq <= 100) {
    izq = 0;
  } else {
    izq = 1;
  }
  if (der == HIGH) {
    Serial.print("DERECHO");
    leftLine();
  } else if (izq == HIGH) {
    Serial.print("IZQUIERDO");
    RightLine();
  } else if (izq == LOW && der == LOW) {
    Serial.print("ADELANTE");
    up();
  } else {
    Serial.print("FRENADO");
    stopKar();
  }
  delay(50);
}

void getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);

  distance = duration / 58.2;
}

void executeAction() {
  switch (command) {
    case 'u':
      up();
      changeCommand();
      break;
    case 'd':
      down();
      changeCommand();
      break;
    case 'l':
      if (lastCommand == 'd')
        leftReverse();
      else
        left();
      changeCommand();
      break;
    case 'r':
      if (lastCommand == 'd')
        rightReverse();
      else
        right();
      changeCommand();
      break;
    case 's':
      stopKar();
      changeCommand();
      break;
    case 'a':
      automatic = !automatic;
      if (!automatic) stopKar();
      else {
        carSpeed = 180;
      }
      break;
    case 'F':
      followLine = !followLine;
      if (!followLine) stopKar();
      else
        carSpeed = 120;
      break;
    case 'v':
      while (true) {
        String auxSpeed = ""; //This is on charge of keep all the numbers that comform the speed value
        while (serialBlue.available() > 0) {
          command = serialBlue.read(); //Cach each number of the speed
          if (command != '\n') //command == '\n' means that the speed has been totally pass
            auxSpeed += (char)command;
          else
            break;
        }
        carSpeed = auxSpeed.toInt();
        break;
      }
      command = lastCommand;
      executeAction();
      break;
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

  analogWrite(enA, carSpeed);
  analogWrite(enB, carSpeed);
}

void down() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, carSpeed);
  analogWrite(enB, carSpeed);
}

void left() {
  stopKar();
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enB, carSpeed);
}

void leftReverse() {
  stopKar();
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enA, carSpeed);
}

void right() {
  stopKar();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enA, carSpeed);
}

void rightReverse() {
  stopKar();
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enB, carSpeed);
}

void stopKar() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


void leftLine() {
  stopKar();
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, carSpeed);
  analogWrite(enB, carSpeed);
}
void RightLine() {
  stopKar();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, carSpeed);
  analogWrite(enB, carSpeed);
}
