int wypelnienie = 0;
int zmiana = 5;
int i = 0;
boolean rosnie = true;

void setup() {
  pinMode(3, OUTPUT); // konfiguracja pinu jako wyjscie
}

void loop() {
  while (rosnie == true) {
  analogWrite(3, wypelnienie);  //generowanie sygnalu o danym wypelnieniu
  wypelnienie += zmiana;
  delay(10);
    if (wypelnienie == 255) {
    analogWrite(3, wypelnienie);
    rosnie = false;
    delay(100);
    }
  }
  
  while (rosnie == false) {
  analogWrite(3, wypelnienie);  //generowanie sygnalu o danym wypelnieniu
  wypelnienie -= zmiana;
  delay(15);
    if (wypelnienie == 0) {
    analogWrite(3, wypelnienie);
    rosnie = true;
    delay(100);
    }
  }

}
