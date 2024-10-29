void IRAM_ATTR interrupcion(){ // funcion que se ejecuta con la interrupción
  cuenta++;
}

void setup() {
  
  pinMode(pinInt, INPUT_PULLUP); 
  
  attachInterrupt(digitalPinToInterrupt(pinInt), interrupcion, RISING);

}

void loop() {
  // put your main code here, to run repeatedly:

}
