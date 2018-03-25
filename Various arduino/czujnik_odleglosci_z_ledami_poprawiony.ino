#define trigPin 12
#define echoPin 11

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  for (int i=3; i<=8; i++) {
  pinMode(i, OUTPUT);
  }
}

void loop() {
  int stan;
  stan = przelicz();
  switch (stan) {
    case 1:
      zapalWybraneDiody(1,1,1,1,1,1);
      break;
    case 2:
      zapalWybraneDiody(1,1,1,1,1,0);
      break;
    case 3:
      zapalWybraneDiody(1,1,1,1,0,0);
      break;
    case 4:
      zapalWybraneDiody(1,1,1,0,0,0);
      break;
    case 5:
      zapalWybraneDiody(1,1,0,0,0,0);
      break;
    case 6:
      zapalWybraneDiody(1,0,0,0,0,0);
      break;
    default:
      zapalWybraneDiody(0,0,0,0,0,0);
  }
  
  delay(10);
}

int zmierzOdleglosc() {
  long czas, dystans;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  czas = pulseIn(echoPin, HIGH);
  dystans = czas/58;  
  
  return dystans;
}

int przelicz() {
  int takBlisko;
  if (zmierzOdleglosc()<=50) {
  takBlisko = map (zmierzOdleglosc(), 0, 45, 1, 6);
  } else {
  takBlisko=0;
  }
  return takBlisko;
}

void zapalWybraneDiody(byte a, byte b, byte c, byte d, byte e, byte f) {
digitalWrite(3, a); 
digitalWrite(4, b); 
digitalWrite(5, c);
digitalWrite(6, d);
digitalWrite(7, e); 
digitalWrite(8, f);
}
