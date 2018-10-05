/*

  Code adapted from Maxbotix
  Written by Tom Bonar for testing

  Code adapted by Jen Sykes
  to read one sensor and control switch case statements
  sending MIDI data

  This requires a device that can send MIDI(eg:Teensy) values or a MIDI out socket wired into the circuit
** if you want to emulate MIDI notes on your laptop use Processing as a middle tool.
*/

long pulse1, sensor1;
const int pwPin1 = 1; //the pin the distance sensor is routed to.
int state;
int inByte;

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
  //do something with the data
  //map and constrain sensor data to 4 states.
  state = constrain(map(sensor1, 2, 100, 1, 4), 1, 4);

  switch (state) {
    case 1:
      //put DMX controls in here.
      //They may vary in channel and value number depedning on typoe of light.
      usbMIDI.sendNoteOn(60, 127, 1); //(Note, velocity, channel)
      delay(100);
      usbMIDI.sendNoteOff(60, 127, 1); //(Note, velocity, channel)
      break;
    case 2:
      usbMIDI.sendNoteOn(61, 127, 1); //(Note, velocity, channel)
      delay(100);
      usbMIDI.sendNoteOff(61, 127, 1); //(Note, velocity, channel)
      break;
    case 3:
      usbMIDI.sendNoteOn(62, 127, 1); //(Note, velocity, channel)
      delay(100);
      usbMIDI.sendNoteOff(62, 127, 1); //(Note, velocity, channel)
      break;
    case 4:
      usbMIDI.sendNoteOn(63, 127, 1); //(Note, velocity, channel)
      delay(100);
      usbMIDI.sendNoteOff(63, 127, 1); //(Note, velocity, channel)
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

  Serial.print("S1");
  Serial.print(" ");
  Serial.print(sensor1);
  Serial.println(" ");

}
