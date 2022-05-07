#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

//Task handles
static TaskHandle_t task_1 =NULL;
static TaskHandle_t task_2 =NULL; 

// Pins
static const int LED_PIN = LED_BUILTIN;


//*****************************************************************************
// Tasks

// Task1: Blink LED for 500ms 
void task1(void *parameter) {
  while (1) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(500/ portTICK_PERIOD_MS);
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// Task2: Blink LED for 500ms 
void task2(void *parameter) {
  while (1) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(300/ portTICK_PERIOD_MS);
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}


//*****************************************************************************
// Main

void setup() {

  // Configure pin
  pinMode(LED_PIN, OUTPUT);


  // Start to Blink LED for 500ms 
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
            task1,          // Function to be called
            "Task 1",       // Name of task
            1024,           // Stack size (bytes in ESP32, words in FreeRTOS)
            NULL,           // Parameter to pass
            1,              // Task priority
            NULL,           // Task handle
            app_cpu);       // Run on one core for demo purposes (ESP32 only)
            
  // Start to Blink LED for 300ms 
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
            task2,          // Function to be called
            "Task 2",       // Name of task
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
