long pulse1, sensor1;
const int pwPin1 = 1; //the pin the distance sensor is routed to.


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



}

void read_sensor() {
  pulse1 = pulseIn(pwPin1, HIGH);
  sensor1 = pulse1 / 147; //conversion to mm.
}

//This section of code is if you want to print the range readings to your computer too remove this from the code put /* before the code section and */ after the code
void printall() {
  Serial.println(sensor1); //simplified datastream. Only the numbers go to Processing. /
  //note it is println !!! must execute a new line 

}
