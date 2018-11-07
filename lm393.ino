int SOUND_SENSOR = A0;
int threshold = 25;
int Sensor_value;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SOUND_SENSOR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Sensor_value = analogRead(A0);
  Serial.println(Sensor_value);
  delay(1000);
}
