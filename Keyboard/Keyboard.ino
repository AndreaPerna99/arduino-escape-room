#include <PS2Keyboard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//configurazione dei pin
const int DataPin = 3;
const int ClockPin = 2;
const int relayPin = 8;      //pin del relè
const int lockStatePin = 9;  //pin dello stato della serratura
const int ledStatePin = 10;   //pin del secondo LED

//inizializzazione tastiera e LCD (indirizzo LCD tipico: 0x27)
PS2Keyboard keyboard;
LiquidCrystal_I2C lcd(0x27, 16, 2);  //modifica se il tuo LCD è diverso

//variabili per tracciare il cursore e input utente
int cursorX = 0;
String userInput = "";  //stringa per memorizzare l'input
String targetWord = "must get out";  // Parola target

void setup() {
  //setup tastiera, LCD, LED, relè e stato serratura
  keyboard.begin(DataPin, ClockPin);
  lcd.init();
  lcd.backlight();  //attiva la retroilluminazione
  pinMode(relayPin, OUTPUT);
  pinMode(ledStatePin, OUTPUT);  //pin del secondo LED
  pinMode(lockStatePin, INPUT_PULLUP);  //stato della serratura
  digitalWrite(relayPin, LOW);  //spegni il relè all'inizio
  digitalWrite(ledStatePin, LOW);  //spegni il secondo LED all'inizio

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Parola D'Ordine:");
  lcd.setCursor(0, 1);
}

void loop() {

  //controllo continuo dello stato della serratura
  int lockState = digitalRead(lockStatePin);
  
  if (lockState == HIGH) {
    digitalWrite(ledStatePin, LOW);  //accendi il secondo LED se la serratura è aperta
  }
  else {
    digitalWrite(ledStatePin, HIGH);  //spegni il secondo LED se la serratura è chiusa
  }

  if (keyboard.available()) {
    char c = keyboard.read();  //legge il carattere dalla tastiera

    if (c == PS2_ENTER) {

      if (userInput == targetWord) {
        lcd.setCursor(0, 1);
        lcd.print("CORRETTO!       ");
        digitalWrite(relayPin, HIGH);  //attiva il relè per l'elettroserratura
      }
      
      else {
        lcd.setCursor(0, 1);
        lcd.print("ERRATO!         ");
        digitalWrite(relayPin, LOW);  //spegni il relè
      }

      //attendi un secondo e ripulisci il display
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Parola D'Ordine:");
      lcd.setCursor(0, 1);

      //disattiva il relè dopo il controllo
      digitalWrite(relayPin, LOW);

      //reset delle variabili
      userInput = "";
      cursorX = 0;
    }
    else if (c == PS2_BACKSPACE) {
      if (cursorX > 0) {
        cursorX--;  //sposta il cursore indietro
        userInput.remove(userInput.length() - 1);  //rimuove l'ultimo carattere dalla stringa
        lcd.setCursor(cursorX, 1);
        lcd.print(" ");  //cancella il carattere sul display
        lcd.setCursor(cursorX, 1);  //torna alla posizione
      }
    }

    else {
      //aggiungi il carattere alla stringa
      userInput += c;
      lcd.setCursor(cursorX, 1);
      lcd.print(c);  //stampa il carattere sul display
      cursorX++;  //avanza il cursore

      //se raggiunge la fine della riga, azzera il cursore (opzionale)
      if (cursorX >= 16) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Troppo lunga!");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Scrivi:");
        lcd.setCursor(0, 1);
        userInput = "";  //resetta l'input
        cursorX = 0;
      }
    }
  }
}
