// Arduino PWM Speed Control： 
int E1 = 10;   // Enable pin for right motor
int M11 = 2;   // Speed control pin for left motor
int M12 = 4;   // Speed control pin for left motor
int E2 = 11;   // Enable pin for the left motor
int M21 = 7;   // Speed control pin for right motor
int M22 = 3;   // Speed control pin for left motor

// The following motor speeds are determined by experiment
// so that the robot moves forward in a straight line.
int leftMotorSpeed = 215;
int rightMotorSpeed = 185;

int sensorPinRight = A0;  // Right sensor pin
int sensorPinCenter = A1;  // Center sensor pin
int sensorPinLeft = A2;  // Left sensor pin

int lightReadingRight;
int lightToleranceRight = 1000;  // Sensor reading needed to trigger right turn

int lightReadingCenter;
int lightToleranceCenter = 1000;  // Sensor reading needed to trigger forward movement

int lightReadingLeft;
int lightToleranceLeft = 1000;  // Sensor reading needed to trigger left turn

int readingDelay = 100;  // Delay between readings

void setup()
{
  pinMode(M11,OUTPUT);
  pinMode(M12,OUTPUT);
  pinMode(M21,OUTPUT);
  pinMode(M22,OUTPUT);
  pinMode(E1,OUTPUT);
  pinMode(E2,OUTPUT); 

pinMode(sensorPinRight,INPUT);
pinMode(sensorPinCenter,INPUT);
pinMode(sensorPinLeft,INPUT);

//  Uncomment the serial feed for testing if need be
  Serial.begin(9600);
}

void loop()
{
// Uncomment the serial print lines for calibration purposes

// Take reading from right sensor
  lightReadingRight = analogRead(sensorPinRight);
  Serial.print("Right Sensor Reading :");
  Serial.println(lightReadingRight);
  
// Take reading from center sensor
  lightReadingCenter = analogRead(sensorPinCenter);
  Serial.print("Center Sensor Reading :");
  Serial.println(lightReadingCenter);
  
// Take reading from left sensor
  lightReadingLeft = analogRead(sensorPinLeft);
  Serial.print("Left Sensor Reading :");
  Serial.println(lightReadingLeft);


// Move forward if enought light is detected from center sensor
  if (lightReadingCenter > lightToleranceCenter)
  {
      digitalWrite(M11, HIGH);        
      digitalWrite(M12, LOW);
      digitalWrite(M21, HIGH);        
      digitalWrite(M22, LOW);            
      analogWrite(E1, leftMotorSpeed);   
      analogWrite(E2, rightMotorSpeed);
      delay(readingDelay);
      // Stop
      digitalWrite(M11, LOW);
      digitalWrite(M12, LOW);
      digitalWrite(M21, LOW);
      digitalWrite(M22, LOW);
      analogWrite(E1, 0);   
      analogWrite(E2, 0);
  }
  
// Turn right if enough light is detected from right sensor
  if (lightReadingRight > lightToleranceRight)
  {
      digitalWrite(M11, HIGH);        
      digitalWrite(M12, HIGH);  
      digitalWrite(M21, HIGH);        
      digitalWrite(M22, LOW);            
      analogWrite(E1, leftMotorSpeed);  
      analogWrite(E2, rightMotorSpeed);
      delay(readingDelay);
// Stop
      digitalWrite(M11, LOW);
      digitalWrite(M12, LOW);
      digitalWrite(M21, LOW);
      digitalWrite(M22, LOW);
      analogWrite(E1, 0);   
      analogWrite(E2, 0);
  }
  
// Turn left if enough light is detected from left sensor
  if (lightReadingLeft > lightToleranceLeft)
  {
      digitalWrite(M11, HIGH);        
      digitalWrite(M12, LOW);
      digitalWrite(M21, LOW);        
      digitalWrite(M22, LOW);            
      analogWrite(E1, leftMotorSpeed);  
      analogWrite(E2, rightMotorSpeed);
      delay(readingDelay);
// Stop
      digitalWrite(M11, LOW);
      digitalWrite(M12, LOW);
      digitalWrite(M21, LOW);
      digitalWrite(M22, LOW);
      analogWrite(E1, 0);   
      analogWrite(E2, 0);
  }
// delay(5000); // Uncomment this long delay for calibration purposes
}
