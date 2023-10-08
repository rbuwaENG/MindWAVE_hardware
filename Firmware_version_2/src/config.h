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
