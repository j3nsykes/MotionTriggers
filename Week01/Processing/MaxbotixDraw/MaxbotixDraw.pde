/*
Bare bones structure to get sensor data from Arduino into Processing
Constructed from the Serial Library example SimpleRead
Code provided by Jen Sykes
*/


import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port

void setup() 
{
  size(200, 200);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  printArray(Serial.list()); //print all dveices
  String portName = Serial.list()[3];

  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  background(0);
  if ( myPort.available() > 0) {  // If data is available,
    val = myPort.read();         // read it and store it in val
  }
   println("val: ", val);
   
   //do something with the data
   fill(255);
   ellipse(width/2,height/2,val,val);
}
