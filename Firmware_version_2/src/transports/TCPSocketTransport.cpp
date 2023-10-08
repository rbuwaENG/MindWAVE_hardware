#include <WiFiServer.h>
#include "TCPSocketTransport.h"

Audio audio(false, 3, I2S_NUM_1);

void TCPSocketTransport::begin()
{
  //server running on port 5001 to stream audio
  server = new WiFiServer(5001);
  server->begin();
  Serial.println("Connect to TCP socket microphone.local:5001 to listen to audio stream");

  //server running on port 5002 listen for text
  textServer = new WiFiServer(5002);
  textServer->begin();
  Serial.println("Connect to TCP socket microphone.local:5002 to send a text to ESP32");

  //pins of speaker
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(100);
  audio.setConnectionTimeout(10000, 10000);
  audio.connecttohost("http://192.168.8.141:5001/audio.mp3");
 
  //audio.connecttospeech("Hi i am alice", "en"); // Google TTS
}

//function to send audio data
void TCPSocketTransport::send(void *data, size_t len)
{
  // get any new connections
  WiFiClient client = server->available();
  if (client)
  {
    Serial.println("Server found");
    // add to the list of clients
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
      if (NULL == clients[i])
      {
        clients[i] = new WiFiClient(client);
        break;
      }
    }
  }
  // send the audio data to any clients
  for (int i = 0; i < MAX_CLIENTS; i++)
  {
    if (clients[i] != NULL && (*clients[i]))
    {
      // send the samples to the client
      clients[i]->write((uint8_t *)data, len);
    }
    else
    {
      // client has gone away, remove it from the list
      clients[i] = NULL;
    }
  }
}

void audio_info(const char *info) 
{
  Serial.print("audio_info: "); 
  Serial.println(info);
}

//function for receiving text data
void TCPSocketTransport::listen_for_text()
{
  /*
  // Text Server
  WiFiClient textClient = textServer->available();
  if (textClient) {
    Serial.println("New text client connected");
    while (textClient.connected()) {
      if (textClient.available()) {
        String message = textClient.readStringUntil('\n');
        Serial.println(message);
        
        
      }
    }
    textClient.stop();
    Serial.println("Text client disconnected");
  }
  */

  audio.loop();
}