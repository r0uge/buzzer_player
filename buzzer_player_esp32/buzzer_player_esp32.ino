//Microcontrolador: ESP32
//Descripción:
//  Lee archivos de texto con notas musicales y duraciones para reproducir en un buzzer
//  La notación musical debe ser sostenido reemplazando # por la letra S. 
//  Formato del archivo es NOTA, Duracion , donde se define 4 para una negra y 8 para una corchea
//Autor: Agustin Alvarez
//Fecha: 20/8/2024

//-----------------------------------------------------------------------------
#include <SD.h>
#include <SPI.h>
//#include "pitches.h"  // Necesitas una tabla de frecuencias de notas


//-----------------------------------------------------------------------------
//  Definiciones

#define SD_CS_PIN 5         // Pin CS para la tarjeta SD
#define BUZZER_PIN 25       // Pin para el buzzer

/* Conexion del lector SD
MISO -> GPIO19
MOSI -> GPIO23
SCK -> GPIO18
CS -> GPIO5
*/

/* Conexion del Buzzer
GPIO 25 (DAC1) del ESP32 y a GND
*/

//-----------------------------------------------------------------------------
//  Funciones

void playTone(int note, int duration) {
  tone(BUZZER_PIN, note, duration);
  delay(duration * 1.30);  // Pausa entre notas
  noTone(BUZZER_PIN); //Stop sound
}

void playSongFromFile(File file){
  // Lee cada línea del archivo de texto
  while (melodyFile.available()) {
      String line = melodyFile.readStringUntil('\n');
      
      // Divide la línea en nota y duración
      int commaIndex = line.indexOf(',');
      String noteStr = line.substring(0, commaIndex);
      String durationStr = line.substring(commaIndex + 1);
      
      // Convierte la nota y la duración a enteros
      int note = noteToFrequency(noteStr);  // Función que convierte la nota a frecuencia
      int duration = durationStr.toInt();
      
      // Reproduce la nota
      playTone(note, duration);
    }
}

//-----------------------------------------------------------------------------
// Configuracion
void setup() {
  Serial.begin(115200);
  
  // Inicializa la tarjeta SD
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Tarjeta SD no encontrada");
    while (1);
  }
  Serial.println("Tarjeta SD iniciada");
}

//-----------------------------------------------------------------------------
//  Bucle
void loop() {
  // Abre el archivo de texto con la melodía
  //File melodyFile = SD.open("/melody.txt");
  
  File root = SD.open("/");
  while (true) {
    File file = root.openNextFile();
    if (!file) {
      // Restart the song sequence from the beginning
      root.rewindDirectory();
      continue;
    }
    if (file && !file.isDirectory()) {
      Serial.print("Archivo: ");
      Serial.println(file.name());
      playSongFromFile(file);
      //Serial.println("Reproduciendo melodía...");
      file.close();
    } else {
      Serial.println("No se pudo abrir el archivo de melodía");
    }
  
    delay(5000);  // Espera 5 segundos antes de empezar de nuevo
  }
}

//-----------------------------------------------------------------------------
// Convierte una nota musical (por ejemplo "C4") en frecuencia
int noteToFrequency(String note) {
  if (note == "B0") return 31;
  if (note == "C1") return 33;
  if (note == "CS1") return 35;
  if (note == "D1") return 37;
  if (note == "DS1") return 39;
  if (note == "E1") return 41;
  if (note == "F1") return 44;
  if (note == "FS1") return 46;
  if (note == "G1") return 49;
  if (note == "GS1") return 52;
  if (note == "A1") return 55;
  if (note == "AS1") return 58;
  if (note == "B1") return 62;
  if (note == "C2") return 65;
  if (note == "CS2") return 69;
  if (note == "D2") return 73;
  if (note == "DS2") return 78;
  if (note == "E2") return 82;
  if (note == "F2") return 87;
  if (note == "FS2") return 93;
  if (note == "G2") return 98;
  if (note == "GS2") return 104;
  if (note == "A2") return 110;
  if (note == "AS2") return 117;
  if (note == "B2") return 123;
  if (note == "C3") return 131;
  if (note == "CS3") return 139;
  if (note == "D3") return 147;
  if (note == "DS3") return 156;
  if (note == "E3") return 165;
  if (note == "F3") return 175;
  if (note == "FS3") return 185;
  if (note == "G3") return 196;
  if (note == "GS3") return 208;
  if (note == "A3") return 220;
  if (note == "AS3") return 233;
  if (note == "B3") return 247;
  if (note == "C4") return 262;
  if (note == "CS4") return 277;
  if (note == "D4") return 294;
  if (note == "DS4") return 311;
  if (note == "E4") return 330;
  if (note == "F4") return 349;
  if (note == "FS4") return 370;
  if (note == "G4") return 392;
  if (note == "GS4") return 415;
  if (note == "A4") return 440;
  if (note == "AS4") return 466;
  if (note == "B4") return 494;
  if (note == "C5") return 523;
  if (note == "CS5") return 554;
  if (note == "D5") return 587;
  if (note == "DS5") return 622;
  if (note == "E5") return 659;
  if (note == "F5") return 698;
  if (note == "FS5") return 740;
  if (note == "G5") return 784;
  if (note == "GS5") return 831;
  if (note == "A5") return 880;
  if (note == "AS5") return 932;
  if (note == "B5") return 988;
  if (note == "C6") return 1047;
  if (note == "CS6") return 1109;
  if (note == "D6") return 1175;
  if (note == "DS6") return 1245;
  if (note == "E6") return 1319;
  if (note == "F6") return 1397;
  if (note == "FS6") return 1480;
  if (note == "G6") return 1568;
  if (note == "GS6") return 1661;
  if (note == "A6") return 1760;
  if (note == "AS6") return 1865;
  if (note == "B6") return 1976;
  if (note == "C7") return 2093;
  if (note == "CS7") return 2217;
  if (note == "D7") return 2349;
  if (note == "DS7") return 2489;
  if (note == "E7") return 2637;
  if (note == "F7") return 2794;
  if (note == "FS7") return 2960;
  if (note == "G7") return 3136;
  if (note == "GS7") return 3322;
  if (note == "A7") return 3520;
  if (note == "AS7") return 3729;
  if (note == "B7") return 3951;
  if (note == "C8") return 4186;
  if (note == "CS8") return 4435;
  if (note == "D8") return 4699;
  if (note == "DS8") return 4978;
  // Añade más notas según sea necesario
  return 0;
}
