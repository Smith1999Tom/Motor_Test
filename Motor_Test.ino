const int motorPin = 9;
const int potPin = 2;
const int buttonPin = 4;
int potValue = 0;

int buttonPreviousState = 0;
int buttonCurrentState = 0;
boolean buttonLatch = false;

boolean runProgram = false;

void setup()
{
  // Set up the motor pin to be an output:
  pinMode(motorPin, OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  
}
void loop()
{
  determineButtonState();
  if(runProgram)
  {
    motorOnThenOffWithSpeed();
  }
  delay(50);
  
}
void motorOnThenOffWithSpeed()
{
  float potValue = analogRead(potPin);  //Get value(0-1024) of potentiometer
  
  float Speed1 = (255)*(potValue/1024);  // between 0 (stopped) and 255 (full speed)
  int Time1 = 1500;  // milliseconds for speed 1
  Serial.println(potValue, DEC);
  Serial.println(Speed1, DEC);
  analogWrite(motorPin, Speed1);  // turns the motor On
  delay(Time1);                   // delay for onTime milliseconds
  
  float Speed2 = Speed1/4;   // between 0 (stopped) and 255 (full speed)
  int Time2 = 1500;  // milliseconds to turn the motor off
  analogWrite(motorPin, Speed2);  // turns the motor Off
  delay(Time2);                   // delay for offTime milliseconds
}

void determineButtonState()
{
  buttonCurrentState = digitalRead(buttonPin);

  if(buttonCurrentState != buttonPreviousState)
  {
    if(buttonCurrentState == HIGH && buttonLatch == false)
    {
      runProgram = true;
      buttonLatch = true;
    }
    else if (buttonCurrentState == HIGH && buttonLatch == true)
    {
      runProgram = false;
      buttonLatch = false;
    }
   buttonPreviousState = buttonCurrentState;
    
  }

  
}

