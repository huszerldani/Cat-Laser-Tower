#include <Servo.h>

Servo servoX, servoY;

int stop = 0;

int desiredX[] = {60, 100};
int desiredY[] = {15, 70};

int servoPinX = 2;
int servoPinY = 6;

long randNumber;

int servoXMin = 0;
int servoXMax = 180;

int servoYMin = 10;
int servoYMax = 105;

float center[] = {
  ((servoXMax - servoXMin) / 2) - 8,
  (servoYMax - servoYMin) / 2 + 15
};

float currentPosition[] = {
  center[0],
  center[1]
};

void setup() {
  Serial.begin(9600);

  servoX.attach(servoPinX);
  servoY.attach(servoPinY);

  randomSeed(analogRead(0));

  setX(center[0]);
  setY(center[1]);

  delay(2000);
  
  move(center[0], center[1] + 30, 50);
  move(center[0], center[1] - 30, 50);
  move(center[0], center[1] + 30, 50);
  move(center[0], center[1] - 30, 50);

  delay(200);
  move(center[0], center[1], 150);

  delay(1000);
}

void loop() {
  if (stop == 1) {
    return;
  }

  move(
    random(desiredX[0], desiredX[1]),
    random(desiredY[0], desiredY[1]),
    random(20, 200)
  );

  delay(random(100));
}

void move(int positionX, int positionY, int steps) {
  float lengthX = positionX - currentPosition[0];
  float lengthY = positionY - currentPosition[1];

  float forwardXPerStep = lengthX / steps;
  float forwardYPerStep = lengthY / steps;

  for (int i = 0; i <= steps; i++) {
    setX(currentPosition[0] + forwardXPerStep);
    setY(currentPosition[1] + forwardYPerStep);

    delay(random(10));
  }
}


//----------------------
//--- HELPERS ----------
//----------------------

void setX(float position) {
  float setPosition = position;

  if (position > servoXMax) {
    setPosition = servoXMax;
  }

  if (position < servoXMin) {
    setPosition = servoXMin;
  }

  currentPosition[0] = setPosition;
  servoX.write(setPosition);
}

void setY(float position) {
  float setPosition = position;

  if (position > servoYMax) {
    setPosition = servoYMax;
  }

  if (position < servoYMin) {
    setPosition = servoYMin;
  }

  currentPosition[1] = setPosition;
  servoY.write(setPosition);
}

void log(String key, int value) {
  Serial.println(key + ": " + String(value));
}

int intVal(float value) {
  return value;
}