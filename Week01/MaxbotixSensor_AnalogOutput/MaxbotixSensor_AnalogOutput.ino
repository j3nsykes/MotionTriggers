long pulse1, sensor1;
const int pwPin1 = 1; //the pin the distance sensor is routed to.
const int motor = 3; //the output pin for a light or motor. 

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

  int brightness = map(sensor1, 2, 100, 0, 255);
  analogWrite(motor, brightness);
  
  delay(50); //arbitary delay to control influx of data



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
