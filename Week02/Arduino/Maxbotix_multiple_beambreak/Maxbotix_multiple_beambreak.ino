/*
  Code written by Jen Sykes
  Triggers multiple sensors in differring combinations to imitate gesture.

  Multiple Maxbotix Sensor reading adapted from
  code by Tom Bonar for testing
  Sensors being used for this code are the MB10X0 from MaxBotix
  All PW inputs are coded in this for simplicity.

*/

#define THRESHOLD 10

const int pwPin1 = 3;
const int pwPin2 = 4;
//const int pwPin3 = 10;
const int triggerPin = 13;
long pulse1, pulse2, pulse3, sensor1, sensor2, sensor3, inches;
boolean beam1, beam2, beam3;
int state;

void setup () {
  Serial.begin(9600);
  pinMode(pwPin1, INPUT);
  pinMode(pwPin2, INPUT);
  pinMode(pwPin3, INPUT);

  pinMode(triggerPin, OUTPUT);

  beam1 = false;//set all beams to not be broken/false
  beam2 = false;
  //beam3 = false;

}

void read_sensor() {
  pulse1 = pulseIn(pwPin1, HIGH);
  pulse2 = pulseIn(pwPin2, HIGH);
  // pulse3 = pulseIn(pwPin3, HIGH);

  sensor1 = pulse1 / 147;
  sensor2 = pulse2 / 147;
  // sensor3 = pulse3 / 147;

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
  //  Serial.print(" ");
  //  Serial.print("S3");
  //  Serial.print(" ");
  //  Serial.print(sensor3);
  Serial.println(" ");
}

void beamBreak() {
  //is an object under the threshold(in the zone)
  //is the beam broken?
  if ((sensor1 != 0) && (sensor1 < THRESHOLD)) {
    beam1 = true;

  }

  if ((sensor2 != 0) && (sensor2 < THRESHOLD)) {
    beam2 = true;

  }

  //  if ((sensor3 != 0) && (sensor3 < THRESHOLD)) {
  //    beam3 = true;
  //
  //  }



}

void delayTime(int time) {
  int current = millis();
  while (millis () < current + time) yield();
}

void gestures() {
  //set your gestures here:

  if ((beam1) && (beam2)) { //first 2 sensors triggered
    state = 1;
    beam1 = false;
    beam2 = false;


  }

  if ((!beam1) && (beam2)) { //last 2 sensors triggered
    state = 2;
    beam1 = false;
    beam2 = false;
  }

  if ((beam1) && (!beam2)) { //all sensors triggered
    state = 3;
    beam1 = false;
    beam2 = false;

  }

  //explore making different combinations true/false
  //try making a state where none are triggered
}
void loop () {
  start_sensor();
  read_sensor();
  printall();
  beamBreak();
  gestures();

  switch (state) {
    case 1:
      //put your event/output here.
      break;
    case 2:
      //put your event/output here.
      break;
    case 3:
      //put your event/output here.
      break;



  }
  //check what state is triggered.
  Serial.print("state: ");
  Serial.println(state);

  delay(150); // This delay time changes by 50 for every sensor in the chain.  For 5 sensors this will be 250
}
