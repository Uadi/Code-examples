#define trigPin 12
#define echoPin 11

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  sprawdzaj();
  Serial.println(zmierzOdleglosc());
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

void sprawdzaj(){
  int jakDaleko = zmierzOdleglosc();  
  if (jakDaleko > 50) 
  {
    digitalWrite(3, LOW);
  } 
  else 
    {
      if ((jakDaleko <= 50) && (jakDaleko > 40)) 
      {
        pikaj(500);  
      }
      else 
        {
          if ((jakDaleko <= 40) && (jakDaleko > 25)) 
          {
            pikaj(250);  
          }
          else 
          {
            if ((jakDaleko <= 25) && (jakDaleko > 10))
            {
              pikaj(5);
            }
            else
             {
               digitalWrite(3, HIGH);
             }
          }
        }
    }
}

void pikaj(int czas) {
  delay(czas);
  digitalWrite(3, HIGH);
  delay(75); 
  digitalWrite(3, LOW);
}
