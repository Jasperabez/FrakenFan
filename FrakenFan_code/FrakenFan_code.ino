#include <Ultrasonic.h>
#include <Servo.h>
#define trigPin 9
#define echoPin 10
#define motorPWM 11
#define switchPin 12
#define servoPWM 6
Ultrasonic ultrasonic(trigPin, echoPin);
Servo servo;
int motorStatus = 0; //indicate whether the motor is on or off
int pos = 0; //position(in degrees from 0) of Servo
void setup(){
    pinMode(switchPin,INPUT);
    pinMode(motorPWM,OUTPUT);
    servo.attach(servoPWM);
    //Serial.begin(9600);     debugging code
}
void loop(){
    if(digitalRead(switchPin)==HIGH){ // when switch turns on
        int distance = ultrasonic.read();
        delay(10);
        //Serial.println(distance);   debugging code
        if(distance<=50 && motorStatus==0){ //motor starts when detect user
            analogWrite(motorPWM,100);
            motorStatus=1;
        }
        else if(distance>50 && motorStatus==1){//motor stops when user not detected 
            analogWrite(motorPWM,0);
            motorStatus=0;
        }
        else if(motorStatus==0 && pos<90){//sweep ultrasonic to find user
            pos++;
            servo.write(pos);
            delay(10);
        }
        else if(motorStatus==0 && pos==90){//resets back to pos 0 when user max degree reached
            pos = 0;
            servo.write(pos);
        }
    }
    else{//resets back to pos 0 and switch off motor when switch off
      analogWrite(motorPWM,0);
      motorStatus = 0;
      pos = 0;
      servo.write(pos);
      Serial.println("off");
    }
}
