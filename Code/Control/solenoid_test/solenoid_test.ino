//Pin Assignments
int sPin2 = 9;
int sPin3 = 10;
//Variables
float lbound = 500;
float ubound = 19000;
float tau = 0;
uint16_t lux = 0;

//SETUP
void setup() 
{
  Serial.begin(9600);

  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  //Setup of valve is OFF
  digitalWrite(sPin2, LOW);
  digitalWrite(sPin3, LOW);
}

//LOOP
void loop() 
{
  //reading light levels
  lux = 5000;
  
  //Reading knobs & calculating tau wrt to lux levels
  if(lux > ubound)
  {
    tau = 1000;
  } else
  {
    tau = (1000*(lux/(ubound+lbound)));
  };
  
  //control for solenoid
  if(lux<lbound)
  {
    //turning solenoid off
    digitalWrite(sPin2, LOW);
    digitalWrite(sPin3, LOW);
    digitalWrite(LED_BUILTIN, LOW); 
  } else
  {
    //turning on with some PWM
    digitalWrite(sPin2, HIGH);
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(tau);                       
    digitalWrite(sPin3, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000-tau);
  };
}
