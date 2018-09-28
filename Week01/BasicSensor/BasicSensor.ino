long pulse1;
const int pwPin1 = 1; //the pin the distance sensor is routed to.

void setup() {
  // put your setup code here, to run once:
  //initialise the inputs and outputs.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pwPin1, INPUT);

  Serial.begin(9600); //open the serial port
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second


  //check if the sensor is working
  pulse1 = pulseIn(pwPin1, HIGH); //get input from the sensor. 
  Serial.print("sensor :");
  Serial.println(pulse1);

  delay(50); //arbitary delay to control influx of data
}
