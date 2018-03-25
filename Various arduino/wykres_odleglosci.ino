#define trigPin 12
#define echoPin 11

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); //pin podlaczony do trig jako wyjscie
  pinMode(echoPin, INPUT); //echo jako wejscie
}

void loop() {
  long czas, dystans;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  czas = pulseIn(echoPin, HIGH);  //pomiar czasu trwania impulsu
  dystans = czas/58;

  if (dystans > 400) {
    dystans = 400;
  }
  
  Serial.print(dystans);
  Serial.print("\t");
  Serial.print(dystans+40);
  Serial.print("\t");
  Serial.println(dystans+20);
  delay(25);

}
