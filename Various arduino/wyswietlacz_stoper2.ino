#include <LiquidCrystal.h>  //bilbioteka wyswietlacza
#define startuj 11
#define stopuj 12
float sekundy;
int minuty;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 

void setup() {
  analogWrite(10, 255);  // jasnosc wyswietlacza 0-255
  Serial.begin(9600);
  pinMode(startuj, INPUT_PULLUP);
  pinMode(stopuj, INPUT_PULLUP);
  lcd.begin(16, 2); // deklaracja typu wyswietlacza (2 linie po 16 znakow)
}

void loop() {
  sekundy = 0.00;
  minuty = 0;
  lcd.clear();
  lcd.setCursor(0, 0); // ustawienie kursora w pierwszej linii
  lcd.print("Odmierzony czas:"); // ustawienie tekstu
  lcd.setCursor(0, 1); // ustawienie kursora w drugiej linii
  lcd.print("0.00s");
  
  while (digitalRead(startuj)==LOW) {}
  delay(50);
  while (digitalRead(startuj)==HIGH) {} 
  while (digitalRead(stopuj)==HIGH) {
  
  delay(50);
  sekundy+=0.05;
  
  if (sekundy>=59.99) {  //co tu sie odjebalo to ja nawet nie 
  sekundy=0.00;          //nigdy nie byl spelniony warunek
  minuty+=1;             //sekundy == 60.00
  }
  
  Serial.println(minuty);
  Serial.println(sekundy);
 
  
  if (minuty>0) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Odmierzony czas:");
  lcd.setCursor(0, 1);
  lcd.print(minuty);
  lcd.print("m "); 
  lcd.print(sekundy);
  lcd.print("s"); 
  } else {
  lcd.setCursor(0, 1);
  lcd.print(sekundy);
  lcd.print("s");
  }
  
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("KONIEC!");
  if (minuty>0) {
    lcd.setCursor(0, 1);
    lcd.print("Czas: ");
    lcd.print(minuty);
    lcd.print("m "); 
    lcd.print(sekundy);
    lcd.print("s"); 
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Czas: ");
    lcd.print(sekundy);
    lcd.print("s");
  }
  
  delay(100);
  
  while (digitalRead(stopuj)==LOW) {}
  delay(50);
  while (digitalRead(stopuj)==HIGH) {}
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wcisnij start");
  lcd.setCursor(0, 1);
  lcd.print("aby wyzerowac");
  while (digitalRead(startuj)==HIGH) {} 
  
}
