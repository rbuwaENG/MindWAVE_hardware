#include <freertos/FreeRTOS.h>
#include "Application.h"
#include <ADCSampler.h>
#include "transports/TCPSocketTransport.h"
#include "config.h"

const int FILTER_WINDOW_SIZE = 10; // Adjust the window size as desired

void Application::begin()
{
  // Check max4466 module
  this->input = new ADCSampler(ADC_UNIT_1, ADC1_CHANNEL_0, i2s_adc_config);
  this->input = input;
  this->transport2 = new TCPSocketTransport();
  this->input->start();
  this->transport2->begin();

  // Create task with high priority "2"
  TaskHandle_t text_task_handle;
  xTaskCreate(Application::listen_for_text_task, "text_task", 8192, this, 2, &text_task_handle);

  // Create task with low priority "1"
  TaskHandle_t stream_task_handle;
  xTaskCreate(Application::stream_task, "stream_task", 8192, this, 1, &stream_task_handle);
}

// For audio stream
void Application::stream_task(void *param)
{
  Application *app = (Application *)param;
  // Now just read from the microphone and send to the clients
  int16_t *samples = (int16_t *)malloc(sizeof(int16_t) * 1024);
  int16_t *filtered_samples = (int16_t *)malloc(sizeof(int16_t) * 1024);

  // Initialize filter window
  int16_t filter_window[FILTER_WINDOW_SIZE] = {0};
  int filter_window_index = 0;

  Serial.println("Streaming running");
  while (true)
  {
    // Read from the microphone
    int samples_read = app->input->read(samples, 1024);

    // Apply moving average filter to the samples
    for (int i = 0; i < samples_read; i++)
    {
      // Add the current sample to the filter window
      filter_window[filter_window_index] = samples[i];

      // Compute the average of the samples in the filter window
      int32_t sum = 0;
      for (int j = 0; j < FILTER_WINDOW_SIZE; j++)
      {
        sum += filter_window[j];
      }
      filtered_samples[i] = sum / FILTER_WINDOW_SIZE;

      // Update the filter window index
      filter_window_index = (filter_window_index + 1) % FILTER_WINDOW_SIZE;
    }

    // Stream filtered audio
    app->transport2->send(filtered_samples, samples_read * sizeof(int16_t));
  }

  free(samples);
  free(filtered_samples);
}

void Application::listen_for_text_task(void *param)
{
  Application *app = (Application *)param;
  // Listen to text
  Serial.println("TTS running");
  while (true)
  {
    app->transport2->listen_for_text();
    //vTaskDelay(pdMS_TO_TICKS(1000));
  }
}