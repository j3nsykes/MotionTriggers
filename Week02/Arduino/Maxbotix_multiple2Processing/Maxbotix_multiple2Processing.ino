/*
  Test code for the Arduino Uno
  Written by Tom Bonar for testing
  Sensors being used for this code are the MB10X0 from MaxBotix
  All PW inputs are coded in this for simplicity.
  Remove the comments to use the additional sensor inputs

  Sketch adapted by Jen Sykes for 3 comma separated sensor values to be sent to Processing. 
*/
const int pwPin1 = 1;
const int pwPin2 = 2;
const int pwPin3 = 3;

const int triggerPin = 13;
long pulse1, pulse2, pulse3,, sensor1, sensor2, sensor3, inches;

void setup () {
  Serial.begin(9600);
  pinMode(pwPin1, INPUT);
  pinMode(pwPin2, INPUT);
  pinMode(pwPin3, INPUT);

  pinMode(triggerPin, OUTPUT);
}

void read_sensor() {
  pulse1 = pulseIn(pwPin1, HIGH);
  pulse2 = pulseIn(pwPin2, HIGH);
  pulse3 = pulseIn(pwPin3, HIGH);

  sensor1 = pulse1 / 147;
  sensor2 = pulse2 / 147;
  sensor3 = pulse3 / 147;

}

void start_sensor() {
  digitalWrite(triggerPin, HIGH);
  delay(1);
  digitalWrite(triggerPin, LOW);
}

//This section of code is if you want to print the range readings to your computer too remove this from the code put /* before the code section and */ after the code
void printall() {
  Serial.print(sensor1);
  Serial.print(","); //note the separation by a comma.
  //This is important so Processing can read it correctly!
  Serial.print(sensor2);
  Serial.print(",");
  Serial.println(sensor3); //important the last value is println not print!

}

void loop () {
  start_sensor();
  read_sensor();
  printall();
  delay(150); // This delay time changes by 50 for every sensor in the chain.  For 5 sensors this will be 250
}
