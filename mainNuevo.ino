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

int voltajeIn;
int sumaVINdc;
int sumaVINrms;
int VINdc;
int VINrms;

int voltajeOut;
int sumaVOUTdc;
int sumaVOUTrms;
int VOUTdc;
int VOUTrms;

int corriente;
int sumaIdc;
int sumaIrms;
int Idc;
int Irms;

int suma;
int sumaPeriodos;

int tant = 0;
int dt;

int aux;


void IRAM_ATTR interrupcion(){ // funcion que se ejecuta con la interrupción
  int tiempoinicio = micros(); //mido en que momento comencé el período
  int retraso = valorPot*(3333)/511; // calculo el tiempo que tengo que esperar dependiendo del valor del potenciómetro (3333 microsegundos equivale a pi/3)
  sumaPeriodos++; //cuento los periodos para promediar mas adelante
  while(micros() - tiempoinicio < retraso){ //Espero el tiempo correspondiente al retraso
    // por mientras uso ese tiempo para medir
    dt = micros() - tant;
    aux = analogRead(pin_vIn)*dt;
    sumaVINdc += aux;
    sumaVINrms += aux*aux;
    aux = analogRead(pin_vOut)*dt;
    sumaVOUTdc += aux;
    sumaVOUTrms += aux*aux;
    aux = analogRead(pin_i)*dt;
    sumaIdc += aux;
    sumaIrms += aux*aux;
    tant = micros();
    suma++;
  }; 
  
  digitalWrite(pin_T2, HIGH); //enciendo T2
  digitalWrite(pin_T6, HIGH); //enciendo T6
  
  while(micros() - tiempoinicio < 3333 + retraso){ //Espero el tiempo correspondiente a alfa
    // por mientras uso ese tiempo para medir
    dt = micros() - tant;
    aux = analogRead(pin_vIn)*dt;
    sumaVINdc += aux;
    sumaVINrms += aux*aux;
    aux = analogRead(pin_vOut)*dt;
    sumaVOUTdc += aux;
    sumaVOUTrms += aux*aux;
    aux = analogRead(pin_i)*dt;
    sumaIdc += aux;
    sumaIrms += aux*aux;
    tant = micros();
    suma++;
  };
  digitalWrite(pin_T4, HIGH); // enciendo T4
  digitalWrite(pin_T6, LOW); // apago T6 y T2
  digitalWrite(pin_T2, LOW);
  while(micros() - tiempoinicio < 6666 + retraso){ //Espero el tiempo correspondiente a alfa
    // por mientras uso ese tiempo para medir
    dt = micros() - tant;
    aux = analogRead(pin_vIn)*dt;
    sumaVINdc += aux;
    sumaVINrms += aux*aux;
    aux = analogRead(pin_vOut)*dt;
    sumaVOUTdc += aux;
    sumaVOUTrms += aux*aux;
    aux = analogRead(pin_i)*dt;
    sumaIdc += aux;
    sumaIrms += aux*aux;
    tant = micros();
    suma++;
  };
  digitalWrite(pin_T3, HIGH); // T3 y T4
  digitalWrite(pin_T4, LOW);
  while(micros() - tiempoinicio < 9999 + retraso){ //Espero el tiempo correspondiente a alfa
    // por mientras uso ese tiempo para medir
    dt = micros() - tant;
    aux = analogRead(pin_vIn)*dt;
    sumaVINdc += aux;
    sumaVINrms += aux*aux;
    aux = analogRead(pin_vOut)*dt;
    sumaVOUTdc += aux;
    sumaVOUTrms += aux*aux;
    aux = analogRead(pin_i)*dt;
    sumaIdc += aux;
    sumaIrms += aux*aux;
    tant = micros();
    suma++;
  };
  digitalWrite(pin_T5, HIGH); // T3 y T5
  digitalWrite(pin_T3, LOW);
  while(micros() - tiempoinicio < 13332 + retraso){ //Espero el tiempo correspondiente a alfa
    // por mientras uso ese tiempo para medir
    dt = micros() - tant;
    aux = analogRead(pin_vIn)*dt;
    sumaVINdc += aux;
    sumaVINrms += aux*aux;
    aux = analogRead(pin_vOut)*dt;
    sumaVOUTdc += aux;
    sumaVOUTrms += aux*aux;
    aux = analogRead(pin_i)*dt;
    sumaIdc += aux;
    sumaIrms += aux*aux;
    tant = micros();
    suma++;
  };
  digitalWrite(pin_T1, HIGH); // T1 y T5
  digitalWrite(pin_T5, LOW);
  if(sumaPeriodos > 25){
    VINdc = sumaVINdc/500; // el 500 sale de 25 períodos * 20 microsegundos c/u (hay que ajustar unidades)
    VOUTdc = sumaVOUTdc/500;
    Idc = sumaIdc/500;

    VINrms = sumaVINrms/500;
    VOUTrms = sumaVOUTrms/500;
    Irms = sumaIrms/500;

    sumaVIN = 0;
    sumaVOUT = 0;
    sumaI = 0;
    suma = 0;
    
  }
  while(micros() - tiempoinicio < 16665 + retraso){ //Espero el tiempo correspondiente a alfa
    // por mientras uso ese tiempo para medir
    dt = micros() - tant;
    aux = analogRead(pin_vIn)*dt;
    sumaVINdc += aux;
    sumaVINrms += aux*aux;
    aux = analogRead(pin_vOut)*dt;
    sumaVOUTdc += aux;
    sumaVOUTrms += aux*aux;
    aux = analogRead(pin_i)*dt;
    sumaIdc += aux;
    sumaIrms += aux*aux;
    tant = micros();
    suma++;
  };
  digitalWrite(pin_T6, HIGH); // T1 y T6
  digitalWrite(pin_T1, LOW);
}


void setup() {
  // falta definir pines como entrada
  attachInterrupt(digitalPinToInterrupt(pin_restaRS), interrupcion, RISING);
  pinMode(pin_T1, OUTPUT);
  pinMode(pin_T2, OUTPUT);
  pinMode(pin_T3, OUTPUT);
  pinMode(pin_T4, OUTPUT);
  pinMode(pin_T5, OUTPUT);
  pinMode(pin_T6, OUTPUT);
  pinMode(voltajeIn, INPUT);
  pinMode(voltajeOut, INPUT);
  pinMode(corriente, INPUT);
  Serial.begin(9600);
  analogReadResolution(9);
}

void loop() {
  valorPot = analogRead(potenciometro);

  
  voltajeIn = analogRead(pin_vIn);
  
  
  voltajeOut = analogRead(pin_vOut);
  corriente = analogRead(pin_i);
}
