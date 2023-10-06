#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"

#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26

Audio audio;


void setup()
{

  Serial.begin(115200);
  pinMode(13,OUTPUT);
  pinMode(25,OUTPUT);
  digitalWrite(13,LOW);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin( "C++ Net2", "21472147");

  while (WiFi.status() != WL_CONNECTED)
    delay(1500);
  digitalWrite(13,HIGH);
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(100);
  audio.connecttospeech("Hi i am buwaneka ", "en"); // Google TTS
      
}


void loop() 

{
  
  audio.loop();

}

void audio_info(const char *info) {
  Serial.print("audio_info: "); Serial.println(info);
}
