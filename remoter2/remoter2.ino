#define st 0
#define up 1
#define dw 2
#define rt 3
#define lt 4
#define ur 5
#define ul 6
#define dr 7
#define dl 8
#define b1 9
#define b2 10
#define b3 11
#define b4 12
int x = 0;
int y = 0;
int xx = 0;
int yy = 0;
int mode = 0;
int last_mode=0;
void send(int v){
	v=map(v,0,9,0,255);
	analogWrite(10,v);
  Serial.println(v);
}
void setup() {
  // put your setup code here, to run once:
	pinMode(3,OUTPUT);
  pinMode(10,OUTPUT);
	Serial.begin(9600);
	Serial.println("begin");
}

void loop() {
  // put your main code here, to run repeatedly:
	x = analogRead(A0);
	y = analogRead(A1);
	if (x>800){
		yy= 10;
	}else if(x<250){
		yy=-10;
	}else{
		yy=0;
	}
	if (y>900){
		xx=-1;
	}else if(y<150){
		xx=1;
	}else{
		xx=0;
	}
	mode=xx+yy;
	if (mode == xx+yy){
		switch(mode){
			case 10:	//當為上
				send(up);
				Serial.println("up");
				break;
			case -10:	//當為下
				send(dw);
				Serial.println("down");
				break;
			case 1:		//當為右
				send(rt);
				Serial.println("right");
				break;
			case -1:	//當為左
				send(lt);
				Serial.println("left");
				break;
			case 11:	//當為右上
				send(ur);
				Serial.println("up and right");
				break;
			case 9:		//當為左上
				send(ul);
				Serial.println("up and left");
				break;
			case -9:	//當為右下
				send(dr);
				Serial.println("down and right");
				break;
			case -11:	//當為左下
				send(dl);
				Serial.println("down and left");
				break;
			case 0:		//當為中間
				send(st);
				//Serial.println("stop");
				break;
		}
	}
	delay(500);
	last_mode=mode;
	
}
