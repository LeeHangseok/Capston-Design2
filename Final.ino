#include <Stepper.h> //스탭모터 라이브러리
#include <Servo.h> // 서보모터 라이브러리
#include <Thread.h> // 스레드 라이브러리 MIT Lisence
#include <ThreadController.h> // MIT Lisnece

int volume_ain = A0;
int Value = 0; // 소리센서 초기값
int MAX = 760; // 소리 최댓값 임계치
int MIN = 0; // 소리 최솟값 임계치
int Air = A1; // 대기질 받을 핀 넘버 A1
int R = 4; // R핀 디지털 4번
int G = 5; // G핀 디지털 5번 
int B = 6; // B핀 디지털 6번
int AirValue = 0; // 소리센서 값 받을 변수

const int stepsPerRevolution = 1024;
Stepper myStepper(stepsPerRevolution,11,9,10,8);
Servo servomotor;
int pos = 0; //servomotor's position

Thread myThread1= Thread();
Thread myThread2 = Thread();


void setup() {
  // put your setup code here, to run once:
pinMode(Air, INPUT); // 대기질 센서 Input 선언
Serial.begin(9600); // 직렬통신 9600 보드레이트
pinMode(R,OUTPUT); // R핀 OUTPUT 선언
pinMode(G,OUTPUT); // G핀 OUTPUT 선언
pinMode(B,OUTPUT); // B핀 OUTPUT 선언
pinMode(volume_ain, INPUT);
myStepper.setSpeed(30);
servomotor.attach(12);


myThread1.onRun(CryingCheck);
myThread1.setInterval(100);
myThread2.onRun(AirCheck);
myThread2.setInterval(100);
}


void CryingCheck(){ // 아기가 울 때 
  Value = analogRead(volume_ain);
Serial.print(Value);
Serial.print("");

if (Value > 400){
  myStepper.step(stepsPerRevolution);
  delay(300);

  myStepper.step(-stepsPerRevolution);
  delay(300);
  for(pos = 0; pos < 180;pos++){
    servomotor.write(pos);
    delay(15);
    }
   for(pos-180;pos>0;pos--){
    servomotor.write(pos);
    delay(15);
    }
  }
  else{
    delay(300);
    }
delay(300);
  }



void AirCheck(){ // 대소변 감지
  AirValue = analogRead(Air); // AirValue 변수에 대기질값 아날로그 입력
 Serial.println(AirValue); // AirValue 출력
 if(AirValue>20){ // 암모니아 수치
  digitalWrite(R, HIGH);
  delay(300);
  digitalWrite(R,LOW);
  delay(300);
  }
  else if(AirValue>10){ 
    digitalWrite(G, HIGH);
    delay(300);
    digitalWrite(G,LOW);
    delay(300);
    }
   else {
    delay(300);
   }
   delay(300);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(myThread1.shouldRun()) myThread1.run();
  if(myThread2.shouldRun()) myThread2.run();
  
}
