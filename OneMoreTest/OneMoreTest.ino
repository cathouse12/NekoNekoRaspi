#include <Servo.h>
#include <SimpleTimer.h>

//서보모터 핀 설정하기
int feedServoPin1 = 4;
int feedServoPin2 = 5;

//서보모터 각도 설정하기
int feedServoAngle1 = 0;
int feedServoAngle2 = 0;

//Servo객체 선언하기
Servo feedServo1;
Servo feedServo2;

//초음파 센서 핀 설정
int echoPin = 12;
int trigPin = 14;

//SimpleTImer 선언하기
SimpleTimer timer;

void setup() {
  //시리얼 포트 설정하기
  Serial.begin(115200);
  
  //Servo 객체와 pin 연결하기
  feedServo1.attach(feedServoPin1);
  feedServo2.attach(feedServoPin2);  

  //trig를 출력 모드로, echo를 입력모드로 설정하기
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);

  //타이머 설정하기
  /* 1000 -> 1초
   * 60000 -> 1분
   * 600000 -> 10분
   * 10분 마다 서버 정보 업데이트 */
  timer.setInterval(1000,sendToFirebase);
}

void loop() {
  // 첫번째 서보모터 돌리기
  for(feedServoAngle1 = 0; feedServoAngle1 < 180; feedServoAngle1++){
    feedServo1.write(feedServoAngle1);
    delay(15);  
  }

  //타이머 시작하기
  timer.run();
}


void sendToFirebase(){
   //echo,trig 핀 초기화하기
  digitalWrite(trigPin,LOW);
  digitalWrite(echoPin,LOW);
  delayMicroseconds(2);

  //초음파 보내기
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  //초음파 받기 까지의 시간 구하기
  unsigned long duration = pulseIn(echoPin,HIGH);
    
  //거리 계산하기리
  float distance = ((float)(340 * duration)/10000)/2;

  //시리얼에 출력하기
  Serial.println(distance);
  
  Serial.println("OH!!");
}