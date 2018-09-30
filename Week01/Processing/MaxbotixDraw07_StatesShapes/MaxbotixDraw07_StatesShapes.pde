/*
This example shows how to trigger graphic animations with switch case statements
Code provided by Jen Sykes
getSensorInput() function referenced from Paul Maguire's data filtering structure
*/
import processing.serial.*;


Serial myPort;  // Create object from Serial class
String val = null; // Data received from the serial port
int lf = 10;    // Linefeed in ASCII
String lastSensorString = "";
int sensorIntReading = 0;
float newDistance, newColour;
int state, lastState;
color col;
boolean triggered =false;

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

      break;
    case 2:
      col=color(0, 255, 0, 200);

      break;
    case 3:
      col=color(0, 0, 255, 200);

      break;
    case 4:
      col=color(255, 200, 0, 200);

      break;
    }
 



  fill(col);
  rect(0, 50, width, height);
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
