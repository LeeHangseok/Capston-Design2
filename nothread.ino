#include <Stepper.h> //스탭모터 라이브러리
#include <Servo.h> // 서보모터 라이브러리
#include <SoftwareSerial.h>

int volume_ain = A0;
int Value = 0; // 소리센서 초기값
int MAX = 760; // 소리 최댓값 임계치
int MIN = 0; // 소리 최솟값 임계치
/*int Air = A1; // 대기질 받을 핀 넘버 A1*/

#define RL 47  //The value of resistor RL is 47K
#define m -0.263 //Enter calculated Slope 
#define b 0.42 //Enter calculated intercept
#define Ro 20 //Enter found Ro value
#define MQ_sensor A1 //Sensor is connected to A1




int R = 4; // R핀 디지털 4번
int G = 5; // G핀 디지털 5번 
int B = 6; // B핀 디지털 6번
int AirValue = 0; // 암모니아센서 값 받을 변수
int temp = 1;
int cryingarray[2];
int i = -1;
bool iscrying = false;

const int stepsPerRevolution = 1024;
SoftwareSerial BTSerial(2,3);
Stepper myStepper(stepsPerRevolution,11,9,10,8);
Servo servomotor;
int pos = 0; //servomotor's position



void setup() {
  // put your setup code here, to run once:

Serial.begin(9600); // 직렬통신 9600 보드레이트
pinMode(R,OUTPUT); // R핀 OUTPUT 선언
pinMode(G,OUTPUT); // G핀 OUTPUT 선언
pinMode(B,OUTPUT); // B핀 OUTPUT 선언
pinMode(volume_ain, INPUT);
  Serial.println("Start");
  BTSerial.begin(9600);
myStepper.setSpeed(30);
servomotor.attach(12);// 12번 핀에 서보모터 연결


}

 
 
  

void loop() { 
Serial.println(analogRead(volume_ain));
Serial.println(cryingarray[0]);
Serial.println(cryingarray[1]);
  i++;
  if (analogRead(volume_ain) < 600){
    cryingarray[0] = 0;
    cryingarray[1] = 0;
    i = -1;
  }
  else {
    cryingarray[i] = 1;
    if (cryingarray[0] == cryingarray[1] ==1 )
    {
      //모터 돌리기
      while (analogRead(volume_ain) >= 600){
      Serial.println("mortor rolling");
      }
    }
    }
    if (cryingarray[0] == 1 && cryingarray[1] == 0){
    delay(3000);
    }



 float VRL; //Voltage drop across the MQ sensor
  float Rs; //Sensor resistance at gas concentration 
  float ratio; //Define variable for ratio
   
  VRL = analogRead(MQ_sensor)*(5.0/1023.0); //Measure the voltage drop and convert to 0-5V
  Rs = ((5.0*RL)/VRL)-RL; //Use formula to get Rs value
  ratio = Rs/Ro;  // find ratio Rs/Ro
 
  float ppm = pow(10, ((log10(ratio)-b)/m)); //use formula to calculate ppm

  Serial.print("NH3 (ppm) = "); //Display a ammonia in ppm
  Serial.print(ppm);
  Serial.println();
   if(ppm=0.01){ // 암모니아 수치
  digitalWrite(R, HIGH);
  delay(300);
  digitalWrite(R,LOW);
   BTSerial.write(temp);
  BTSerial.println(temp); 
  delay(300);
  
  }
  else if(ppm>0.005){ 
    digitalWrite(G, HIGH);
    delay(300);
    digitalWrite(G,LOW);
    BTSerial.write(temp-1);
    BTSerial.println(temp-1);
    delay(300);
    }
   else {
    delay(300);
   }





    
  }
  
