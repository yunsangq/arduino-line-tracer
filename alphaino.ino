
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

//long cnt = 0;
int check = 0;
void loop() {
  //cnt++;
  
  if( check < 3 && (Robot.Front_IRread(0) < VALUE) && (Robot.Front_IRread(1) < VALUE) && (Robot.Front_IRread(2) < VALUE) && (Robot.Front_IRread(3) < VALUE) && (Robot.Front_IRread(4) < VALUE) && (Robot.Front_IRread(5) < VALUE)){
    check++;
    Robot.motors(-230, -230);
    delay(1000);
  }
  //우회전 방향전환 => |a| > |b| (a>0, b<0)
  else if((Robot.Front_IRread(4) < VALUE) && (Robot.Front_IRread(5) < VALUE) && (Robot.Front_IRread(3) < VALUE)){
    Robot.motors(80, -150);
    delay(200);
  }
  
  //좌회전 방향전환 => |a| < |b| (a<0, b>0) 
  else if((Robot.Front_IRread(0) < VALUE) && (Robot.Front_IRread(1) < VALUE) && (Robot.Front_IRread(2) < VALUE)){ 
    Robot.motors(-150, 80);
    delay(200);
  }

  //항시구간
  if( (Robot.Front_IRread(2) < VALUE) || (Robot.Front_IRread(3) < VALUE) )
  {
      Robot.motors(-230, -230);
  }
  else if( (Robot.Front_IRread(0) < VALUE) || (Robot.Front_IRread(1) < VALUE) )
  {
      Robot.motors(-150, 80);
  }
  else if( (Robot.Front_IRread(4) < VALUE) || (Robot.Front_IRread(5) < VALUE) )
  {
      Robot.motors(80, -150);
  }
}

/*
#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

#define VALUE  500

void setup() { 
  Serial.begin(9600);
  Robot.begin();   
  Robot.stop();    
}

long cnt = 0; 
int check = 0;
void loop() {
  cnt++;
  //Serial.println(cnt);
  if(cnt > 35500){
    if((Robot.Front_IRread(0) > VALUE) && (Robot.Front_IRread(1) > VALUE) && (Robot.Front_IRread(2) > VALUE) && (Robot.Front_IRread(3) > VALUE) && (Robot.Front_IRread(4) > VALUE) && (Robot.Front_IRread(5) > VALUE) && (Robot.Rear_IRread(0) > VALUE) && (Robot.Rear_IRread(1) > VALUE) && (Robot.Rear_IRread(2) > VALUE) && (Robot.Rear_IRread(3) > VALUE) && (Robot.Rear_IRread(4) > VALUE) && (Robot.Rear_IRread(5) > VALUE)){
      Robot.motors(0,0);
      delay(5000);
    }
  }
  else if(cnt < 22800 || check == 1){
    //우회전 방향전환 => |a| > |b| (a>0, b<0)
    // 0 0 0 0 1 1 AND
    if((Robot.Front_IRread(4) < VALUE) && (Robot.Front_IRread(5) < VALUE) && (Robot.Front_IRread(3) < VALUE)){
      //Robot.motors(0,0);
      //delay(150);
      Robot.motors(90, -120);
      delay(300);
      //delay(100);
    }
    
    //좌회전 방향전환 => |a| < |b| (a<0, b>0) 
    // 1 1 0 0 0 0 AND
    if((Robot.Front_IRread(0) < VALUE) && (Robot.Front_IRread(1) < VALUE) && (Robot.Front_IRread(2) < VALUE)){ 
      //Robot.motors(0,0);
      //delay(150);
      Robot.motors(-110, 100);
      delay(300);
      //delay(100);
    }
    
    //직진
    // 0 0 1 1 0 0
    if((Robot.Front_IRread(2) < VALUE) || (Robot.Front_IRread(3) < VALUE)){
      Robot.motors(-210, -230);
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
    //직진
    // 0 0 1 1 0 0
    if((Robot.Front_IRread(2) < VALUE) || (Robot.Front_IRread(3) < VALUE)){
      Robot.motors(-160, -180);
    }

    //우회전 직진 보정 => |a| < |b| (a<0, b<0)
    // 0 0 0 0 1 1 OR
    if((Robot.Front_IRread(4) < VALUE) || (Robot.Front_IRread(5) < VALUE)){
      Robot.motors(-30, -100);
    }

    //좌회전 직진 보정 => |a| > |b| (a<0, b<0)
    // 1 1 0 0 0 0 OR
    if((Robot.Front_IRread(0) < VALUE) || (Robot.Front_IRread(1) < VALUE)){
      Robot.motors(-100, -30);
    }
 
    if((Robot.Front_IRread(0) > VALUE) && (Robot.Front_IRread(1) > VALUE) && (Robot.Front_IRread(2) > VALUE) && (Robot.Front_IRread(3) > VALUE) && (Robot.Front_IRread(4) > VALUE) && (Robot.Front_IRread(5) > VALUE) && (Robot.Rear_IRread(0) > VALUE) && (Robot.Rear_IRread(1) > VALUE) && (Robot.Rear_IRread(2) > VALUE) && (Robot.Rear_IRread(3) > VALUE) && (Robot.Rear_IRread(4) > VALUE) && (Robot.Rear_IRread(5) > VALUE)){
      Robot.motors(0,0);
      delay(500);
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
*/
