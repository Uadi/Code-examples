#define trigPin 12
#define echoPin 11

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  Serial.print(zmierzOdleglosc());
  Serial.println(" cm");
  delay(500);
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
