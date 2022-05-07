// Needed for atoi()
#include <stdlib.h>
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

// Settings
static const uint8_t buf_len = 20;

// Pins
static const int LED_PIN = LED_BUILTIN;

// Globals
static int LED_DELAY = 500;   // ms

//*****************************************************************************
// Tasks

// Task: Blink LED 
void blinkLED(void *parameter) {
  while (1) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(LED_DELAY/ portTICK_PERIOD_MS);
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(LED_DELAY / portTICK_PERIOD_MS);
  }
}

// Task: Read from serial terminal
void readSerial(void *parameters) {

  char c;
  char buf[buf_len];
  uint8_t idx = 0;

  // Clear whole buffer
  memset(buf, 0, buf_len);

  // Loop forever
  while (1) {

    // Read characters from serial
    if (Serial.available() > 0) {
      c = Serial.read();

      // Update delay variable and reset buffer if we get a newline character
      if (c == '\n') {
        LED_DELAY = atoi(buf);
        Serial.print("Updated LED delay to: ");
        Serial.println(LED_DELAY);
        memset(buf, 0, buf_len);
        idx = 0;
      } else {
        
        // Only append if index is not over message limit
        if (idx < buf_len - 1) {
          buf[idx] = c;
          idx  ;
        }
      }
    }
  }
}

//*****************************************************************************
// Main

void setup() {

  // Configure pin
  pinMode(LED_PIN, OUTPUT);

  // Configure serial and wait a second
  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("Enter a number in milliseconds to change the LED delay.");

  // Start blink task
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
            blinkLED,       // Function to be called
            "Blink LED",    // Name of task
            1024,           // Stack size (bytes in ESP32, words in FreeRTOS)
            NULL,           // Parameter to pass
            1,              // Task priority
            NULL,           // Task handle
            app_cpu);       // Run on one core for demo purposes (ESP32 only)
            
  // Start serial read task
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
            readSerial,     // Function to be called
            "Read Serial",  // Name of task
            1024,           // Stack size (bytes in ESP32, words in FreeRTOS)
            NULL,           // Parameter to pass
            1,              // Task priority (must be same to prevent lockup)
            NULL,           // Task handle
            app_cpu);       // Run on one core for demo purposes (ESP32 only)

  // Delete "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {
  // Execution should never get here
}
