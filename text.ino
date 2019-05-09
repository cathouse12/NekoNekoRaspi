#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);        //RS 핀, E핀, 데이터 핀 4개
String lcdString = "";                   //객체 선언 : 출력 할 글자 저장

void setup() {                   
  lcd.begin(16,2);                       //LCD 크기 지정, 2줄 16칸
  lcd.clear();                           //화면 초기화
  Serial.begin(9600);                    //시리얼 통신 초기화
}

void loop() {
  lcd.setCursor(0,0);                    //커서를 0,0에 지정
   
  if(Serial.available()) {               //입력받은 데이터가 있으면
    delay(200);                          //0.2초 대기
    
    while(Serial.available() > 0) {      //문자 수 만큼 반복
      char lcdChar = (char)Serial.read();//문자 하나씩 읽고
      lcdString += lcdChar;              //읽은 문자를 하나씩 더해 문자열을 만듬
    }
    
    lcd.print(lcdString);                //문자열 LCD에 출력
    Serial.println(lcdString);           //시리얼 모니터에 입력한 값 출력
    lcdString = "";                      //문자열 초기화
    lcd.print("               ");        //전 글씨 삭제
  }
}
