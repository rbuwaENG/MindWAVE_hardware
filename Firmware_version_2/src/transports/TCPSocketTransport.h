#pragma once
#include "Transport.h"

class WiFiClient;
class WiFiServer;
#define MAX_CLIENTS 10
#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"

#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26

class TCPSocketTransport : public Transport
{
private:
  WiFiServer *server = NULL;
  WiFiServer *textServer = NULL;
  WiFiClient *clients[MAX_CLIENTS] = {NULL};

public:
  void begin();
  void send(void *data, size_t size) override;
  void listen_for_text() override;
};