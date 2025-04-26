///////////////////////////////////////////
/////////////// Librerie //////////////////
///////////////////////////////////////////

#include <IRremote.h>

///////////////////////////////////////////
/////////////// Parametri /////////////////
///////////////////////////////////////////

// Pin di controllo del Servo42C
const int stepPin = 8;  // Pin STEP
const int dirPin = 9;   // Pin DIR
const int enablePin = 7; // Pin ENABLE
const int buzzerPin = 5; // Pin del buzzer
const int receiverPin = 10; // Pin del ricevitore IR
const int led = 4;

// Parametri per il profilo di accelerazione
float k = 10.0;           // Ripidità della curva sigmoidale
float x0 = 0.5;           // Punto centrale della curva sigmoide
int delayMin = 200;       // Minimo ritardo
int delayMax = 1000;      // Massimo ritardo

// Configurazione movimento
const int stepsPerRevolution = 200; // Numero di passi per un giro completo del motore
const int microstepping = 16;       // Valore del microstepping (se configurato)
const int totalSteps = stepsPerRevolution * microstepping; // Passi totali per un giro completo
bool isMoving = false;               // Controlla se il motore è in movimento

IRrecv irrecv(receiverPin);          // Inizializza il ricevitore IR sul pin 10
decode_results results;

// codici IR per attivazione sequenze: 1-CAMERA, 2-DOWN, 3-SX, 4-UP, 5-DX, 6-STOP, 7-PLAY, 8-PAUSE, 9-OFF
const unsigned long codiciIR[] = {0xA6B92, 0x5EB92, 0xDEB92, 0x9EB92, 0x3EB92, 0x1CB92, 0x4CB92, 0x9CB92, 0xA8B92};
const int sequenze[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

///////////////////////////////////////////
/////////// Inizializzazione //////////////
///////////////////////////////////////////

void setup() {

  Serial.begin(9600);                // Inizializza la comunicazione seriale
  pinMode(stepPin, OUTPUT);          // Configura il pin STEP
  pinMode(dirPin, OUTPUT);           // Configura il pin DIR
  pinMode(led, OUTPUT);
  pinMode(enablePin, OUTPUT);        // Configura il pin ENABLE
  pinMode(buzzerPin, OUTPUT);        // Configura il pin del buzzer
  irrecv.enableIRIn();               // Inizia a ricevere segnali IR
  digitalWrite(led, LOW);

  digitalWrite(enablePin, LOW);      // Abilita il motore
}

///////////////////////////////////////////
//////////////// Funzioni /////////////////
///////////////////////////////////////////

void avviaMovimento(int sequence) {

  isMoving = true;

  switch (sequence) {

    case 1: 
      eseguiPassi(totalSteps/12, true, 12);
      break;

    case 2: //STEP IN SENSO ORARIO
      eseguiPassi(stepsPerRevolution / 4, false, 1);
      break;

    case 3: //GIRO COMPLETO IN SENSO ORARIO CON FERMATE
      eseguiPassi(totalSteps / 12, true, 12);
      break;

    case 4: //STEP IN SENSO ANTI-ORARIO
      eseguiPassi(stepsPerRevolution / 4, true, 1);
      break;

    case 5: //GIRO COMPLETO IN SENSO ANTI-ORARIO CON FERMATE
      eseguiPassiAccelerati(totalSteps / 12, false, 12);
      break;

    case 6:
      eseguiPassiConAccelerazione(totalSteps, true); // Movimento con accelerazione
      break;

    case 7:
      //eseguiTraiettoria(0, 0, 0, 10, 0, 0, 2); // Movimento da 0 a 10 in 5 sec
      break;

    case 8:
      eseguiPassiConCurvaMista(totalSteps, true);
      break;

    case 9:
      eseguiPassiAccelerati(totalSteps / 6, false, 6);
      break;

    default:
      Serial.println("Sequenza sconosciuta.");
      break;
  }

  Serial.println("Movimento completato.");
  isMoving = false;
}

void eseguiGiroCompleto() {

    int passiTotali = totalSteps;  // Un giro completo
    int passiPerFermata = passiTotali / 12; // Divide il giro in 12 sezioni
    float t = 0;
    
    digitalWrite(dirPin, HIGH); // Imposta la direzione in avanti

    for (int i = 0; i < 12; i++) { // 12 segmenti del giro
        for (int step = 0; step < passiPerFermata; step++) {
            
            // Calcola un delay variabile per una curva morbida
            int delayTime = 50 + 50 * (1 - cos(PI * t)); // Coseno per accelerazione dolce
            
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(delayTime);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(delayTime);

            t += 1.0 / passiTotali; // Incremento normalizzato per un ciclo fluido
        }
    }
}

void eseguiPassiConAccelerazione(int passiTotali, bool direzione) {

  digitalWrite(dirPin, direzione ? HIGH : LOW); // Imposta la direzione
  
  float k = 5.0; // Ripidità della curva sigmoidale
  float x0 = passiTotali / 2.0; // Punto centrale della curva
  int delayMin = 100; // Minimo ritardo tra i passi
  int delayMax = 2000; // Massimo ritardo tra i passi

  for (int step = 0; step < passiTotali; step++) {
    // Calcola la posizione normalizzata (tra 0 e 1)
    float x = (float)step / passiTotali;
    
    // Applica la funzione sigmoidale
    float sigmoid = 1.0 / (1.0 + exp(-k * (x - 0.5)));
    
    // Calcola il ritardo in base alla curva sigmoidale
    int delayTime = delayMin + (delayMax - delayMin) * (1 - sigmoid);
    delayTime = (delayTime)*(-1) + delayMax + delayMin;

    // Genera il passo
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayTime);
  }
}

