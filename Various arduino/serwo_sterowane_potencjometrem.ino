#include <Servo.h>  //biblioteka do obslugi serwa
int odczyt;
Servo serwo;

void setup() {
  Serial.begin(9600);
  serwo.attach(3); //serwo na pinie 3
}

void loop() {
  odczyt = analogRead(A5);
  odczyt = map(odczyt, 0, 1023, 0, 180); // przeskaluj z 0-1023 do 0-180
  Serial.println(odczyt);
  serwo.write(odczyt);
  delay(20);
}
