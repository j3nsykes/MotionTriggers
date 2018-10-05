/*
This example requires theMIDIbus libaray 
 Code adapted by jen Sykes to read a Maxbotix sensor and trigger MIDI notes
 GetSensorInput filtering function referenced from Paul Maguire example. 
 */
import processing.serial.*;
import themidibus.*; //Import the library

MidiBus myBus; // The MidiBus

Serial myPort;  // Create object from Serial class
String val = null; // Data received from the serial port
int lf = 10;    // Linefeed in ASCII
String lastSensorString = "";
int sensorIntReading = 0;
float newDistance, newColour;
int state, lastState;
color col;
boolean triggered =false;
int channel = 0;
int pitch = 64;
int velocity = 127;

void setup() 
{
  size(500, 500);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  printArray(Serial.list()); //print all dveices
  String portName = Serial.list()[3];

  myPort = new Serial(this, portName, 9600);
  myPort.clear();
  val = myPort.readStringUntil(lf);
  val = null;

  //MIDI information
  MidiBus.list(); // List all available Midi devices on STDOUT. This will show each device's index and name.

  // Either you can
  //                   Parent In Out
  //                     |    |  |
  //myBus = new MidiBus(this, 0, 1); // Create a new MidiBus using the device index to select the Midi input and output devices respectively.

  // or you can ...
  //                   Parent         In                   Out
  //                     |            |                     |
  //myBus = new MidiBus(this, "IncomingDeviceName", "OutgoingDeviceName"); // Create a new MidiBus using the device names to select the Midi input and output devices respectively.

  // or for testing you could ...
  //                 Parent  In        Out
  //                   |     |          |
  myBus = new MidiBus(this, -1, "Java Sound Synthesizer"); // Create a new MidiBus with no input device and the default Java Sound Synthesizer as the output device.
}

void draw()
{
  getSensorInput();
  background(0);

  //draw the data to canvas
  textAlign(LEFT, TOP);
  textSize(18);  
  fill(255);
  text(nfs(int(sensorIntReading), 3) +" cm", 20, 20);

  //do something with the data
  state=int(constrain(map(sensorIntReading, 2, 100, 1, 4), 1, 4));
  text("state: "+ state, 100, 20);




  switch(state) {
  case 1:
    col=color(255, 0, 0, 200);
    channel = 0;
    pitch = 64;
    velocity = 127;
    break;
  case 2:
    col=color(0, 255, 0, 200);
    channel = 0;
    pitch = 62;
    velocity = 127;
    break;
  case 3:
    col=color(0, 0, 255, 200);
    channel = 0;
    pitch = 72;
    velocity = 127;
    break;
  case 4:
    col=color(255, 200, 0, 200);
    channel = 0;
    pitch = 60;
    velocity = 127;
    break;
  }



//send MIDI information OUT. 
  myBus.sendNoteOn(channel, pitch, velocity); // Send a Midi noteOn
  delay(200);
  myBus.sendNoteOff(channel, pitch, velocity); // Send a Midi nodeOff

  fill(col);
  rect(0, 50, width, height);
}

void delay(int time) {
  int current = millis();
  while (millis () < current+time) Thread.yield();
}

//read sensor and do smoothing
void getSensorInput() {
  if (myPort.available () > 0) {
    val = myPort.readStringUntil(lf);
    if (val != null) { //if my input is not emptry
      String s = trim(val); // your data!
      if (lastSensorString.equals(s) == false) { // if your data isn't the same it is your new data!
        lastSensorString = s; // update and remember this reading
        int newSensorIntReading = int(s); // convert it to integer(whole number) to be useful
        if (newSensorIntReading != -1) { // Helps avoid random false positive input
          sensorIntReading = newSensorIntReading;
        }
      }
    }
  }
}
