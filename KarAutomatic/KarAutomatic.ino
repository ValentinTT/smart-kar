
int trig = 3;
int echo = 2;
int duration = 0;
int distance = 0;

int carSpeed = 180;
int enA = 10;
int in1 = 9;
int in2 = 8;
int in3 = 7;
int in4 = 6;
int enB = 5;

void setup() {
  // put your setup code here, to run once:  
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
  getDistance();
  if(distance > 10) {
    up();
  } else {
    leftReverse();
    delay(900);
    up();
  }
}

void getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);

  distance = duration/58.2;
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

