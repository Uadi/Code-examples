#include <Servo.h> //Biblioteka odpowiedzialna za serwa
 
Servo serwomechanizm;  //Tworzymy obiekt, dzięki któremu możemy odwołać się do serwa 
byte pozycja = 0; //Aktualna pozycja serwa 0-180
int pozycjaPoprzednia = 0;

void setup() { 
  serwomechanizm.attach(9);  //Serwomechanizm podłączony do pinu 11
  Serial.begin(9600);
} 
 
void loop() 
{ 
  int odczytCzujnika = analogRead(A5); //Odczytujemy wartość z czujnika
  pozycja = map(odczytCzujnika, 200, 1000, 0, 180); //Zamieniamy ją na pozycję serwa
  
  if (abs(pozycja-pozycjaPoprzednia) > 3) { //Sprawdzamy czy pozycje różnią się o ponad 5 stopni
    serwomechanizm.write(pozycja); //Wykonajujemy ruch
    pozycjaPoprzednia = pozycja; //Zapamiętujemy aktualną pozycję jako poprzednią
  }
  
  Serial.println(odczytCzujnika); //Wysyłamy wartość do terminala
  delay(100); //Opóźnienie dla lepszego efektu
}
