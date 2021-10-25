
#define RELAY_NO_PIN 3                   //control pin in relay module
void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY_NO_PIN, OUTPUT);

}

void loop() {
  digitalWrite(RELAY_NO_PIN, LOW);      //turn on relay switch on
  delay(1000);            
  digitalWrite(RELAY_NO_PIN, HIGH);       //turn  relay switch off
  delay(1000); 
}
