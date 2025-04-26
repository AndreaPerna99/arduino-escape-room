#include <Keypad.h>
#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Definizione del layout del tastierino numerico (4 righe e 4 colonne)
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {40, 50, 48, 44}; // Pin delle righe
byte colPins[COLS] = {42, 38, 46, 52}; // Pin delle colonne

// Creazione dell'oggetto Keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String codiceInserito = ""; // Stringa per il codice inserito
String codiceCorretto = "1234"; // Codice corretto
const int ledPinB = 3; // Pin del LED rosso
const int ledPinR = 4; // Pin del LED rosso
const int ledPinB_ext = 26; // Pin del LED rosso
const int ledPinR_ext = 28; // Pin del LED rosso
const int ConsensoSerranda = 5; // Pin del LED verde
const int PulsA = 22; // Pin del pulsante A
const int PulsB = 24; // Pin del pulsante B
const int SwitchB = 8; // Pin del pulsante A
const int SwitchR = 9; // Pin del pulsante B
const int PulsO = 2; // Pin dell'occhio
const long interval = 1000;  // Intervallo di tempo in millisecondi (5 secondi)
unsigned long previousMillis = 0;  // Tempo di riferimento precedente

Servo myServo;              // Oggetto servo

//Variabili globali
int giusto = 0;
bool EnablePassword = true;
bool StatoBottoneA = 0;
bool UltimoStatoBottoneA = 0;
bool StatoBottoneB = 0;
bool UltimoStatoBottoneB = 0;
bool StatoBottoneO = 0;
bool UltimoStatoBottoneO = 0;
bool StatoLedA = false;
bool StatoLedB = false;
bool Serranda = false;
LiquidCrystal_I2C lcd(0x3f, 16, 2); // Indirizzo 0x3F, 16 colonne e 2 righe

void setup() {
  pinMode(ledPinR, OUTPUT); // Imposta il pin del LED come output
  pinMode(ledPinB, OUTPUT); // Imposta il pin del LED come output
  pinMode(ConsensoSerranda, OUTPUT); // Imposta il pin del LED come output
  pinMode(PulsA, INPUT_PULLUP); // Imposta il pin pulsA
  pinMode(PulsB, INPUT_PULLUP); // Imposta il pin pulsB
  pinMode(SwitchB, INPUT_PULLUP); // Imposta il pin pulsB
  pinMode(SwitchR, INPUT_PULLUP); // Imposta il pin pulsB
  pinMode(ledPinB_ext, OUTPUT);
  pinMode(ledPinR_ext, OUTPUT);
  digitalWrite(ledPinB_ext, LOW);
  digitalWrite(ledPinR_ext, LOW);
  pinMode(PulsO, INPUT_PULLUP); // Imposta il pin pulsO
  digitalWrite(ledPinR, HIGH); // Spegne inizialmente il LED
  digitalWrite(ledPinB, HIGH); // Spegne inizialmente il LED
  digitalWrite(ConsensoSerranda, HIGH); // Spegne inizialmente il LED
  myServo.attach(7);        // Collegare il servo al pin 7
  myServo.write(10);         // Inizializza il servo a 0 gradi
  Serial.begin(9600); // Avvia la comunicazione seriale per il debug
  lcd.init();
  lcd.backlight();

  //lcd.print("Katy Perry"); // Stampa il codice inserito sulla prima riga
}

