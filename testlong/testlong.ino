#include <Servo.h>

#define trig 24
#define echo 25

#define l1 6
#define l2 5
#define r1 4
#define r2 3
const int center = 90;
Servo servo;
long val[3];
void setmotor(int B, int A) {
  if (A > 0) {
    //analogWrite(rs, A);
    analogWrite(r1, A);
    digitalWrite(r2, LOW);
  } else if (A < 0) {
    //analogWrite(rs, abs(A));
    digitalWrite(r1, LOW);
    analogWrite(r2, A);
  } else {
    //analogWrite(rs, 0);
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
  }
  if (B > 0) {
    //analogWrite(ls, B);
    analogWrite(l1, B);
    digitalWrite(l2, LOW);
  } else if (B < 0) {
    //analogWrite(ls, abs(B));
    digitalWrite(l1, LOW);
    analogWrite(l2, B);
  } else {
    //analogWrite(ls, 0);
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
  }
}
long longs(){
	digitalWrite(trig,LOW);
	delay(2);
	digitalWrite(trig,HIGH);
	delay(10);
	digitalWrite(trig,LOW);
	return pulseIn(echo,HIGH)/58;
}
void setup(){
	pinMode(trig,OUTPUT);
	pinMode(echo,INPUT);
	pinMode(50,INPUT);
	Serial.begin(9600);
	Serial.println("begin");
	servo.attach(9);
	digitalWrite(50,HIGH);
	servo.write(center);
	while(digitalRead(50)==HIGH){
		
	}
}
void loop(){
	if (longs()<20){
		setmotor(0,0);
		servo.write(center);
		val[0]=longs();
		delay(300);
		servo.write(center+60);
		val[1]=longs();
		delay(200);
		servo.write(center-60);
		val[2]=longs();
		delay(200);
		servo.write(center);
		if(val[1]>val[2]and val[1]>15){
			setmotor(-100,100);
			delay(100);
			while(longs()<40){
				delay(100);
			}
		}else if (val[2]>val[1]and val[2]>15){
			setmotor(100,-100);
			delay(100);
			while(longs()<40){
				delay(100);
			}
		}else{
			setmotor(-100,-100);
			delay(500);
			setmotor(-100,100);
			delay(500);
		}
		setmotor(0,0);
		delay(300);
	}else{
		servo.write(center);
		setmotor(100,100);
	}
	delay(0);
}
