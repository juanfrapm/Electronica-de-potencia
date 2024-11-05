#define pin_alfa 5 //D1
#define potenciometro A0 //A0
#define restaRS 0
#define pin_T1 35
#define pin_T2 32
#define pin_T3 33
#define pin_T4 25
#define pin_T5 26
#define pin_T6 27
#define pin_vIn 12
#define pin_vOut 13
#define pin_i 14

int valorPot;
int voltajeIn;
int sumaVIN;
int VINdc;
int VINrms;
int voltajeOut;
int sumaVOUT;
int VOUTdc;
int VOUTrms;
int corriente;


void IRAM_ATTR interrupcion(){ // funcion que se ejecuta con la interrupción
  unsigned long currentMicros = micros();
  int retraso = valorPot*(2500)/1023; // calculo el tiempo que tengo que esperar dependiendo del valor del potenciómetro
  while(currentMicros < retraso); //Espero el tiempo correspondiente a alfa
  digitalWrite(pin_T2, HIGH);
  digitalWrite(pin_T6, HIGH); // T2 y T6
  while(currentMicros < 2500);
  while(currentMicros < retraso); //Espero el tiempo correspondiente a alfa
  digitalWrite(pin_T6, LOW);
  digitalWrite(pin_T4, HIGH); // T2 y T4
  while(currentMicros < 5000);
  while(currentMicros < retraso); //Espero el tiempo correspondiente a alfa
  digitalWrite(pin_T6, LOW);
  digitalWrite(pin_T3, HIGH); // T3 y T4
  while(currentMicros < 7500);
  while(currentMicros < retraso); //Espero el tiempo correspondiente a alfa
  digitalWrite(pin_T4, LOW);
  digitalWrite(pin_T5, HIGH); // T3 y T5
  while(currentMicros < 10000);
  while(currentMicros < retraso); //Espero el tiempo correspondiente a alfa
  digitalWrite(pin_T3, LOW);
  digitalWrite(pin_T1, HIGH); // T1 y T5
  while(currentMicros < 12500);
  while(currentMicros < retraso); //Espero el tiempo correspondiente a alfa
  digitalWrite(pin_T5, LOW);
  digitalWrite(pin_T6, HIGH); // T1 y T6
}


void setup() {
  // falta definir pines como entrada
  attachInterrupt(digitalPinToInterrupt(pin_alfa), interrupcion, RISING);
  pinMode(pin_T1, OUTPUT);
  pinMode(pin_T2, OUTPUT);
  pinMode(pin_T3, OUTPUT);
  pinMode(pin_T4, OUTPUT);
  pinMode(pin_T5, OUTPUT);
  pinMode(pin_T6, OUTPUT);
  pinMode(voltajeIn, INPUT);
  pinMode(voltajeOut, INPUT);
  pinMode(corriente, INPUT);
}

void loop() {
  valorPot = analogRead(potenciometro);

  
  voltajeIn = analogRead(pin_vIn);
  
  
  voltajeOut = analogRead(pin_vOut);
  corriente = analogRead(pin_i);
}

