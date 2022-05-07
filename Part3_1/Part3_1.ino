#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu =0;
#else
static const BaseType_t app_cpu =1;
#endif

static const int LED_PIN = LED_BUILTIN;     // configure the internal LED

// Task : Blink a LED
void blinkLED (void*parameter){             // as this is FREERTOS function, this returns only the void pointer parameter
  while(1){
    digitalWrite(LED_PIN ,HIGH);
    vTaskDelay(500/portTICK_PERIOD_MS);     // this fuction tells sheduler to run other tasks until specified delay time is up
    digitalWrite(LED_PIN,LOW);
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
}
    
void setup() {
    pinMode (LED_PIN , OUTPUT);     // configure the LED

 //Task run forever
    xTaskCreatePinnedToCore(
    blinkLED,                       // function to be called
   "blinkLED",                      // name of the function
   1024,                            // stack size (bytes in ESP32, words in RTOS)
   NULL,                            // parameter to pass to function
   1,                               // task priority (0 to configMAX_PRIORITIES-1)
   NULL,                            // task handle
   app_cpu);                        // run on one core 
}

void loop() {
  // put your main code here, to run repeatedly:
}
