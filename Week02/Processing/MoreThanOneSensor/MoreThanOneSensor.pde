/* Processing code for this example
 Code for recieving more than one data variable via serial communication
 by Jen Sykes
 Adapted from the virtual colour mixer example in Arduino.
 This example code is in the public domain.
 */
import processing.serial.*;

float sensor1 = 0;        // red value
float sensor2 = 0;      // green value
float sensor3 = 0;       // blue value

int minThreshold=5; //set your min and max range for your sensor
int maxThreshold=60;// easier to change all the mapping inputs up here than in x amount of lines of code below. 


Serial myPort;

void setup() {
  size(200, 200);

  // List all the available serial ports
  printArray(Serial.list());

  // I know that the first port in the serial list on my Mac is always my
  // Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[0], 9600);

  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
}

void draw() {
  //note the sensor values have already been mapped in the SerialEvent()

  // set the background color with the new values:
  background(sensor1, sensor2, sensor3);
}


//get the serial information. 
void serialEvent(Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n'); //new line

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // split the string on the commas and convert the resulting substrings
    // into an integer array:
    float[] sensors = float(split(inString, ","));
    // if the array has at least three elements, you know you got the whole
    // thing.  Put the numbers in the sensor variables:
    if (sensors.length >= 3) {
      // map them to the range 0-255:
      sensor1 = map(sensors[0], minThreshold, maxThreshold, 0, 255);
      sensor2 = map(sensors[1], minThreshold, maxThreshold, 0, 255);
      sensor3 = map(sensors[2], minThreshold, maxThreshold, 0, 255);
    }
  }
}
