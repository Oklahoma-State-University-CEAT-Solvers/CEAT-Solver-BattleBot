//Code for Oklahoma State Battlebots Robot

//System control variables
#define LOOP_DELAY  100
int maxSpeed;

// Radio Input Connections
#define CH1 2 //Right stick horizontal
#define CH2 3 //Right stick vertical
#define CH3 4 //Left stick vertical
#define CH4 5 //Left stick horizontal
#define CH5 6 //Left potentiometer
#define CH6 7 //Right potentiometer

//Motor Bridge Connections
#define ENA 8
#define IN1 9
#define IN2 10
#define ENB 11
#define IN1 12
#define IN2 13

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
  Serial.begin(115200);

  //Set radio pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);

  //Set motor pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  resetMotors();

}

void loop()
{
  readRadioValues();
  printRadioValues();
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
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, -100);
  ch4Value = readChannel(CH4, -100, 100, 0);
  ch5Value = readChannel(CH5, -100, 100, 0);
  ch6Value = readChannel(CH6, -100, 100, 0);
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
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

//CH 5 is a throttle limit
//CH 2 is for forwards and backwards
//CH 4 is for left and right
void channelMapping()
{
  
}
