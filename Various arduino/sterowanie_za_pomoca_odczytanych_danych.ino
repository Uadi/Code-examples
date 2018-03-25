#define niebieska 6
#define zolta 7
#define zielona 8
#define czerwona 9
String odebrane_dane = "";
boolean stanziel = false;
boolean stanczer = false;
boolean stanzolt = false;
boolean stannieb = false;

void setup() {
  Serial.begin(9600);
  pinMode(zielona, OUTPUT);
  pinMode(czerwona, OUTPUT);
  pinMode(zolta, OUTPUT);
  pinMode(niebieska, OUTPUT);
  digitalWrite(zielona, LOW);
  digitalWrite(czerwona, LOW);
  digitalWrite(zolta, LOW);
  digitalWrite(niebieska, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    odebrane_dane = Serial.readStringUntil('\n');
     
    if (odebrane_dane == "zielona") {
      if (stanziel == false) {
      digitalWrite(zielona, HIGH);
      stanziel = true;
      }
      else {
      digitalWrite(zielona, LOW);
      stanziel = false;
      }
    }
     
    if (odebrane_dane == "czerwona") {
      if (stanczer == false) {
      digitalWrite(czerwona, HIGH);
      stanczer = true;
      }
      else {
      digitalWrite(czerwona, LOW);
      stanczer = false;
      }
    }
    
    if (odebrane_dane == "zolta") {
      if (stanzolt == false) {
      digitalWrite(zolta, HIGH);
      stanzolt = true;
      }
      else {
      digitalWrite(zolta, LOW);
      stanzolt = false;
      }
    }
    
    if (odebrane_dane == "niebieska") {
      if (stannieb == false) {
      digitalWrite(niebieska, HIGH);
      stannieb = true;
      }
      else {
      digitalWrite(niebieska, LOW);
      stannieb = false;
      }
    }
    
    if (odebrane_dane != "czerwona" && odebrane_dane != "zielona" && odebrane_dane != "niebieska" && odebrane_dane != "zolta") {      //// && - warunek AND
      Serial.println("bledna komenda");
    }
  }  
}

