#define pin_alfa 5 //D1
#define potenciometro A0 //A0
#define restaRS 0
#define pin_T1 6
#define pin_T2 7
#define pin_T3 8
#define pin_T4 9
#define pin_T5 10
#define pin_T6 11


void setup() {

  // falta definir pines como entrada
  
  pinMode(pin_T1, OUTPUT);
  pinMode(pin_T2, OUTPUT);
  pinMode(pin_T3, OUTPUT);
  pinMode(pin_T4, OUTPUT);
  pinMode(pin_T5, OUTPUT);
  pinMode(pin_T6, OUTPUT);

}

void loop() {
  int valorPot = analogRead(potenciometro);
  int valorRestaRS = analogRead(restaRS);
  tiristores();
}

void tiristores(){ // funcion que se ejecuta con la interrupción
  unsigned long currentMicros = micros();
  int retraso = valorPot*(2500)/1023; // calculo el tiempo que tengo que esperar dependiendo del valor del potenciómetro
  while(currentMillis < retraso); //Espero el tiempo correspondiente a alfa
  digitalWrite(pin_T2, HIGH);
  digitalWrite(pin_T6, HIGH); // T2 y T6
  while(currentMillis < 2500);
  while(currentMillis < retraso); //Espero el tiempo correspondiente a alfa
  digitalWrite(pin_T6, LOW);
  digitalWrite(pin_T4, HIGH); // T2 y T4
  while(currentMillis < 5000);
  while(currentMillis < retraso); //Espero el tiempo correspondiente a alfa
  digitalWrite(pin_T6, LOW);
  digitalWrite(pin_T3, HIGH); // T3 y T4
  while(currentMillis < 7500);
  while(currentMillis < retraso); //Espero el tiempo correspondiente a alfa
  digitalWrite(pin_T4, LOW);
  digitalWrite(pin_T5, HIGH); // T3 y T5
  while(currentMillis < 10000);
  while(currentMillis < retraso); //Espero el tiempo correspondiente a alfa
  digitalWrite(pin_T3, LOW);
  digitalWrite(pin_T1, HIGH); // T1 y T5
  while(currentMillis < 12500);
  while(currentMillis < retraso); //Espero el tiempo correspondiente a alfa
  digitalWrite(pin_T5, LOW);
  digitalWrite(pin_T6, HIGH); // T1 y T6

}
