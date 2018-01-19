#include <Servo.h>
Servo servo;
#define trig 24
#define echo 25
#define IF A2
long longs(){
	digitalWrite(trig,LOW);
	delay(2);
	digitalWrite(trig,HIGH);
	delay(10);
	digitalWrite(trig,LOW);
	return pulseIn(echo,HIGH)/58;
}
float get_distance(){
	float var = analogRead(IF);
	return var;
}
void setup(){
	Serial.begin(9600);
	servo.attach(9);
	servo.write(30);
	delay(200);
	servo.write(90);
	pinMode(trig,OUTPUT);
	pinMode(echo,INPUT);
}
void loop(){
	float v = get_distance();
	Serial.print("V:");
	Serial.println(v);
	delay(200);
}