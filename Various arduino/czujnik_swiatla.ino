float napiecie = 0;
int odczyt = 0; //Zmienna do przechowywania odczytu ADC
boolean stan = false;

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT); //Konfiguracja wyjść pod diodę LED
}

void loop() {
  odczyt = analogRead(A5);//Odczytanie wartości z ADC
  napiecie = odczyt * (5.0/1023.0);
  if (odczyt < 150) {
     digitalWrite(7, HIGH);//Włączenie diody
       if (stan == false){
         Serial.println(napiecie);
         stan = true;
       }    
  } else {
     digitalWrite(7, LOW);//Wyłączenie diody     
     stan = false; 
  }
  
  delay(50);
}
