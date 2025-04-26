#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Imposta l'indirizzo I2C del modulo LCD
//LiquidCrystal_I2C lcd(0x3E, 16, 2);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definizione dei pin
const int trigPin = 9;
const int echoPin = 10;
const int ledRosso = 13;
const int ledGiallo = 12;

// Variabili
long durata;
int distanza;
String statoDisplay = "";  // Variabile per memorizzare lo stato corrente del display

void setup() {
  // Configurazione dei pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledRosso, OUTPUT);
  pinMode(ledGiallo, OUTPUT);

  // Inizializzazione della comunicazione seriale (opzionale)
  Serial.begin(9600);

  // Inizializzazione del display LCD
  lcd.init();            // Inizializza il display
  lcd.backlight();       // Attiva la retroilluminazione
  lcd.setCursor(0, 0);
  lcd.print("Rilevamento attivo");
}

void loop() {
  // Invia un impulso al trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calcola la durata dell'eco
  durata = pulseIn(echoPin, HIGH);

  // Calcola la distanza in cm
  distanza = durata * 0.034 / 2;

  // Determina il messaggio da visualizzare
  if (distanza > 0 && distanza <= 15) {
    digitalWrite(ledRosso, HIGH);   // Accende il LED rosso
    digitalWrite(ledGiallo, LOW);   // Spegne il LED giallo
    if (statoDisplay != "Error") {
      statoDisplay = "Error";
      lcd.clear();                  // Cancella il display
      lcd.setCursor(0, 0);
      lcd.print(statoDisplay);      // Stampa "Ostacolo rilevato"
    }
  } 
  
  delay(200); // Piccola pausa per evitare aggiornamenti troppo rapidi
}
