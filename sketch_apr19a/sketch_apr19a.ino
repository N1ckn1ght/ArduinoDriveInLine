const int DIRA = 4;
const int SPDA = 5;
const int SPDB = 6;
const int DIRB = 7;
const int SLL = A5;
const int SLR = A0;

const int rate = 20;
const int speed_ = 42 ;

void setup() {
  Serial.begin(9600);
  pinMode(DIRA, OUTPUT);
  pinMode(SPDA, OUTPUT);
  pinMode(SPDB, OUTPUT);
  pinMode(DIRB, OUTPUT);
  stop_();
}

void forward(int speed = 255) {
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, HIGH);
  analogWrite(SPDA, speed);
  analogWrite(SPDB, speed);
  Serial.println("Moving: forward with " + String(speed) + " speed!");
}

void backward(int speed = 255) {
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);
  analogWrite(SPDA, speed);
  analogWrite(SPDB, speed);
  Serial.println("Moving: backward with " + String(speed) + " speed!");
}

void rotation(bool right = true, int speed = 255) {
  if (right) {
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, HIGH);
    Serial.println("Rotating: right with " + String(speed) + " speed!");
  } else {
    digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, LOW);
    Serial.println("Rotating: right left " + String(speed) + " speed!");
  }
  analogWrite(SPDA, speed);
  analogWrite(SPDB, speed);
}

void turn(bool right = true, int speed = 255) {
  if (right) {
    digitalWrite(DIRB, HIGH);
    analogWrite(SPDA, 0);
    analogWrite(SPDB, speed);
    Serial.println("Turning: right with " + String(speed) + " speed!");
  } else {
    digitalWrite(DIRA, LOW);
    analogWrite(SPDA, speed);
    analogWrite(SPDB, 0);
    Serial.println("Turning: left with " + String(speed) + " speed!");
  }
}

void stop_() {
  analogWrite(SPDA, 0);
  analogWrite(SPDB, 0);
  Serial.println("Stopping!");
}

void loop() {
  bool sigLeft = digitalRead(SLL);
  bool sigRight = digitalRead(SLR);
  if (sigLeft && sigRight) {
    stop_();
  } else if (sigLeft && !sigRight) {
    turn(false, speed_);
  } else if (!sigLeft && sigRight) {
    turn(true, speed_);
  } else {
    forward(speed_);
  }
  delay(rate);
}
