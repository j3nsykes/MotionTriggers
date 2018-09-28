long pulse1, sensor1;
const int pwPin1 = 1; //the pin the distance sensor is routed to.
const int motor = 2;

void setup() {
  // put your setup code here, to run once:
  //initialise the inputs and outputs.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pwPin1, INPUT);

  Serial.begin(9600); //open the serial port
}

void loop() {

  //run the functions
  read_sensor();
  printall();
  delay(50); //arbitary delay to control influx of data

  //control an output here:
  if (sensor1 < 40) { //if the sensor reading is under 40 turn the light ON
    analogWrite(LED_BUILTIN, 255);
  }
  else {
    analogWrite(LED_BUILTIN, 100);
  }
}

void read_sensor() {
  pulse1 = pulseIn(pwPin1, HIGH);
  sensor1 = pulse1 / 147; //conversion to mm.
}

//This section of code is if you want to print the range readings to your computer too remove this from the code put /* before the code section and */ after the code
void printall() {
  Serial.print("S1");
  Serial.print(" ");
  Serial.print(sensor1);
  Serial.println(" ");
}
