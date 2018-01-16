// Pins for Motor B
const int right_BB = 5;
const int right_BA = 6;

// Pins for Motor A
const int left_AB = 9;
const int left_AA = 10;

// Pins for sensor inputs
const int right_sens = 7;
const int left_sens = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Setup pins -----
  // Motors
  pinMode(right_BB, OUTPUT);
  pinMode(right_BA, OUTPUT);
  pinMode(left_AB, OUTPUT);
  pinMode(left_AA, OUTPUT);

  // Sensors
  pinMode(right_sens, INPUT);
  pinMode(left_sens, INPUT);
  
  // -----
}

void loop() {
  // put your main code here, to run repeatedly:
  if(left_sens == LOW && right_sens == LOW)
  {
    // Forward ------
    wheelsForward();
    // -----
  }
  // Sensors check
  else if(left_sens == HIGH || right_sens == HIGH)
  {
    // If both sensors are HIGH, both detect black.
    // Happens at "T" and "+" junctions.
    //
    while(left_sens == HIGH && right_sens == HIGH)
    {
      // do something like stop
    }

    // If left sensor is HIGH, detects the black line, adjust left.
    // Turn left until input goes low.
    while(left_sens == HIGH && right_sens == LOW)
    {
      // Pivot Left
      wheelsPivotLeft();
    }

    // If right sensor is HIGH, detects the black line, adjust right.
    // Turn right until input goes low.
    while(left_sens == LOW && right_sens == HIGH)
    {
      // Pivot Right
      wheelsPivotRight();
    }
  }
}

// Wheel controls start -----

void wheelsForward()
{
  digitalWrite(left_AB, HIGH);
  digitalWrite(left_AA, LOW);   // Opposite of L911OS chart
  
  digitalWrite(right_BB, LOW);
  digitalWrite(right_BA, HIGH); // Same as L911OS chart
}

void wheelsPivotLeft()
{
  // Stop left wheel
  digitalWrite(left_AB, LOW);
  digitalWrite(left_AA, LOW);
  
  // Keep right wheel turning
  digitalWrite(right_BB, LOW);
  digitalWrite(right_BA, HIGH);
}

void wheelsPivotRight()
{
  // Keep right wheel turning
  digitalWrite(left_AB, HIGH);
  digitalWrite(left_AA, LOW);
  
  // Stop right wheel
  digitalWrite(right_BB, LOW);
  digitalWrite(right_BA, LOW);
}

// Wheel controls end -----
