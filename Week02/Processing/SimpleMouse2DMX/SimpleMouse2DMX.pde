
/*
Simplified Code provided by jen Sykes. 
 References the DMXSimple library by Paul Stoffregen which is uploaded to an Arduino with DMX output
 https://github.com/PaulStoffregen/DmxSimple
 
 Processing code references example by Peter Knight 
 http://www.tinker.it 05 Mar 2009
 
 
 Some DMX lights commands...
 Showtech Sunstrip:
 channel = bulb
 intensity 0-255
 
 
 Analog Dimmer Box:
 

 
 QTX Par Can 64
 channel 1= bulb on 
 channel 5 = red
 channel 6 = blue
 channel 7 = green
 
 */

import processing.serial.*; // Import Serial library to talk to Arduino 


int data; // create a variable to hold the data we are sending to the Arduino 

int value; //dmx variables
int channel;

Serial myPort; // Send new DMX channel value to Arduino // 

void setDmxChannel(int channel, int value) { // Convert the parameters into a message of the form: 123c45w where 123 is the channel and 45 is the value // then send to the Arduino 
  myPort.write( str(channel) + "c" + str(value) + "w" );
}


void setup() { 
  printArray(Serial.list()); // shows available serial ports on the system 

  // Change 0 to select the appropriate port as required. 
  String portName = Serial.list()[2]; 
  myPort = new Serial(this, portName, 9600);

  size(256, 256); // Create a window
  //initialise communiction over serial
  setDmxChannel(123, 45);

  // You may have to set other channels. Some lamps have a shutter channel that should be set to 255. 
  // Set it here: setDmxChannel(4,255);
  //find out what channel and values these require.
}

void draw() { 

  data = (255 * mouseX / width); // Use cursor X position to get channel 1 value 


  setDmxChannel(channel, data); // Send new channel values to Arduino 



  delay(20); // Short pause before repeating
} 
