void setup() {
  Serial.begin(9600);
}

void loop() {
  float temp = float(random(96,100)) + float(random(0,100))/100;
  Serial.println(temp);
  delay(1000);
}
