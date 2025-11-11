#include <Arduino.h>

#define CLK 10
#define DT  11
#define SW  12

#define CORE_ID 1

int counter = 0;
int lastCLK = HIGH;

void taskEncoder(void *pvParameters) {
  while (1) {
    int newCLK = digitalRead(CLK);

    if (newCLK != lastCLK) {
      if (newCLK == LOW) {
        if (digitalRead(DT) != newCLK) counter++;
        else counter--;
        
        Serial.print("Encoder counter: ");
        Serial.print(counter);
        Serial.print(" | Core: ");
        Serial.println(xPortGetCoreID());
      }
    }

    lastCLK = newCLK;
    delay(5);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT,  INPUT_PULLUP);
  pinMode(SW,  INPUT_PULLUP);

  xTaskCreatePinnedToCore(taskEncoder,"taskEncoder",2000,NULL,1,NULL,CORE_ID);
}

void loop() {}
