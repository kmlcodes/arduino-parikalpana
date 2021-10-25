

/************************
  Infrared Thermometer
 ************************
  Developed by:
  PARIKALPANA NEPAL
  Damak, Nepal
  (c)2020
 ************************
*/

//----include necessary libraries--------

//I2C library
#include <Wire.h>

//LCD I2C module library
#include <LiquidCrystal_I2C.h>

//----------------------------------------

//----------define constants---------------
#define MIN_RANDOM 97      //minimum random value
#define MAX_RANDOM 99      //maximum random value
#define MIN_DISTANCE 1     //minimum distance from person (in cm)
#define MAX_DISTANCE 10    //maximum distance from person (in cm)
#define THRESHOLD_TEMP 101 //threshold temperature(in deg F) for warning alert
#define ECHO_PIN 8
#define TRIG_PIN 7
#define BUZZER_PIN 9
//-----------------------------------------

//----------initialize objects-------------

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2); // LCD connected on I2C

//-----------------------------------------
boolean wasInRangePrevious = false;           //flag to check if object was  in range previously
float prevTemp = 0;                           //store previous temperature

//setup
void setup()
{
  //set buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);

  //set ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initiate the LCD
  lcd.init();
  lcd.backlight();

  //display startup message
  lcd.setCursor(2, 0);
  lcd.print("PARIKALPANA");
  lcd.setCursor(5, 1);
  lcd.print("NEPAL");

  delay(2000);                                                                   //pause screen to show startup message
}

//run in loop
void loop() {
  float distance = getDistance();
  if ( distance >= MIN_DISTANCE && distance <= MAX_DISTANCE)                      //if object is currently in range
  {
    if (!wasInRangePrevious)                                                      //object was not in range previously
    {
      float temp = float(random(96, 100)) + float(random(0, 100)) / 100;          //generate a new random floating point number
      float prevTemp = temp;                                                      //set current temperature as new temperature
      
      int currentDistance = getDistance();
      if (currentDistance >= MIN_DISTANCE && currentDistance <= MAX_DISTANCE)     //object is still in range
      {
        wasInRangePrevious = true;
      }
      else {
        wasInRangePrevious = false;
      }

    }
    else {
        float temp = prevTemp();                                                  //take previous temperature if object was in range previously
    }

    lcd.backlight();                                                              //turn on lcd backlight
    lcd.clear();                                                                  //clear display

    //display temperature
    lcd.setCursor(0, 0);
    lcd.print("TEMPT ");
    lcd.print(temp);
    lcd.print((char)223);
    lcd.print("F");

    //display normal text
    lcd.setCursor(5, 1);
    lcd.print("NORMAL");
    normalTone();                                                       //play normal tone
  }
  else {
    if(wasInRangePrevious){                                             //object is currently not in range but was in previous reading
      wasInRangePrevious = false;                                       
      delay(5000);                                                      //pause to display temperature
    }
    
    lcd.noBacklight();                                                  //turn off lcd backlight
    lcd.clear();                                                        //clear display

    //display idle text
    lcd.setCursor(2, 0);
    lcd.print("PARIKALPANA");
    lcd.setCursor(5, 1);
    lcd.print("NEPAL");
  }
  delay(500);
}

///play normal tone
void normalTone()
{
  tone(BUZZER_PIN, 250);                                          // Send sound signal...
  delay(200);
  noTone(BUZZER_PIN);                                           // Stop sound...
  delay(200);
}


//get distance in centimetres
float getDistance()
{
  digitalWrite(TRIG_PIN, LOW);                                 //clears the trigger pin
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);                               //sets the trigger pin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float duration = pulseIn(ECHO_PIN, HIGH);                   //reads the echo pin, returns the sound wave travel time in microseconds
  return duration * 0.034 / 2;                                //calculate and return distance in centimetres
}
