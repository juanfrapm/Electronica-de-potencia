//const int pinInt = 0;
const int prueba = 4;

//void IRAM_ATTR interrupcion(){ // funcion que se ejecuta con la interrupción

//}

void setup() {
  
  //pinMode(pinInt, INPUT_PULLUP); 
  pinMode(prueba, OUTPUT);
  pinMode(2, OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(pinInt), interrupcion, RISING);

}

void loop() {
  delay(8000);
  digitalWrite(2, HIGH);
  digitalWrite(prueba, HIGH);
  delay(3000);
  digitalWrite(prueba, LOW);
  digitalWrite(2, LOW);
}
