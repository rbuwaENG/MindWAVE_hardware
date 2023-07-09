#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <ESPmDNS.h>
#include "Application.h"
#include "config.h"


void setup()
{
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  Serial.println("Starting up");
  delay(1000);
 
  WiFiManager wm;
  wm.resetSettings();
   bool res;
   res = wm.autoConnect("MindWave_testing"); // anonymous ap
   while(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    }

  // disable WiFi sleep mode
  WiFi.setSleep(WIFI_PS_NONE);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.println("");

  // startup MDNS
  if (!MDNS.begin(MDNS_DOMAIN))
  {
    Serial.println("MDNS.begin failed");
  }
  Serial.println("Creating microphone");
  Application *application = new Application();
  application->begin();
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}