#include <Stepper.h>

const int stepsPerRevolution = 1024;
Stepper myStepper(stepsPerRevolution,11,9,10,8);

void setup() {
  // put your setup code here, to run once:
  myStepper.setSpeed(30);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("counterclockwise");
  myStepper.step(stepsPerRevolution);
  delay(1000);

  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(1000);

}
