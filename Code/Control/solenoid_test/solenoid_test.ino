//Pin Assignments
int sPin2 = 9;
int sPin3 = 10;

int tau = 0;

//SETUP
void setup() 
{
  Serial.begin(9600);

  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  //Setup of valve is OFF
  digitalWrite(sPin2, LOW);
}

//LOOP
void loop() 
{
  tau=1000;
  digitalWrite(sPin3, HIGH);
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(tau);                       
  digitalWrite(sPin3, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000-tau);
}
