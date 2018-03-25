void setup() {
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH); // ustawiamy na stale stan wysoki na pin 6
  pinMode(7, OUTPUT);  // sygnaly sterujace kierunkiem obrotow silnika
  pinMode(8, OUTPUT);
  
}

void loop() {
  digitalWrite(7, LOW); //silnik nr 1 obroty w lewo
  digitalWrite(8, HIGH);
  delay(3000);
  digitalWrite(7, HIGH); //silnik nr 1 obroty w prawo
  digitalWrite(8, LOW);
  delay(3000);
}
