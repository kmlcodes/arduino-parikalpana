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

//IR sensor library
#include <Adafruit_MLX90614.h>

//I2C library
#include <Wire.h>

//LCD library
#include <LiquidCrystal.h>

//----------------------------------------

//----------define constants---------------
#define MIN_DISTANCE 1     //minimum distance from person (in cm)
#define MAX_DISTANCE 15    //maximum distance from person (in cm)
#define THRESHOLD_TEMP 101 //threshold temperature(in deg F) for warning alert
#define LCD_CONTRAST 80    // LCD constrast value(min-0 max-255)

#define ECHO_PIN 6
#define TRIG_PIN 7
#define BUZZER_PIN 10
#define LCD_V0_PIN 9

//-----------------------------------------

//----------initialize objects-------------

Adafruit_MLX90614 ir_sensor = Adafruit_MLX90614(); // initialize ir sensor object
//-----------------------------------------

/*
  PINS FOR LCD WHERE
  | Vo  =>  D6  |
  | Rs  =>  D12 |
  | E   =>  D11 |
  | D4  =>  D5  |
  | D5  =>  D4  |
  | D6  =>  D3  |
  | D7  =>  D2  |
*/
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//setup
void setup()
{
  //set buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);

  //set ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  //setup ir sensor
  ir_sensor.begin();

  //setup LCD
  lcd.begin(16, 2);

  //set LCD constrast
  analogWrite(LCD_V0_PIN, LCD_CONTRAST);

  //display startup message
  lcd.setCursor(2, 0);
  lcd.print("PARIKALPANA");
  lcd.setCursor(5, 1);
  lcd.print("NEPAL");

  //delay
  delay(2000);
}

//code that run in loop
void loop()
{
  //calculate object distance
  float distance = getDistance();

  //check if object is within range
  if (distance >= MIN_DISTANCE && distance <= MAX_DISTANCE)
  {
    //get calculated object temperature
    float temp = getTemp();

    //clear display
    lcd.clear();

    //display temperature
    lcd.setCursor(0, 0);
    lcd.print("TEMPT ");
    lcd.print(temp);
    lcd.print((char)223);
    lcd.print("F");

    if (temp >= THRESHOLD_TEMP)
    {
      //display warning text
      lcd.setCursor(5, 1);
      lcd.print("HIGH!!");
      warningTone(); //play warning tone
    }
    else
    {
      //display normal text
      lcd.setCursor(5, 1);
      lcd.print("NORMAL");
      normalTone(); //play normal tone
    }
  }
  else
  {
    //clear display
    lcd.clear();

    //display idle text
    lcd.setCursor(2, 0);
    lcd.print("PARIKALPANA");
    lcd.setCursor(5, 1);
    lcd.print("NEPAL");
  }

  //delay before looping
  delay(500);
}

//play normal tone
void normalTone()
{
  for (int i = 0; i <= 1; i++)
  {
    digitalWrite(BUZZER_PIN, HIGH); // Send sound signal...
    delay(600);
    digitalWrite(BUZZER_PIN, LOW); // Stop sound...
    delay(600);
  }
}

//play warning tone
void warningTone()
{
  //play warning tone in a loop
  for (int i = 0; i <= 24; i++)
  {
    digitalWrite(BUZZER_PIN, HIGH); // Send sound signal...
    delay(100);
    digitalWrite(BUZZER_PIN, LOW); // Stop sound...
    delay(100);
  }
}

//get temperature with calculated offset
float getTemp()
{

  //current distance of an object
  float distance = getDistance();

  //temperature of an object
  float temp = ir_sensor.readObjectTempF();

  //ambient temperature
  float ambientTemp = ir_sensor.readAmbientTempF();

  //calculate offset using formula
  float offset = (98.6 - ambientTemp) * (distance / MAX_DISTANCE);


  //add temperature with calculated offset
  return temp + offset;
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
