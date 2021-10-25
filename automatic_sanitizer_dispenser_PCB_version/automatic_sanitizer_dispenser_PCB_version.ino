#define THRESHOLD_DISTANCE 10             //Distance in centimetres
#define AUTOCUT_TIME 2                    //Autocut time in seconds
#define LED_PIN 13                        //LED pin
#define SSR_PIN 2                         //Solid State Relay(SSR) control pin
#define TRIG_PIN 11                        //Trigger pin in ultrasonic sensor
#define ECHO_PIN 12                       //Echo pin in ultrasonic sensor

boolean wasInRangePrevious = false;       // flag to check if object was  in range previously
void setup() {
  Serial.begin(9600);
  pinMode(SSR_PIN, OUTPUT);
  digitalWrite(SSR_PIN, LOW);          //initially turn relay off
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  float distance = getDistance();
  Serial.println("Distance: " + String(distance));
  if ( distance > 0 && distance <= THRESHOLD_DISTANCE)         //if object is currently in range
  {
    Serial.println("Object in range");
    if (!wasInRangePrevious)                //if object was not in range previously
    {
      Serial.println("Object was not in range in previously reading");
      Serial.println("Relay triggered!");
      digitalWrite(SSR_PIN, HIGH);           //turn on relay switch on
      digitalWrite(LED_PIN, HIGH);           //turn led on
      delay(AUTOCUT_TIME * 1000);            //delay as per autocut time
      digitalWrite(SSR_PIN, LOW);            //turn  relay switch off
      digitalWrite(LED_PIN, LOW);            //turn led off

      float checked_distance = getDistance();

      if (checked_distance > 0 && checked_distance <= THRESHOLD_DISTANCE) //check if object is still in range
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
