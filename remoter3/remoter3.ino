#include <IRremote.h>
#include <IRremoteInt.h>

#define st 0x66
#define up 0xAA
#define dw 0xBB
#define rt 0xCC
#define lt 0xDD
#define ur 0xAC
#define ul 0xAD
#define dr 0xBC
#define dl 0xBD
#define ir 9
int x = 0;
int y = 0;
int xx = 0;
int yy = 0;
int mode = 0;
int last_mode=0;
int cut(int num,int a){
	int b = num/pow(10,a);
	return b%10;
	}
void s(boolean x){
	float d=0.3;
	for(int i =0;i<10;i++){
		digitalWrite(ir,x);
		delay(d);
		digitalWrite(ir,LOW);
		delay(d);
	}
}
void sent(int info) {
	s(50);
	delay(1);
	y=(info,BIN);
	for (int i=0;i<8;i++){
		s(cut(y,i));
	}
}
void setup() {
  // put your setup code here, to run once:
	pinMode(3,OUTPUT);
	Serial.begin(9600);
	Serial.println("begin");
}

void loop() {
  // put your main code here, to run repeatedly:
	x = analogRead(A0);  
	y = analogRead(A1);
	if (x>800){
		xx= 1;
	}else if(x<250){
		xx=-1;
	}else{
		xx=0;
	}
	if (y>900){
		yy=10;
	}else if(y<150){
		yy=-10;
	}else{
		yy=0;
	}
	mode=xx+yy;
	switch(mode){
		case 10:	//當為上
			sent(up);
			Serial.println("up");
			break;
		case -10:	//當為下
			sent(dw);
			Serial.println("down");
			break;
		case 1:		//當為右
			sent(rt);
			Serial.println("right");
			break;
		case -1:	//當為左
			sent(lt);
			Serial.println("left");
			break;
		case 11:	//當為右上
			sent(ur);
			Serial.println("up and right");
			break;
		case 9:		//當為左上
			sent(ul);
			Serial.println("up and left");
			break;
		case -9:	//當為右下
			sent(dr);
			Serial.println("down and right");
			break;
		case -11:	//當為左下
			sent(dl);
			Serial.println("down and left");
			break;
		case 0:		//當為中間
			sent(st);
			//Serial.println("stop");
			break;
	}
	delay(10);
	
	
}
