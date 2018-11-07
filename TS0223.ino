int volume_ain = A0;
int Value = 0;
int MAX = 760;
int MIN = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(volume_ain, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Value = analogRead(volume_ain);
Serial.print(Value);
//Serial.print(",");
//Serial.print("MAX : "+MAX);
//Serial.print(",");
//Serial.print("MIN : "+ MIN);
delay(5000);
}
