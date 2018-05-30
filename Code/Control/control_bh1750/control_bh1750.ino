#include <Wire.h>
#include <BH1750.h>

// address from datasheet
BH1750 lightMeter(0x5c);

//INITIALISATION
//Pin Assignments
int dviPin = 4;
int en1Pin = 5;
int en2Pin = A2;
int intPin = 6;
int sPin1 = 8;
int sPin2 = 9;
int sPin3 = 10;
int sPin4 = 11;
int debugPin1 = 12;
int debugPin2 = 13;
int analogPin1 = A0;
int analogPin2 = A1;
int analogPin3 = A3;

//Variables
float lBound = 0;
float uBound = 0;
float pWidth = 0;
float tau=0;
uint16_t lux = 0;

//SETUP
void setup() 
{
  Serial.begin(9600);

  // put your setup code here, to run once:
  pinMode(dviPin, OUTPUT);
  pinMode(en1Pin, OUTPUT);
  pinMode(en2Pin, OUTPUT);
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
}

//LOOP
void loop() 
{ 
  //Changing pulse width
  // note that analog read is between 0 and 1023
  pWidth = 1000 + (9000*analogRead(analogPin3)/1023); //goes from 1 Hz to 0.1 Hz.
  
  //tuning circuit
  lBound = analogRead(analogPin1) + 500; // lower bound from 500 - 1523
  uBound = (analogRead(analogPin2)*2) + 19000; //upper bound from 19000 - 21046 
  
  //BH1750 - reading light levels
  lux = lightMeter.readLightLevel();
  Serial.print("Light: ");  
  Serial.println(lux);

  //Reading knobs & calculating tau wrt to lux levels
  if(lux > uBound) //abpods tau being larger than pWidth
  {
    //solenoid fully open
    digitalWrite(sPin2, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(pWidth);
  } else if(lux < lBound) //avoids the negative tau values
  {
    //solenoid fully closed
    digitalWrite(sPin2, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    delay(pWidth);
  } else
  {
    //solenoid varying
    tau = pWidth*((lux-lBound)/(uBound-lBound)); //goes to zero when lux is at lBound and to one when lux is at uBound
    digitalWrite(sPin2, HIGH);
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(tau);                       
    digitalWrite(sPin2, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    delay(pWidth-tau);
  };
}
