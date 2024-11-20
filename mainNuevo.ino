#define potenciometro 36 //O A0
#define pin_restaRS 32
#define pin_T1 12
#define pin_T2 14
#define pin_T3 26
#define pin_T4 27
#define pin_T5 25
#define pin_T6 33
#define pin_vIn 13
#define pin_vOut 34
#define pin_i 39
#define pin_iOut 35

int valorPot;
/*
int voltajeIn;
int sumaVINdc;
int sumaVINrms;
float VINdc;
float VINrms;

int voltajeOut;
int sumaVOUTdc;
int sumaVOUTrms;
float VOUTdc;
float VOUTrms;

int corriente;
int sumaIdc;
int sumaIrms;
float Idc;
float Irms;

int suma;
int sumaPeriodos;
*/
int tant = 0;
int dt;

int aux;
volatile int retraso;
volatile int tiempoprueba = 0;

void IRAM_ATTR interrupcion(){ // funcion que se ejecuta con la interrupción
  if((micros() - tiempoprueba > 19900)){
  tiempoprueba = micros();
  
  int tiempoinicio = micros(); //mido en que momento comencé el período
  retraso = 0*valorPot*(3333)/511; // calculo el tiempo que tengo que esperar dependiendo del valor del potenciómetro (3333 microsegundos equivale a pi/3)
  //sumaPeriodos++; //cuento los periodos para promediar mas adelante
  
  while(micros() - tiempoinicio < retraso){ //Espero el tiempo correspondiente al retraso
    // por mientras uso ese tiempo para medir
    //dt = micros() - tant;
    //Serial.println("valor medido: " + analogRead(pin_vIn)*311/511);
    //aux = (analogRead(pin_vIn)*311*dt)/511; // 311 es el valor máximo que puede tomar vIn
    //sumaVINrms += aux*aux;
    /*
    aux = (analogRead(pin_vOut)*311*dt)/511;
    sumaVOUTdc += aux;
    sumaVOUTrms += aux*aux;
    aux = ((analogRead(pin_i))*100*dt)/511;
    sumaIdc += aux;
    sumaIrms += aux*aux;
    */
    //tant = micros();
  }; 
  digitalWrite(pin_T3, LOW);
  digitalWrite(pin_T4, HIGH); //enciendo T4
  
  
  while(micros() - tiempoinicio < 3333 + retraso){ //Espero el tiempo correspondiente a alfa
    // por mientras uso ese tiempo para medir
    //dt = micros() - tant;
    //Serial.println("valor medido: " + analogRead(pin_vIn)*311/511);
    //aux = (analogRead(pin_vIn)*311*dt)/511; // 311 es el valor máximo que puede tomar vIn
    //sumaVINrms += aux*aux;
    /*
    aux = (analogRead(pin_vOut)*311*dt)/511;
    sumaVOUTdc += aux;
    sumaVOUTrms += aux*aux;
    aux = ((analogRead(pin_i))*100*dt)/511;
    sumaIdc += aux;
    sumaIrms += aux*aux;
    */
    //tant = micros();
  };
  digitalWrite(pin_T4, LOW);
  digitalWrite(pin_T2, HIGH); // enciendo T2
  
  
  while(micros() - tiempoinicio < 6666 + retraso){ //Espero el tiempo correspondiente a alfa
    // por mientras uso ese tiempo para medir
    //dt = micros() - tant;
    //Serial.println("valor medido: " + analogRead(pin_vIn)*311/511);
    //aux = (analogRead(pin_vIn)*311*dt)/511; // 311 es el valor máximo que puede tomar vIn
    //sumaVINrms += aux*aux;
    /*
    aux = (analogRead(pin_vOut)*311*dt)/511;
    sumaVOUTdc += aux;
    sumaVOUTrms += aux*aux;
    aux = ((analogRead(pin_i))*100*dt)/511;
    sumaIdc += aux;
    sumaIrms += aux*aux;
    */
    //tant = micros();
  };
  digitalWrite(pin_T2, LOW);
  digitalWrite(pin_T6, HIGH); // enciendo T6
  
  
  while(micros() - tiempoinicio < 9999 + retraso){ //Espero el tiempo correspondiente a alfa
    // por mientras uso ese tiempo para medir
    //dt = micros() - tant;
    //Serial.println("valor medido: " + analogRead(pin_vIn)*311/511);
    //aux = (analogRead(pin_vIn)*311*dt)/511; // 311 es el valor máximo que puede tomar vIn
    //sumaVINrms += aux*aux;
    /*
    aux = (analogRead(pin_vOut)*311*dt)/511;
    sumaVOUTdc += aux;
    sumaVOUTrms += aux*aux;
    aux = ((analogRead(pin_i))*100*dt)/511;
    sumaIdc += aux;
    sumaIrms += aux*aux;
    */
    //tant = micros();
  };
  digitalWrite(pin_T6, LOW);
  digitalWrite(pin_T1, HIGH); // enciendo T4
  
  
  while(micros() - tiempoinicio < 13332 + retraso){ //Espero el tiempo correspondiente a alfa
    // por mientras uso ese tiempo para medir
    //dt = micros() - tant;
    //Serial.println("valor medido: " + analogRead(pin_vIn)*311/511);
    //aux = (analogRead(pin_vIn)*311*dt)/511; // 311 es el valor máximo que puede tomar vIn
    //sumaVINrms += aux*aux;
    /*
    aux = (analogRead(pin_vOut)*311*dt)/511;
    sumaVOUTdc += aux;
    sumaVOUTrms += aux*aux;
    aux = ((analogRead(pin_i))*100*dt)/511;
    sumaIdc += aux;
    sumaIrms += aux*aux;
    */
    tant = micros();
  };
  digitalWrite(pin_T1, LOW);
  digitalWrite(pin_T5, HIGH); // enciendo T4
  
  //if(sumaPeriodos > 250){
    //VOUTdc = sumaVOUTdc/5;// el 5 sale de 250 períodos * 20 milisegundos c/u = 5 segundos
    //Idc = sumaIdc/5;

    //VINrms = 2*sumaVINrms/5000;
    //VOUTrms = sumaVOUTrms/5;
    //Irms = sumaIrms/5;

    //Serial.println(VOUTrms);
    //Serial.println(VINrms);
    //Serial.println(Irms);
/*
    sumaVOUTdc = 0;
    sumaIdc = 0;
    sumaVINrms = 0;
    sumaVOUTrms = 0;
    sumaIrms = 0;
    sumaPeriodos = 0;
    */
  //}
  
  while(micros() - tiempoinicio < 16665 + retraso){ //Espero el tiempo correspondiente a alfa
     // por mientras uso ese tiempo para medir
    //dt = micros() - tant;
    //Serial.println("valor medido: " + analogRead(pin_vIn)*311/511);
    //aux = (analogRead(pin_vIn)*311*dt)/511; // 311 es el valor máximo que puede tomar vIn
    //sumaVINrms += aux*aux;
    /*
    aux = (analogRead(pin_vOut)*311*dt)/511;
    sumaVOUTdc += aux;
    sumaVOUTrms += aux*aux;
    aux = ((analogRead(pin_i))*100*dt)/511;
    sumaIdc += aux;
    sumaIrms += aux*aux;
    */
    //tant = micros();
  };
  digitalWrite(pin_T5, LOW);
  digitalWrite(pin_T3, HIGH); // enciendo T4
  
  };
}


void setup() {
  // falta definir pines como entrada
  analogReadResolution(9);
  attachInterrupt(digitalPinToInterrupt(pin_restaRS), interrupcion, FALLING);
  pinMode(pin_T1, OUTPUT);
  pinMode(pin_T2, OUTPUT);
  pinMode(pin_T3, OUTPUT);
  pinMode(pin_T4, OUTPUT);
  pinMode(pin_T5, OUTPUT);
  pinMode(pin_T6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  valorPot = analogRead(potenciometro);
  Serial.println("valor medido: " + analogRead(pin_vIn));
  delay(10);
}
