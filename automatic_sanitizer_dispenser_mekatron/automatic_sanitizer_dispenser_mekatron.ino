#define THRESHOLD_DISTANCE 20            //Distance in centimetres
#define AUTOCUT_TIME 2                   //Autocut time in seconds
#define RELAY_NO_PIN 2                   //control pin in relay module
#define TRIG_PIN 10                       //Trigger pin in ultrasonic sensor
#define ECHO_PIN 11                       //Echo pin in ultrasonic sensor

boolean wasInRangePrevious = false;           // flag to check if object was  in range previously
void setup() {
  Serial.begin(9600);
  pinMode(RELAY_NO_PIN, OUTPUT);
  digitalWrite(RELAY_NO_PIN, LOW);          //initially turn relay off
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  float dis = getDistance();
  Serial.println("Distance: " + String(dis));
  if ( dis <= THRESHOLD_DISTANCE) //if object is currently in range
  {
    Serial.println("Object in range");
    if (!wasInRangePrevious)                //object was not in range previously
    {
      Serial.println("Object was not in range in previously reading");
      Serial.println("Relay triggered!");
      digitalWrite(RELAY_NO_PIN, HIGH);      //turn on relay switch on
      delay(AUTOCUT_TIME * 1000);            // delay as per autocut time
      digitalWrite(RELAY_NO_PIN, LOW);       //turn  relay switch off

      if (getDistance() <= THRESHOLD_DISTANCE) //object is still in range
      {
        wasInRangePrevious = true;
      }
      else {
        wasInRangePrevious = false;
      }

    }
    else {
      Serial.println("Object was in range in previously reading");
      Serial.println("Relay not triggered!");
    }
  }
  else {
    Serial.println("No object in range");
    wasInRangePrevious = false;
  }
  Serial.println("____________________");
  delay(500);
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
