int solenoidPin1 = 11;
int solenoidPin2 = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); 
  
  pinMode(solenoidPin1, OUTPUT);
  pinMode(solenoidPin2, OUTPUT);
  solenoidPin2 = HIGH;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  
  digitalWrite(solenoidPin1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(250);                       // wait for a second
  digitalWrite(solenoidPin1, LOW);    // turn the LED off by making the voltage LOW
  delay(250);
}
