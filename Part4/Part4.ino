// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Some string to print
const char msg[] = "Tharani";

// Task handles
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;
//*****************************************************************************

// Tasks
// Task: print to Serial Terminal with lower priority

void startTask1(void *parameter) {
  // Count number of characters in string
  int msg_len = strlen(msg);
  // Print string to Terminal
  while (1) {
    Serial.println();
    for (int i = 0; i < msg_len; i++) {
      Serial.print(msg[i]);
    }
    Serial.println();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
// Task: print to Serial Terminal with higher priority
void startTask2(void *parameter) {
  while (1) {
    Serial.print('*');
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {
   Serial.begin(115200);
     xTaskCreatePinnedToCore(              //use xTaskCreate() in vanila freertos
                          startTask1,    //function 
                          "Task1",      //name of the task
                          1024,         //stack size(bytes)
                          NULL,         //parameter to pass to function
                          1,            //task priority
                          NULL,         //task handle
                          app_cpu);     //run on 1 core for demo porpuse

    xTaskCreatePinnedToCore(              //use xTaskCreate() in vanila freertos
                          startTask2,    //function 
                          "Task2", //name of the task
                          1024,         //stack size(bytes)
                          NULL,         //parameter to pass to function
                          1,            //task priority
                          NULL,         //task handle
                          app_cpu);     //run on 1 core for demo porpuse
}

void loop() {
}