void loop() {
  
  unsigned long currentMillis = millis();

  StatoBottoneA = digitalRead(PulsA);
  StatoBottoneB = digitalRead(PulsB);

  if (EnablePassword == true){
     char tasto = keypad.getKey(); // Ottiene il tasto premuto

    if (tasto) {
      if (tasto == '#') { // Se si preme '#', controlla il codice inserito
        Serial.println("Codice inserito: " + codiceInserito);
      
        if (codiceInserito == codiceCorretto) {
          lcd.setCursor(0, 1); // Posiziona il cursore sulla prima riga
          lcd.print("Codice corretto!");
          giusto = 1;
          EnablePassword = false;
        } 
        else {
          lcd.setCursor(0, 1); // Posiziona il cursore sulla prima riga
          lcd.print("Codice errato.");
          giusto = 0;
        }
      
        delay(2000); // Mostra il risultato per 2 secondi
        lcd.clear(); // Pulisce il display
        codiceInserito = ""; // Resetta il codice inserito
        lcd.setCursor(0, 0); // Posiziona il cursore sulla prima riga
      } 
      else if (tasto == '*') { // Se si preme '*', resetta il codice inserito
        codiceInserito = "";
        lcd.clear(); // Pulisce lo schermo LCD
        lcd.setCursor(0, 0); // Posiziona il cursore sulla prima riga
      } 
      else if (codiceInserito.length() < 10) { // Limita il codice a 16 caratteri
        codiceInserito += tasto; // Aggiunge il tasto premuto al codice inserito
        lcd.setCursor(0, 0); // Posiziona il cursore sulla prima riga
        lcd.print(codiceInserito); // Stampa il codice inserito sulla prima riga
      }
    
      //Serial.println("Tasto premuto: " + String(tasto)); // Debug seriale
    }
  }
  if (giusto == 1){
    if ((StatoBottoneA == HIGH) && (UltimoStatoBottoneA == LOW)){
      StatoLedA = false;
    }
    else if ((StatoBottoneA == LOW) && (UltimoStatoBottoneA == HIGH)){
      StatoLedA = true;
      //lcd.print("A");
    }
    if ((StatoBottoneB == HIGH) && (UltimoStatoBottoneB == LOW)){
      StatoLedB = false;
    }
    else if ((StatoBottoneB == LOW) && (UltimoStatoBottoneB == HIGH)){
      StatoLedB = true;
      lcd.print("B");
    }
  }
  else if (giusto == 0){
    digitalWrite(ledPinR, HIGH); // Spegne il LED
  }
  if (StatoLedA == true && StatoLedB == true){
    if (digitalRead(SwitchR) ==  HIGH && digitalRead(SwitchB) == LOW){
      
      //gestione LED interni
      digitalWrite(ledPinB, HIGH); // Spegne il LED
      digitalWrite(ledPinR, LOW); // Spegne il LED

      //gestione LED esterni
      digitalWrite(ledPinB_ext, LOW);
      digitalWrite(ledPinR_ext, HIGH);

      Serial.println("ROSSO");
    }
    else if (digitalRead(SwitchB) ==  HIGH && digitalRead(SwitchR) == LOW){

      //gestione LED interni
      digitalWrite(ledPinR, HIGH); // Spegne il LED
      digitalWrite(ledPinB, LOW); // Spegne il LED

      //gestione LED esterni
      digitalWrite(ledPinB_ext, HIGH);
      digitalWrite(ledPinR_ext, LOW);
      
      Serial.println("BLU");
    }
    Serranda = true;
    previousMillis = currentMillis;
  }
  else if ((currentMillis - previousMillis >= interval) && ((StatoLedA == false) || (StatoLedB == false))){

    //gestione LED esterni
    digitalWrite(ledPinR, HIGH); // Spegne il LED
    digitalWrite(ledPinB, HIGH); // Spegne il LED

    //gestione LED esterni
    digitalWrite(ledPinB_ext, LOW);
    digitalWrite(ledPinR_ext, LOW);
    
    Serranda = false;
    digitalWrite(ConsensoSerranda, HIGH);
    previousMillis = currentMillis;
  }
  else {
  Serranda = false;
  //previousMillis = 0;
  }
  if (digitalRead(PulsO) == LOW && Serranda == true){
    digitalWrite(ConsensoSerranda, LOW);
    lcd.print("S");
    myServo.write(90);
  }
  else {
  myServo.write(1);
  }

  UltimoStatoBottoneA = StatoBottoneA;
  UltimoStatoBottoneB = StatoBottoneB;
  
}