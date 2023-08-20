#include <SD.h>
#include <SPI.h>

const int chipSelect = 53;
int ledPin6 = 6;
int ledPin5 = 5;
int buzzerPin8 = 8;
long soilMoisture[1000];
unsigned long redLedOnTime = 0;

void setup() {
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(buzzerPin8, OUTPUT);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  
  for (int i = 0; i < 400; i++) {
    soilMoisture[i] = random(-402500000, -400900000);
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.println(soilMoisture[i]);
      dataFile.close();
    } else {
      Serial.println("error opening datalog.txt");
    }
  }
  
  for (int i = 400; i < 1000; i++) {
    soilMoisture[i] = random(-404100000, -402600000);
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.println(soilMoisture[i]);
      dataFile.close();
    } else {
      Serial.println("error opening datalog.txt");
    }
  }
}

void loop() {
  for (int i = 0; i < 1000; i++) {
    if (soilMoisture[i] <= -402500000) {
      digitalWrite(ledPin6, HIGH);
      digitalWrite(ledPin5, LOW);
      digitalWrite(buzzerPin8, LOW);
      redLedOnTime = millis();
    } else if (soilMoisture[i] >= -402600000) {
      if (millis() - redLedOnTime <= 5000) {
        digitalWrite(ledPin6, LOW);
        digitalWrite(ledPin5, HIGH);
        digitalWrite(buzzerPin8, HIGH);
      } else {
        digitalWrite(ledPin6, HIGH);
        digitalWrite(ledPin5, LOW);
        digitalWrite(buzzerPin8, LOW);
      }
    }
    delay(50);
  }
}


