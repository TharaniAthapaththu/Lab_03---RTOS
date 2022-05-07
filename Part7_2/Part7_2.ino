#include <WiFi.h>

const char* ssid     = "EN20412098";
const char* password = "Tharani@123";

void C1Task(void *parameters) {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  Serial.print("Connected to hotspot on CORE ");
  Serial.println(xPortGetCoreID());

  vTaskDelete(NULL);
}

void C2Task(void *parameters) {
  
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  
  xTaskCreatePinnedToCore(C1Task,
                          "Task A Core0",
                          4096,
                          NULL,
                          1,
                          NULL,
                          0);
}

void loop() { 
  
}
