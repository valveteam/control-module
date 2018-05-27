#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

//INITIALISATION
//Pin Assignments
int dviPin = 4;
int enPin = 5;
int intPin = 6;
int sPin1 = 8;
int sPin2 = 9;
int sPin3 = 10;
int sPin4 = 11;
int debugPin1 = 12;
int debugPin2 = 13;
int analogPin1 = A0;
int analogPin2 = A1;
//Variables
int lbound = 0;
int ubound = 0;
int tau = 0;
uint16_t lux = 0;

//SETUP
void setup() 
{
  Serial.begin(9600);

  // put your setup code here, to run once:
  pinMode(dviPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(intPin, OUTPUT);
  pinMode(sPin1, OUTPUT);
  pinMode(sPin2, OUTPUT);
  pinMode(sPin3, OUTPUT);
  pinMode(sPin4, OUTPUT);
  pinMode(debugPin1, OUTPUT);
  pinMode(debugPin2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  // On esp8266 devices you can select SCL and SDA pins using Wire.begin(D4, D3);
  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test"));

  //Setup of valve is OFF
  digitalWrite(sPin1, LOW);
  digitalWrite(sPin2, LOW);
  digitalWrite(sPin3, LOW);
  digitalWrite(sPin4, LOW);

  //tuning circuit
  lbound = analogRead(analogPin1) + 500; // lower bound from 500 - 1500
  ubound = (analogRead(analogPin2)*2) + 19000; //upper bound from 19000 - 21000
}

//LOOP
void loop() 
{
  //BH1750 - reading light levels
  lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  
  //Reading knobs & calculating tau wrt to lux levels
  if(lux > ubound)
  {
    tau = 1000;
  }
  else
  {
    tau = 1000*(lux/ubound);
  };
  //serial.println(val1);
  //serial.println(val2);

  //control for solenoid
  //TO BE COMPLETED
  if(tau<lbound)
  {
    //turning solenoid off
    digitalWrite(sPin2, LOW);
    digitalWrite(sPin3, LOW);
  }
  else
  {
    //turning on with some PWM
    digitalWrite(sPin2, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(tau);                       // wait for a second
    digitalWrite(sPin3, LOW);    // turn the LED off by making the voltage LOW
    delay(1000-tau);
  };
  
  //blink
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
