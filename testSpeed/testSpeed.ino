
int speed = 120;

// Pins for Motor B
const int right_BB = 5;
const int right_BA = 6;

// Pins for Motor A
const int left_AB = 9;
const int left_AA = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Setup pins -----
  // Motors
  pinMode(right_BB, OUTPUT);
  pinMode(right_BA, OUTPUT);
  pinMode(left_AB, OUTPUT);
  pinMode(left_AA, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

    digitalWrite(right_BB,HIGH);
    digitalWrite(right_BA,LOW);
    digitalWrite(left_AB,LOW);
    digitalWrite(left_AA,HIGH);
  
//  while(speed>=0){
//    Serial.print("Trying speed:");
//    Serial.print(speed,DEC);
//    Serial.print("\n");
//    analogWrite(right_BB,LOW);
//    analogWrite(right_BA,speed);
//    analogWrite(left_AB,speed);
//    analogWrite(left_AA,LOW);
//    delay(500);
//    speed--;
//  }
}
