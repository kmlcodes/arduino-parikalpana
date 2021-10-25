#define ECHO_PIN 12
#define TRIG_PIN 11

void setup() {
pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(getDistance());
}

//get distance in centimetres
float getDistance()
{
  digitalWrite(TRIG_PIN, LOW); //clears the trigger pin
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH); //sets the trigger pin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float duration = pulseIn(ECHO_PIN, HIGH); //reads the echo pin, returns the sound wave travel time in microseconds
  return duration * 0.034 / 2;              //calculate and return distance in centimetres
}
