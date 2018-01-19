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
IRsend ir;
int x = 0;
int y = 0;
int xx = 0;
int yy = 0;
int mode = 0;
int last_mode=0;
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
			ir.sendSony(up,8);
			Serial.println("up");
			break;
		case -10:	//當為下
			ir.sendSony(dw,8);
			Serial.println("down");
			break;
		case 1:		//當為右
			ir.sendSony(rt,8);
			Serial.println("right");
			break;
		case -1:	//當為左
			ir.sendSony(lt,8);
			Serial.println("left");
			break;
		case 11:	//當為右上
			ir.sendSony(ur,8);
			Serial.println("up and right");
			break;
		case 9:		//當為左上
			ir.sendSony(ul,8);
			Serial.println("up and left");
			break;
		case -9:	//當為右下
			ir.sendSony(dr,8);
			Serial.println("down and right");
			break;
		case -11:	//當為左下
			ir.sendSony(dl,8);
			Serial.println("down and left");
			break;
		case 0:		//當為中間
			ir.sendSony(st,8);
			//Serial.println("stop");
			break;
	}
	delay(50);
	
	
}
