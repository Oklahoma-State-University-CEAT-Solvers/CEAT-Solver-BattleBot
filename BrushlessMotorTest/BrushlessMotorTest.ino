#define SPEED 3


void setup() {
  // put your setup code here, to run once:
  pinMode(SPEED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(SPEED, 255);
  delay(1000);
  analogWrite(SPEED, 0);
  delay(1000);
  

}
