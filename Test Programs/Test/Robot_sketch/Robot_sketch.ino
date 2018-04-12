  // right motor B pins
  const int right_BB = 5;
  const int right_BA = 6;

  // left motor A pins
  const int left_AB = 9;
  const int left_AA = 10;

  //IR sensor input pins
  const int right_sens = 7;
  const int left_sens = 8;

  
void setup() {
  // put your setup code here, to run once:
  // serial bits
  Serial.begin(9600);
  // Pin setup
  // Motors
  pinMode(right_BB, OUTPUT);
  pinMode(right_BA, OUTPUT);

  pinMode(left_AB, OUTPUT);
  pinMode(left_AA, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(left_sens)==HIGH){
    digitalWrite(right_BB, LOW);
    digitalWrite(right_BA, HIGH);
    digitalWrite(left_AA, LOW);
    digitalWrite(left_AB, LOW);
  delay(2000);
    }
    digitalWrite(right_BB, LOW);
    digitalWrite(right_BA, LOW);
    delay(2000);
 /* 
  //analogWrite(left_BB, 255);
  //analogWrite(left_BA, 0);

  digitalWrite(right_BB, LOW);
  digitalWrite(right_BA, HIGH);
  
  //analogWrite(right_AA, 255);
  //analogWrite(right_AB, 0);

  digitalWrite(left_AB, HIGH);
  digitalWrite(left_AA, LOW);

  delay(1000);
  digitalWrite(right_BB, LOW);
  digitalWrite(right_BA, LOW);
  
  //analogWrite(right_AA, 255);
  //analogWrite(right_AB, 0);

  digitalWrite(left_AB, LOW);
  digitalWrite(left_AA, LOW);

  delay(1000);
*/ 
}
