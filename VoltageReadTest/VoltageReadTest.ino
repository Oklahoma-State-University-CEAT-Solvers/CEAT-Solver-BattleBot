#define VPIN A1
//#define period  100
#define trigger 300
int periodCount = 0;
int average = 0;
int sum = 0;

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  startMillis = millis();
  //pinMode(VPIN, INPUT);
  //analogReadResolution(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  if (currentMillis - startMillis >= period)
  {
    

  }
    int val = analogRead(VPIN);
    Serial.println(val);
    if(val >= 600)
    {
      Serial.println("SHUTOFF!!!");
      delay(99999999999);
    }



}
