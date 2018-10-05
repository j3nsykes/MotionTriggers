/*
  Code adapted from Maxbotix
  Written by Tom Bonar for testing

  Code adapted by Jen Sykes
  to read one sensor and control switch case statements
  sending DMX data

  utilises the DMXsimple library by Paul Stoffrogen
** <number>c : Select DMX channel
** <number>v : Set DMX channel to new value
**
** These can be combined. For example:
** 100c355w : Set channel 100 to value 255.
**
*/

#include <DmxSimple.h>


long pulse1, sensor1;
const int pwPin1 = 1; //the pin the distance sensor is routed to.
int state;
int inByte;

void setup() {
  // put your setup code here, to run once:
  //initialise the inputs and outputs.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pwPin1, INPUT);


  DmxSimple.usePin(3);//initialsie DMX output pin
  DmxSimple.maxChannel(4); //how many channels in total for that light

  //may need to initialise channel and values to open shutters and turn bulbs on
  DmxSimple.write(4, 255);


  Serial.begin(9600); //open the serial port
  Serial1.begin(9600); //open the serial port 1 if your device has ability to use 2 serial ports such as Teensy, Arduino Mega, Due, Zero etc.
}

void loop() {

  //open Serial port DMX is on. 
  while (Serial.available()) { // If data is available to read,
    inByte = Serial.read(); // read it and store it in val

  }
  
  //run the functions
  read_sensor();
  //printall();
  //do something with the data
  //map and constrain sensor data to 4 states.
  state = constrain(map(sensor1, 2, 100, 1, 4), 1, 4);

  switch (state) {
    case 1:
      //put DMX controls in here.
      //They may vary in channel and value number depedning on typoe of light.
      DmxSimple.write(1, 0);
      DmxSimple.write(2, 0);
      break;
    case 2:
      DmxSimple.write(1, 100);
      DmxSimple.write(2, 100);
      break;
    case 3:
      DmxSimple.write(1, 50);
      DmxSimple.write(2, 0);
      break;
    case 4:
      DmxSimple.write(1, 255);
      DmxSimple.write(2, 255);
      break;


  }
  delay(50); //arbitary delay to control influx of data
}

void read_sensor() {
  pulse1 = pulseIn(pwPin1, HIGH);
  sensor1 = pulse1 / 147; //conversion to mm.
}

//This section of code is if you want to print the range readings to your computer too remove this from the code put /* before the code section and */ after the code
void printall() {
  /*
     comment in if your board has more than one serial port
    Serial1.print("S1");
    Serial1.print(" ");
    Serial1.print(sensor1);
    Serial1.println(" ");
  */
}
