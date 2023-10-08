#pragma once

class Transport;
class I2SSampler;

class Application
{
private:
  Transport *transport2 = NULL;
  I2SSampler *input = NULL;

public:
  void begin();
  static void stream_task(void *param);
  static void listen_for_text_task(void *param);
};