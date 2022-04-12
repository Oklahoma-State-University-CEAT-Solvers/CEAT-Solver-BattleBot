//Code for Oklahoma State Battlebots Robot

//System control variables
#define LOOP_DELAY  10
#define INPUT_SENSITIVITY 10
#define WEAPON_INPUT_SENSITIVITY  20
#define DISCONNECT_SENSITIVITY  600
int maxSpeed;

// Radio Input Connections
#define CH1 2 //Right stick horizontal
#define CH2 3 //Right stick vertical
#define CH3 4 //Left stick vertical
#define CH4 5 //Left stick horizontal
#define CH5 6 //Left potentiometer
#define CH6 7 //Right potentiometer

//Motor Bridge Connections
#define ENA 9
#define IN1 8
#define IN2 A0
#define ENB 10
#define IN3 12
#define IN4 13

//Speed Controller Pins
#define SPEED_PIN 11

//Disconnect pin
#define DISCONNECT  A1

//Radio Communication values
int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value;
int ch5Value;
int ch6Value;

void setup()
{
  //Set up serial monitor
  Serial.begin(9600);

  //Set radio pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);

  //Set motor pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //Set Speed Controller pin 
  pinMode(SPEED_PIN, OUTPUT);

  resetMotors();

}

void loop()
{
  readRadioValues();
  printRadioValues();
  drive();
  weaponSpin(ch5Value);
  int val = analogRead(DISCONNECT);
  if(val >= 600)
    {
      shutoff();
    }
  delay(LOOP_DELAY);
}


// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue)
{
  int ch = pulseIn(channelInput, HIGH, 30000); //30,000 microsecond width
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void readRadioValues()
{
  ch1Value = readChannel(CH1, -255, 255, 0);
  ch2Value = readChannel(CH2, -255, 255, 0);
  ch3Value = readChannel(CH3, 0, 255, 0);
  ch4Value = readChannel(CH4, -255, 255, 0);
  ch5Value = readChannel(CH5, 0, 255, 0);
  ch6Value = readChannel(CH6, 0, 255, 0);
  maxSpeed = ch6Value;
}

void printRadioValues()
{
  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" | Ch2: ");
  Serial.print(ch2Value);
  Serial.print(" | Ch3: ");
  Serial.print(ch3Value);
  Serial.print(" | Ch4: ");
  Serial.print(ch4Value);
  Serial.print(" | Ch5: ");
  Serial.print(ch5Value);
  Serial.print(" | Ch6: ");
  Serial.println(ch6Value);
}

void resetMotors()
{
  // Turn off motors - Initial state
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void turnOnLeftMotorForward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void turnOnRightMotorForward()
{
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnOnLeftMotorBackwards()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void turnOnRightMotorBackwards()
{
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnOnMotorsForward()
{
  turnOnLeftMotorForward();
  turnOnRightMotorForward();
}

void turnOnMotorsBackwards()
{
  turnOnLeftMotorBackwards();
  turnOnRightMotorBackwards();
}

void drive()
{
  driveStraight(ch2Value);
  turn(ch1Value);
}

void driveStraight(int speedVal)
{
  if (abs(speedVal) > INPUT_SENSITIVITY)
  {
    if (speedVal < 0)
      turnOnMotorsBackwards();
    else
      turnOnMotorsForward();
  }
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);
    else
      resetMotors();
}

void turn(int speedVal)
{
  if (abs(speedVal) > INPUT_SENSITIVITY)
  {
    if (speedVal < 0) //stick is turned left, should turn left
    {
      turnOnLeftMotorBackwards();
      turnOnRightMotorForward();
    }
    else
    {
      turnOnLeftMotorForward();
      turnOnRightMotorBackwards();
    }
    analogWrite(ENA, speedVal);
    analogWrite(ENB, speedVal);
  }
    else
      resetMotors();
}

void weaponSpin(int spinSpeed)
{
  if(spinSpeed > WEAPON_INPUT_SENSITIVITY)
    analogWrite(SPEED_PIN, spinSpeed);
  else
    analogWrite(SPEED_PIN, 0);
  
}

void shutoff()
{
  resetMotors();
  weaponSpin(0);
  Serial.println("POSSIBLE EMERGENCY SHUTOFF!");
  delay(9999999999999);
}
