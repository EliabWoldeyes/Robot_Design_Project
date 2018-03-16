  //motor pins
  #define B_DIR 9
  #define B_PWM 10
  
  #define A_DIR 6
  #define A_PWM 5
  
void setup() {
  // put your setup code here, to run once:
  // serial bits
  Serial.begin(9600);
  // Pin setup
  // Motors
  pinMode(B_DIR, OUTPUT);
  pinMode(B_PWM, OUTPUT);
  pinMode(A_DIR, OUTPUT);
  pinMode(A_PWM, OUTPUT);

}

void loop() {

 digitalWrite(B_DIR, LOW);
 digitalWrite(A_DIR, LOW);
 analogWrite(B_PWM, 120);
 analogWrite(A_PWM, 120);
}
