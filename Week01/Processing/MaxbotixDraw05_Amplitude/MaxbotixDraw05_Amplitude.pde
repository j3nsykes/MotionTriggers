
import processing.serial.*;
import processing.sound.*;

SoundFile soundfile;

Serial myPort;  // Create object from Serial class
String val = null; // Data received from the serial port
int lf = 10;    // Linefeed in ASCII
String lastSensorString = "";
int sensorIntReading = 0;
float newDistance, newColour;

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

  // Load a soundfile
  soundfile = new SoundFile(this, "vibraphon.aiff");

  // Play the file in a loop
  soundfile.loop();
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

  float distance =map(sensorIntReading, 2, 100, 0, width);
  newDistance=lerp(newDistance, distance, 0.05);

  float colour= map(sensorIntReading, 5, 100, 0, 255);
  newColour=lerp(newColour, colour, 0.05);
  noStroke();
  color col=color(newColour, 100, 20, newColour);
  fill(col);
  rect(0, 50, width, height); //draw a growing bar

  //start to change sound amplitude
  float amplitude = map(sensorIntReading, 2, 100, 0.2, 1.0);
  soundfile.amp(amplitude);

  //change the rate of a sound
  //float playbackSpeed = map(sensorIntReading, 2, 100, 0.25, 4.0);
  //soundfile.rate(playbackSpeed);
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