void eseguiPassiConCurvaMista(int passiTotali, bool direzione) {
  
  int lineareInizio = passiTotali * 0.2; // 20% dei passi iniziali lineari
  int lineareFine = passiTotali * 0.2;   // 20% dei passi finali lineari
  int centrale = passiTotali - (lineareInizio + lineareFine);

  digitalWrite(dirPin, direzione ? HIGH : LOW); // Imposta la direzione

  for (int step = 0; step < passiTotali; step++) {

    int delayTime;

    if (step < lineareInizio) {

      // Tratto lineare iniziale
      delayTime = delayMin;
    } 

    else if (step >= lineareInizio && step < lineareInizio + centrale) {

      // Tratto sigmoidale centrale
      float x = (float)(step - lineareInizio) / centrale;
      float sigmoid = 1 / (1 + exp(-k * (x - x0)));
      delayTime = delayMin + (delayMax - delayMin) * (1 - sigmoid);
      delayTime = (delayTime)*(-1) + delayMax + delayMin;
    } 

    else {
      // Tratto lineare finale
      delayTime = delayMax;
    }

    // Genera il passo
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayTime);
  }

}

void eseguiPassi(int passiPerFermata, bool direzione, int fermate) {

  digitalWrite(dirPin, direzione ? HIGH : LOW); // Imposta la direzione

  for (int i = 0; i < fermate; i++) {

    for (int step = 0; step < passiPerFermata; step++) {

      digitalWrite(stepPin, HIGH);
      delayMicroseconds(300); // Impulso per il pin STEP
      digitalWrite(stepPin, LOW);
      delayMicroseconds(300); // Pausa tra gli impulsi
    }

    delay(300); // Pausa tra le fermate
  }
}

float sigmoid_function(int Passi, int step){

  float k = 5.0; // Ripidità della curva sigmoidale
  float x0 = Passi / 2.0; // Punto centrale della curva
  int delayMin = 100; // Minimo ritardo tra i passi
  int delayMax = 2000; // Massimo ritardo tra i passi

  // Calcola la posizione normalizzata (tra 0 e 1)
  float x = (float)step / Passi;
  
  // Applica la funzione sigmoidale
  float sigmoid = 1.0 / (1.0 + exp(-k * (x - 0.5)));
  
  // Calcola il ritardo in base alla curva sigmoidale
  int delayTime = delayMin + (delayMax - delayMin) * (1 - sigmoid);
  delayTime = (delayTime)*(-1) + delayMax + delayMin;

  return delayTime;
}

void eseguiPassiAccelerati(int passiPerFermata, bool direzione, int fermate) {

  digitalWrite(dirPin, direzione ? HIGH : LOW); // Imposta la direzione

  for (int i = 0; i < fermate; i++) {

    for (int step = 0; step < passiPerFermata; step++) {

      //calcola il ritardo temporale con la funzione sigmoidale
      int delayTime = sigmoid_function(passiPerFermata, step);

      // Genera il passo
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(delayTime);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(delayTime);
    }

    delay(300); // Pausa tra le fermate
  }
}

///////////////////////////////////////////
//////////// Ciclo Principale /////////////
///////////////////////////////////////////

void loop() {

  if (!isMoving) { // Esegui solo se il motore è fermo
  
    if (irrecv.decode(&results)) { // Il telecomando ha ricevuto un input

      Serial.print("Segnale IR ricevuto: 0x");
      Serial.println(results.value, HEX);

      // Cerca il codice ricevuto nell'array
      for (int i = 0; i < 9; i++) {
        if (results.value == codiciIR[i]) {
          avviaMovimento(sequenze[i]); // Avvia la sequenza corrispondente
          break;
        }
      }

      irrecv.resume(); // Riprendi la ricezione IR
    }
  }
}



