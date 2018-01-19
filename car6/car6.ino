#include <IRremote.h>
#include <Servo.h>
int RECV_PIN = 11;
boolean red=false;
IRrecv re(RECV_PIN);
decode_results results;
#define r1 6
#define r2 5
#define l1 4
#define l2 3

#define led 12
#define trig 24
#define echo 25
#define IF A2
const int high = 350;

#define st 0x1FAEC0E9
#define up 0xBAD3529A
#define dw 0x4B3DE971
#define rt 0x86496FDA
#define lt 0x2AC4BB31
#define ur 0xDB37230C
#define ul 0xDB37230F
#define dr 0xD397D03E
#define dl 0xD397D03D

const int center = 90;
int path = center;
byte x=1;
Servo servo;
byte mode=2 ;
int number[][8] = {
	{1,1,1,1,1,1,0,0}, //0
	{0,1,1,0,0,0,0,0}, //1
	{1,1,0,1,1,0,1,0}, //2
	{1,1,1,1,0,0,1,0}, //3
	{0,1,1,0,0,1,1,0}, //4
	{1,0,1,1,0,1,1,0}, //5
	{1,0,1,1,1,1,1,0}, //6
	{1,1,1,0,0,0,0,0}, //7
	{1,1,1,1,1,1,1,0}, //8
	{1,1,1,1,1,1,0,0}, //9
	{0,0,0,0,0,0,0,0}, //none
	{1,0,0,0,1,1,1,0}  //F
};
long longs(){
	digitalWrite(trig,LOW);
	delay(2);
	digitalWrite(trig,HIGH);
	delay(10);
	digitalWrite(trig,LOW);
	return pulseIn(echo,HIGH)/58;
}
void setnumber(byte num){
	for(int i =0;i<=7;i++){
		digitalWrite(i+30,number[num][i]);
	}
}
void setservo(int p){
	path = p;
	servo.write(path);
}
void changeservo(int p){
	path = path + p ;
	servo.write(path);
}
void setmotor(int B, int A) {
	A += 0;
	B += 30;
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
void easymotor(int A,int B,int t){
	setmotor(A,B);
	delay(t);
}
void setA(){
	Serial.begin(9600);
	re.blink13(true);
	re.enableIRIn();
	Serial.println("begin");
	for (int i = 2; i < 7; i++) {
		pinMode(i,OUTPUT);
	}
}
float get_distance(){
	float var = 0;
	for(byte i=0;i<5;i++){
		var += analogRead(IF);
		delay(2);
	}
	var /= 5;
	if(var>high){
		digitalWrite(led,HIGH);
	}else{
		digitalWrite(led,LOW);
	}
	return var;
}
void setB(){
	pinMode(trig,OUTPUT);
	pinMode(echo,INPUT);
	pinMode(50,INPUT);
	pinMode(led,OUTPUT);
	Serial.begin(9600);
	Serial.println("begin");
	servo.attach(9);
	digitalWrite(50,HIGH);
	servo.write(center);
}
void check_road(){
	setmotor(0,0);
	setservo(center);
	float front = get_distance();
	delay(300);
	setservo(center+60);
	float right = get_distance();
	delay(200);
	setservo(center-60);
	float left = get_distance();
	delay(200);
	setservo(center);
	if(front+left+right<(high+100)*3){
		if(left<right){
			setmotor(-80,80);
			delay(100);
			byte x=0;
			while(get_distance()>high-50 and x<5){
				delay(100);
				x++;
			}
		}else if (right<left){
			setmotor(80,-80);
			delay(100);
			byte x=0;
			while(get_distance()>high-50 and x<5){
				delay(100);
				x++;
			}
		}
	}else{
		easymotor(-100,-100,500);
		easymotor(0,0,200);
		easymotor(-100,100,500);
	}
	easymotor(0,0,300);
}
void run(byte i){
	setservo(25+i*65);
	float val = get_distance();
	Serial.println(val);
	if (val > high){
		if (path > 60 and path < 120){
			check_road();
		}else if(path < 60){
			easymotor(0,80,100);
		}else if(path > 120){
			easymotor(80,0,100);
		}
	}else{
		setmotor(80,80);
	}
	delay(200);
}
void setup() {
	pinMode(50,INPUT);
	pinMode(51,INPUT);
	for (int i = 30;i<=37;i++){
		pinMode(i,OUTPUT);
	}
	digitalWrite(50,HIGH);
	digitalWrite(51,HIGH);
	setnumber(11);
	delay(1);
	while(1+1==2){
		if (!digitalRead(50)){
			mode=1;
			setA();
			setnumber(1);
			break;
		}else if(!digitalRead(51)){
			mode=2;
			setB();
			setnumber(2);
			break;
		}
		setservo(center);
	}
}

void loopA(){
	if (re.decode(&results)) {
		Serial.println(results.value,HEX);
      switch(results.value){
		case up:   //前進
			Serial.println("up");
			setmotor(150, 150);
			delay(0);    
			break;
        case dw:   //後退
			Serial.println("down");
			setmotor(-150, -150);
			delay(0);
          
			break;
		case rt:   //右轉
			setmotor(-150, 150);
			delay(0);
			break;
        case lt:    //左轉
			setmotor(150, -150);
			delay(0);       
			break;
		case ur:	//右上
			setmotor(50,200);
			break;
		case ul:  	//左上
			setmotor(200,50);
			break;
		case dr:	//右下
			setmotor(-200,-50);
			break;
		case dl:	//左下
			setmotor(-50,-200);
			break;
      default:   //停車
      setmotor(0, 0);
      break;
      }
      delay(0);
      re.resume();
  }

}
void loopB(){
	for (byte i = 0 ; i < 3;i++){
		run(i);
	}
	run(1);
}
void loop() {
    if (mode == 1){
		loopA();
	}else if(mode == 2){
		loopB();
		//setservo(center);
	}
}

