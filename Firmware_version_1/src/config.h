#pragma once

#include <freertos/FreeRTOS.h>
#include <driver/i2s.h>

// network config
//#define WIFI_SSID "C++" // reomved hard coding part
//#define WIFI_PASSWORD "21472147"
#define MDNS_DOMAIN "microphone"

// save to SPIFFS instead of SD Card?
// #define USE_SPIFFS 1

// sample rate for the system
#define SAMPLE_RATE 44100

// Analog microphone settings
#define ADC_MIC_CHANNEL ADC1_CHANNEL_0

// i2s config for using the internal ADC
extern i2s_config_t i2s_adc_config;

// i2s config for reading from of I2S
extern i2s_config_t i2s_mic_Config;

// i2s microphone pins - not used for analog input
extern i2s_pin_config_t i2s_mic_pins;