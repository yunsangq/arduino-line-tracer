
#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

#define VALUE  500

void setup() { 
  //Serial.begin(9600);
  Robot.begin();   
  Robot.stop();    
}

/*
    왼쪽바퀴  오른쪽바퀴
       b       a
*/

// L,R 이 반대 motors(a, b)
// -가 커질수록 앞으로 가는 속도 증가
// +가 커질수록 뒤로 가는 속도 증가
// 왼쪽회전 -> R,L => a > b
// 오른쪽회전 -> R,L => a < b

int cnt = 0; 
int check = 0;

void loop() {
  cnt++;
  //Serial.println(cnt);
  if(cnt >= 30500){
    Robot.motors(0,0);
    delay(10000);
  }
  if(cnt < 22800 || check == 1){
    //우회전 방향전환 => |a| > |b| (a>0, b<0)
    // 0 0 0 0 1 1 AND
    if((Robot.Front_IRread(4) < VALUE) && (Robot.Front_IRread(5) < VALUE) && (Robot.Front_IRread(3) < VALUE)){
      Robot.motors(0,0);
      delay(150);
      Robot.motors(90, -120);
      delay(100);
    }
    
    //좌회전 방향전환 => |a| < |b| (a<0, b>0) 
    // 1 1 0 0 0 0 AND
    if((Robot.Front_IRread(0) < VALUE) && (Robot.Front_IRread(1) < VALUE) && (Robot.Front_IRread(2) < VALUE)){ 
      Robot.motors(0,0);
      delay(150);
      Robot.motors(-110, 100);
      delay(100);
    }
    
    //직진 가능하도록 속도 200근처에서 좌 우 최대한 수평값 찾기(내일)
    // 0 0 1 1 0 0
    if((Robot.Front_IRread(2) < VALUE) || (Robot.Front_IRread(3) < VALUE)){
      Robot.motors(-165, -185);
    }

    //우회전 직진 보정 => |a| < |b| (a<0, b<0)
    // 0 0 0 0 1 1 OR
    if((Robot.Front_IRread(4) < VALUE) || (Robot.Front_IRread(5) < VALUE)){
      Robot.motors(-30, -130);
    }

    //좌회전 직진 보정 => |a| > |b| (a<0, b<0)
    // 1 1 0 0 0 0 OR
    if((Robot.Front_IRread(0) < VALUE) || (Robot.Front_IRread(1) < VALUE)){
      Robot.motors(-120, -30);
    } 
  }
  else if(cnt < 30000 && cnt >= 22800){
    //직진 가능하도록 속도 200근처에서 좌 우 최대한 수평값 찾기(내일)
    // 0 0 1 1 0 0
    if((Robot.Front_IRread(2) < VALUE) || (Robot.Front_IRread(3) < VALUE)){
      Robot.motors(-160, -180);
    }

    if((Robot.Front_IRread(0) > VALUE) && (Robot.Front_IRread(1) > VALUE) && (Robot.Front_IRread(2) > VALUE) && (Robot.Front_IRread(3) > VALUE) && (Robot.Front_IRread(4) > VALUE) && (Robot.Front_IRread(5) > VALUE) && (Robot.Rear_IRread(0) > VALUE) && (Robot.Rear_IRread(1) > VALUE) && (Robot.Rear_IRread(2) > VALUE) && (Robot.Rear_IRread(3) > VALUE) && (Robot.Rear_IRread(4) > VALUE) && (Robot.Rear_IRread(5) > VALUE)){
      Robot.motors(0,0);
      delay(350);
      Robot.motors(-80, -60);
      while(1){
        if((Robot.Front_IRread(0) < VALUE) || (Robot.Front_IRread(1) < VALUE)  || (Robot.Front_IRread(2) < VALUE) || (Robot.Front_IRread(3) < VALUE)  || (Robot.Front_IRread(4) < VALUE) || (Robot.Front_IRread(5) < VALUE)){
          check = 1;
          break;
        }
      } 
    }
  }
}


