#include <LiquidCrystal.h>  //bilbioteka wyswietlacza
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // informacja o podlaczeniu wyswietlacza
double odczyt;

void setup() {
  lcd.begin(16, 2); // deklaracja typu wyswietlacza (2 linie po 16 znakow)
  lcd.clear();  //wyczyszczenie wyswietlacza
  lcd.setCursor(0, 0); //ustaw kursor 1 linia
  lcd.print("Odczyt:");
  lcd.setCursor(0, 1); //ustaw kursor 2 linia
  lcd.print("0.00V");
}

void loop() {
  odczyt = analogRead(A5)*5.0/1023.0; //wartosc odczytanego napiecia
  lcd.setCursor(0,1); //ustawienie kursora 2 linia
  lcd.print(odczyt); //wyswietlanie tekstu
  delay(250);
 
}
