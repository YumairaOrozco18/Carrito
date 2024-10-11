const int motores[4] = {12, 13, 14, 27};  // Pines de los motores
const int ENA = 32;  
const int ENB = 33; 
const int EchoPin = 18;
const int TriggerPin = 5; 

// Matriz de movimientos: cada fila representa un movimiento específico (Adelante, Detener, Reversa, Giro Izq, Giro Der)
const int movimientos[5][4] = {
  {HIGH, LOW, HIGH, LOW},  // Adelante
  {LOW, LOW, LOW, LOW},    // Detenerse
  {LOW, HIGH, LOW, HIGH},  // Reversa
  {LOW, LOW, HIGH, LOW},   // Giro Izquierda
  {HIGH, LOW, HIGH, HIGH}  // Giro Derecha
};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) pinMode(motores[i], OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void mover(int mov, int time, int speed) {
  for (int i = 0; i < 4; i++) digitalWrite(motores[i], movimientos[mov][i]);
  
  analogWrite(ENA, (mov == 3) ? 0 : speed);  // Velocidad para ENA
  analogWrite(ENB, (mov == 4) ? 0 : speed);  // Velocidad para ENB
  delay(time);
}

int ping(int TriggerPin, int EchoPin) {
unsigned short int duration;
float distanceCm;

digitalWrite(TriggerPin, LOW); //para generar un pulso limpio ponemos a LOW 4us
delayMicroseconds(4);
digitalWrite(TriggerPin, HIGH); //generamos Trigger (disparo) de 10us
delayMicroseconds(10);
digitalWrite(TriggerPin, LOW);

duration = pulseIn(EchoPin, HIGH); //medimos el tiempo entre pulsos, en microsegundos

distanceCm = float(duration)/58.2; //convertimos a distancia, en cm
return distanceCm;
}

void loop() { //repetir siempre lo que se le pide
  float cm = ping(TriggerPin, EchoPin);
  Serial.println("obstaculo identificado");
  if(cm <= 50){
    mover(1, 500, 0); //detener // movimiento, tiempo, potencia
    if (random(0, 2) == 1){ // random numero al azar
      mover(4, 1000, 150); //giro derecha
    }else{
      mover(3, 1000, 150); //giro izquierda
    }
  }
  else{
    mover(0, 1000, 150);//avanzar
}
}
