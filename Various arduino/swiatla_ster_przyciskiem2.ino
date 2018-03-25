void setup() {
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, INPUT_PULLUP);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(9, HIGH);  // cz
  delay(500); //opoznienia zeby przycisk nie szalal i nie przelaczal kilka sekwnecji podczas wcisniecia
  
  while (digitalRead(6) == HIGH) {}
  delay(1000);
  digitalWrite(8, HIGH);  // cz, zol
  delay(2000);
  
  //while (digitalRead(6) == HIGH) {}
  digitalWrite(9, LOW);   // ziel
  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  delay(500);
  
  while (digitalRead(6) == HIGH) {}
  delay(1000);
  digitalWrite(8, HIGH); //zol
  digitalWrite(7, LOW);
  delay(2000);
  
  //while (digitalRead(6) == HIGH) {}
  digitalWrite(8, LOW);  //cz
  }

