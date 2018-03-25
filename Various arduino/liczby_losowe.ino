void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
}

void loop() {
  Serial.println(random(300)); // "losowa" liczbaod 0-299
  delay(1000);
}
