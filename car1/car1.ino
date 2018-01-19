#include <IRremote.h>
int RECV_PIN = 11;
boolean red=false;
IRrecv re(RECV_PIN);
decode_results results;
#define r1 6
#define r2 5
#define l1 4
#define l2 3

#define st 0x1FAEC0E9
#define up 0xBAD3529A
#define dw 0x4B3DE971
#define rt 0x86496FDA
#define lt 0x2AC4BB31
#define ur 0xDB37230C
#define ul 0xDB37230F
#define dr 0xD397D03E
#define dl 0xD397D03D

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
void setup() {
  // put your setup codree here, to run once:
  Serial.begin(9600);
  re.blink13(true);
  re.enableIRIn();
  Serial.println("begin");
  for (int i = 2; i < 7; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(12,OUTPUT);

}

void loop() {
  
    // put your main code here, to run repeatedly:
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

