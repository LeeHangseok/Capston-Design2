#include <Stepper.h>

int volume_ain = A0;
int Value = 0;
int MAX = 760;
int MIN = 0;
const int stepsPerRevolution = 1024;
Stepper myStepper(stepsPerRevolution,11,9,10,8);

void setup() {
  // put your setup code here, to run once:
pinMode(volume_ain, INPUT);
myStepper.setSpeed(30);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Value = analogRead(volume_ain);
Serial.print(Value);
Serial.print("");
//Serial.print(",");
//Serial.print("MAX : "+MAX);
//Serial.print(",");
//Serial.print("MIN : "+ MIN);
if (Value > 500){
  Serial.println("counterclockwise");
  myStepper.step(stepsPerRevolution);
  delay(1000);

  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(1000);
  }
delay(2000);
}
