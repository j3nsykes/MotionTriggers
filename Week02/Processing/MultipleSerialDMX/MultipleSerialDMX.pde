/**
 * Many Serial Ports
 * 
 * Read data from the multiple Serial Ports
 *
 *DMX controls for lights 
 
 QTX Par Can 64
 channel 1= bulb on 
 channel 5 = red
 channel 6 = blue
 channel 7 = green
 
 
 Showtech Sunstrip:
 channel= bulb number
 brightness 0-255
 
 */


import processing.serial.*;

Serial[] myPorts = new Serial[2];  // Create a list of objects from Serial class
String val = null; // Data received from the serial port
int lf = 10;    // Linefeed in ASCII
String lastSensorString = "";
int sensorIntReading = 0;
int mousePos; 

void setup() {
  size(400, 300);
  // print a list of the serial ports:
  printArray(Serial.list());
  // On my machine, the first and third ports in the list
  // were the serial ports that my microcontrollers were 
  // attached to.
  // Open whatever ports ares the ones you're using.

  // get the ports' names:
  String portOne = Serial.list()[1];
  String portTwo = Serial.list()[2];
  // open the ports:
  myPorts[0] = new Serial(this, portOne, 9600);
  myPorts[1] = new Serial(this, portTwo, 9600);

  //initialise communiction over serial
  setDmxChannel(123, 45);

  // You may have to set other channels. Some lamps have a shutter channel that should be set to 255. 
  //Set it here: 
  setDmxChannel(1, 255);
  //find out what channel and values these require.
}

void setDmxChannel(int channel, int value) { // Convert the parameters into a message of the form: 123c45w where 123 is the channel and 45 is the value // then send to the Arduino 
  myPorts[1].write( str(channel) + "c" + str(value) + "w" );
}

void draw() {
  getSensorInput(); //read Serial input from sensor
  sendDMX(); //send Serial data out to DMX

  // clear the screen:
  background(0);

  // use the latest byte from port 0 for the first circle
  fill(255);
  ellipse(width/3, height/2, sensorIntReading, sensorIntReading); //visualise data coming in
}

void getSensorInput() {
  if (myPorts[0].available () > 0) {
    val = myPorts[0].readStringUntil(lf);
    if (val != null) { //if my input is not emptry
      String s = trim(val); // your data!
      if (lastSensorString.equals(s) == false) { // if your data isn't the same it is your new data!
        lastSensorString = s; // update and remember this reading
        int newSensorIntReading = int(s); // convert it to integer(whole number) to be useful
        if (newSensorIntReading != -1) { // Helps avoid random false positive input
          sensorIntReading = newSensorIntReading;
          //   println(sensorIntReading);
        }
      }
    }
  }
}



void sendDMX() {


  mousePos = (255 * mouseX / width);// Use cursor Y position to get channel 2 value 

  //the channel can be changed as to what DMX light result you want 
  //setDmxChannel(5, mousePos);  // Send new channel values to Arduino 
  setDmxChannel(1, sensorIntReading);  // Send new channel values to Arduino 
  //try also using your sensor data to control the value
  //float inputVal= map(data,5,60,0,255); //map it to be within a value range
  //setDmxChannel(1, inputVal);  // Send new channel values to Arduino 


  // You may have to set other channels. Some lamps have a shutter channel that should be set to 255. 
  // Set it here: setDmxChannel(4,255);

  delay(20); // Short pause before repeating
}
