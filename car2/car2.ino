boolean red=false;
#define r1 5
#define r2 6
#define l1 3
#define l2 4

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

void setmotor(int A, int B) {
	//Serial.print(A);
	//Serial.print(",");
	//Serial.println(B);
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
  Serial.println("begin");
  for (int i = 2; i < 7; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(12,OUTPUT);

}

void loop() {
	int mode = analogRead(A0);
	mode = map(mode,0,1024,0,9);
  Serial.println(mode);
    // put your main code here, to run repeatedly:
    switch(mode){
		case up:   //前進
			//Serial.println("up");
			setmotor(255, 255);
			delay(0);    
			break;
        case dw:   //後退
			//Serial.println("down");
			setmotor(-255, -255);
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
			setmotor(0,150);
			break;
		case ul:  	//左上
			setmotor(150,0);
			break;
		case dr:	//右下
			setmotor(0,-150);
			break;
		case dl:	//左下
			setmotor(-150,0);
			break;
        case b1:  //LEDred
			red= !red;
			digitalWrite(12,red);
			break;
        case b2:   //蜂鳴器
			analogWrite(9,200);
			delay(0);
			analogWrite(9,0);
			break;
		default:   //停車
			setmotor(0, 0);
			break;
		}
    delay(1000);
}

