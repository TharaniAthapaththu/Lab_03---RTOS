#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif


void C1Task(void *parameters) {

  while(1){
    Serial.print("I am Task A I am Running on CORE ");
    Serial.println(xPortGetCoreID());
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }  
}

void C2Task(void *parameters) {

  while(1){
    Serial.print("I am Task B I am Running on CORE ");
    Serial.println(xPortGetCoreID());
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }  
}


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  // Start task A
  xTaskCreatePinnedToCore(C1Task,
                          "Task A Core0",
                          1024,
                          NULL,
                          1,
                          NULL,
                          0);
  
  // Start task B
  xTaskCreatePinnedToCore(C2Task,
                          "Task B Core1",
                          1024,
                          NULL,
                          1,
                          NULL,
                          1);
  
  // Delete "setup and loop" task
  vTaskDelete(NULL);

}

void loop() {
  // put your main code here, to run repeatedly:

}
