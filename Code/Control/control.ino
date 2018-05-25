#include <Wire.h>
#include <BH1750.h>

//Pin Assignments
int solenoidPin = 2;
int analogPin1 = A0;
int analogPin2=A1;

BH1750 lightMeter;
int val1=0;
int val2=0;

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(solenoidPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  // On esp8266 devices you can select SCL and SDA pins using Wire.begin(D4, D3);
  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test"));
}

void loop() {
  //Reading knobs
  val1 = analogRead(analogPin1);
  val2 = analogRead(analogPin2);
  serial.println(val1);
  serial.println(val2);
  
  //BH1750
  uint16_t lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
  
  //solenoid
  digitalWrite(solenoidPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(solenoidPin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  
  //blink
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);          
}
