/*
  Test code for the Arduino Uno
  Written by Tom Bonar for testing
  Sensors being used for this code are the MB10X0 from MaxBotix
  All PW inputs are coded in this for simplicity.
  Remove the comments to use the additional sensor inputs
*/
const int pwPin1 = 3;
const int pwPin2 = 4;
const int pwPin3 = 10;
//const int pwPin4 = 9;
//const int pwPin5 = 10;  // This is the 5th pin that would allow for PW input
//const int pwPin6 = 11;  // This is the 6th pin that would allow for PW intput
const int triggerPin = 13;
long pulse1, pulse2, pulse3, pulse4, pulse5, pulse6, sensor1, sensor2, sensor3, sensor4, sensor5, sensor6, inches;

void setup () {
  Serial.begin(9600);
  pinMode(pwPin1, INPUT);
  pinMode(pwPin2, INPUT);
  pinMode(pwPin3, INPUT);
  //pinMode(pwPin4, INPUT);
  //pinMode(pwPin5, INPUT);
  //pinMode(pwPin6, INPUT);
  pinMode(triggerPin, OUTPUT);
}

void read_sensor() {
  pulse1 = pulseIn(pwPin1, HIGH);
  pulse2 = pulseIn(pwPin2, HIGH);
  pulse3 = pulseIn(pwPin3, HIGH);
  //  pulse4 = pulseIn(pwPin4, HIGH);
  //pulse5 = pulseIn(pwPin5, HIGH);
  //pulse6 = pulseIn(pwPin6, HIGH);
  sensor1 = pulse1 / 147;
  sensor2 = pulse2 / 147;
  sensor3 = pulse3 / 147;
  //  sensor4 = pulse4/147;
  //sensor5 = pulse5/147;
  //sensor6 = pulse6/147;
}

void start_sensor() {
  digitalWrite(triggerPin, HIGH);
  delay(1);
  digitalWrite(triggerPin, LOW);
}

//This section of code is if you want to print the range readings to your computer too remove this from the code put /* before the code section and */ after the code
void printall() {
  Serial.print("S1");
  Serial.print(" ");
  Serial.print(sensor1);
  Serial.print(" ");
  Serial.print("S2");
  Serial.print(" ");
  Serial.print(sensor2);
  Serial.print(" ");
  Serial.print("S3");
  Serial.print(" ");
  Serial.print(sensor3);
  /*
    Serial.print("S4");
    Serial.print(" ");
    Serial.print(sensor4);
    Serial.print("S5");
    Serial.print(" ");
    Serial.print(sensor5);
    Serial.print("S6");
    Serial.print(" ");
    Serial.print(sensor6);*/
  Serial.println(" ");
}

void loop () {
  start_sensor();
  read_sensor();
  printall();
  delay(100); // This delay time changes by 50 for every sensor in the chain.  For 5 sensors this will be 250
}
