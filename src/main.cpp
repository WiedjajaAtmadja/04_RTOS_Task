#include <Arduino.h>

#define LED_RED   21
#define LED_GREEN 22
#define LED_BLUE  23

void taskLedRed(void *pvParameters) {
  pinMode(LED_RED, OUTPUT);
  while (true) {
    Serial.printf("taskLedRed() run on Core: %d\r\n", xPortGetCoreID());    
    digitalWrite(LED_RED, HIGH);
    // vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(LED_RED, LOW);
    // vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void taskLedGreen(void *pvParameters) {
  pinMode(LED_GREEN, OUTPUT);
  while (true) {
    Serial.printf("taskLedGreen() run on Core: %d\r\n", xPortGetCoreID());
    digitalWrite(LED_GREEN, HIGH);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    digitalWrite(LED_GREEN, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  pinMode(LED_BLUE, OUTPUT);
  Serial.begin(115200);
  xTaskCreatePinnedToCore(taskLedRed, "taskLedRed", configMINIMAL_STACK_SIZE+1024, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(taskLedGreen, "taskLedGreen", configMINIMAL_STACK_SIZE+1024, NULL, 1, NULL, 1);
}

void loop() {
// blink the blue led
  Serial.printf("loop() run on Core: %d\r\n", xPortGetCoreID());
  digitalWrite(LED_BLUE, HIGH);
  delay(100);
  digitalWrite(LED_BLUE, LOW);
  delay(1000);
}

