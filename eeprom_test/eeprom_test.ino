#define SLOPE 12.55
#define CONSTANT 11.55


// EEPROM library
#include <EEPROM.h>

void setup() {
  Serial.begin(9600);
  float slope = SLOPE;
  float constant = CONSTANT;

  //    EEPROM.update(0, slope);
  //    EEPROM.update(1, slope * 100 - int(slope) * 100);
  //    EEPROM.update(2, constant);
  //    EEPROM.update(3, constant * 100 - int(constant) * 100);
  //
}

void loop() {
  int val1 = EEPROM.read(0);
  float val2 = EEPROM.read(1);
  int val3 = EEPROM.read(2);
  float val4 = EEPROM.read(3);
  
  float m=val1+val2/100;
  float c=val3+val4/100;
  
  Serial.print("Slope: ");
  Serial.println(m);
  Serial.print("Constant: ");
  Serial.println(c);
  Serial.println("---------------------------------------------------");
  delay(1000);
}
