#include "SRF05.h"  // Aggiunta della libreria per gestire il sensore

// PIN necessari per il funzionamento del sensore, vengono gestiti dalla libreria
const byte TRIG = 7;
const byte ECHO    = 6;

const byte RED_LED = 13;  // PIN a cui è collegato il led
int distance;             // variabile che contiene la distanza
int intensity;            // variabile per stabilire lìintensità variabile del led nel range stabilito

// variabili per gestire la stampa sulla seriale ogni secondo mantenendo la lettura del sensore constante
long int start_time;
long int end_time;

SRF05 SRF(TRIG, ECHO);  // Configurazione necessaria per il richiamo della libreria


void setup() {
  Serial.begin(115200);           // inizializzazione della porta seriale
  while(!Serial);

  SRF.setCorrectionFactor(1.035); // definizione del fattore di correzione

  pinMode(RED_LED, OUTPUT);       // definizione della modalità di utilizzo del PIN del LED
  start_time = millis();          // inizializzazione del conteggio per il timer di 1sec della stampa sulla seriale
}


void loop() {
  delay(10);

  distance = SRF.getMillimeter();   // acquisizione della distanza tramite la funzione fornita dalla libreria

  if (distance>500){                                // se distanza maggiore di 500mm led massima intensità
    intensity = 255;
    analogWrite(RED_LED, intensity);
  } else if (distance<100){                         // se distanza minore di 100mm led spento
    intensity = 0;
    analogWrite(RED_LED, intensity);
  } else if (distance >= 100 && distance <= 500){   // se distanza tra 100 e 500 intensità del led variabile
    intensity = map(distance, 100, 500, 0, 255);
    analogWrite(RED_LED, intensity);
  }

  // stampa sulla seriale dopo 1sec la distanza letta dal sensore
  end_time = start_time + 1000;
  if (millis()>end_time){
    Serial.print("Distanza: ");
    Serial.print(distance);
    Serial.print(" - Intensità: ");
    Serial.println(intensity);
    start_time = end_time;
  }
}