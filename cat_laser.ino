#include <Servo.h>

Servo servoX, servoY;

int stop = 0;

int desiredX[] = {70, 110};
int desiredY[] = {10, 60};

int servoPinX = 2;
int servoPinY = 6;

long randNumber;

int servoXMin = 0;
int servoXMax = 180;

int servoYMin = 10;
int servoYMax = 105;

float currentPosition[] = {
  (servoXMax - servoXMin) / 2,
  (servoYMax - servoYMin) / 2
};

void setup() {
  Serial.begin(9600);

  servoX.attach(servoPinX);
  servoY.attach(servoPinY);

  randomSeed(analogRead(0));

  setX(currentPosition[0]);
  setY(currentPosition[1]);

  delay(1000);
}

void loop() {
  if (stop == 1) {
    return;
  }

  randomSeed(analogRead(0));

  move(
    desiredX[0] + random(desiredX[1] - desiredX[0]),
    desiredY[0] + random(desiredY[1] - desiredY[0]),
    random(300)
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