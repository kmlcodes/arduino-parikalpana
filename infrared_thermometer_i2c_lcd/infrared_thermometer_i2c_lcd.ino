

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

//LCD I2C module library
#include <LiquidCrystal_I2C.h>

//----------------------------------------

//----------define constants---------------
#define MIN_DISTANCE 1     //minimum distance from person (in cm)
#define MAX_DISTANCE 10    //maximum distance from person (in cm)
#define THRESHOLD_TEMP 101 //threshold temperature(in deg F) for warning alert
#define ECHO_PIN 8
#define TRIG_PIN 7
#define BUZZER_PIN 9
//-----------------------------------------

//----------initialize objects-------------

Adafruit_MLX90614 ir_sensor = Adafruit_MLX90614();      // initialize ir sensor object
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2); // LCD connected on I2C

//-----------------------------------------

int prevDistance = 0; // store previous distance to check if an object is still within range

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

  // Initiate the LCD
  lcd.init();
  lcd.backlight();

  //display startup message
  lcd.setCursor(2, 0);
  lcd.print("PARIKALPANA");
  lcd.setCursor(5, 1);
  lcd.print("NEPAL");

  delay(2000);//hold screen to show startup message for a while
  Serial.begin(9600);
}

//code that run in loop
void loop()
{
  int distance = getDistance();
  if (distance >= MIN_DISTANCE && distance <= MAX_DISTANCE)
  {
    float temp = getTempAtDistance(distance); // get current calculated temperature
    lcd.backlight();                          //turn on lcd backlight
    lcd.clear();                              //clear display
    Serial.print(distance);
    Serial.print(',');
    Serial.println(temp);

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
    prevDistance = distance; //reset previous distance
  }
  else
  {
    if (prevDistance >= MIN_DISTANCE && prevDistance <= MAX_DISTANCE)
    {
      //wait to hold displayed temperature
      delay(5000);
    }
    lcd.noBacklight(); //turn off lcd backlight
    lcd.clear();       //clear display

    //display idle text
    lcd.setCursor(2, 0);
    lcd.print("PARIKALPANA");
    lcd.setCursor(5, 1);
    lcd.print("NEPAL");

    prevDistance = 0;
  }
  //delay before looping
  delay(500);
}

///play normal tone
void normalTone()
{
  tone(BUZZER_PIN, 250); // Send sound signal...
  delay(200);
  noTone(BUZZER_PIN); // Stop sound...
  delay(200);
}

//play warning tone
void warningTone()
{
  //play warning tone in a loop
  for (int i = 0; i <= 9; i++)
  {
    tone(BUZZER_PIN, 1200); // Send sound signal...
    delay(100);
    noTone(BUZZER_PIN); // Stop sound...
    delay(100);
  }
}

//get temperature with calculated offset at given distance
float getTempAtDistance(int distance)
{
  float offset;
  switch (distance)
  {
    case 1:
      offset = 2.5;
      break;
    case 2:
      offset = 2.7;
      break;
    case 3:
      offset = 3.1;
      break;
    case 4:
      offset = 3.3;
      break;
    case 5:
      offset = 4.1;
      break;
    case 6:
      offset = 4.4;
      break;
    case 7:
      offset = 5.0;
      break;
    case 8:
      offset = 5.2;
      break;
    case 9:
      offset = 5.3;
      break;
    case 10:
      offset = 5.5;
      break;
    default:
      offset = 0.0;
  }

  return ir_sensor.readObjectTempF() + offset;
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
