
█▀▄▀█ █ █▄░█ █▀▄   █░█░█ ▄▀█ █░█ █▀▀
█░▀░█ █ █░▀█ █▄▀   ▀▄▀▄▀ █▀█ ▀▄▀ ██▄

# HARDWARE VERSION 1.0
includes:
  - firmware
  - Server script

## Firmware
  - This code is wrtten for MAX4466 module 
  - PIN configuration
          - OUT - GPIO36(UP PIN)
          - GND - GND
          - VCC - 3.3V
  - To run this code install platform.io on vscode
  - Before upload to esp 32
          - Set upload_port and monitor_port in platformio.ini
          - Defautly port is set to COM11 you can change according to your port number 
  - Upload code for esp 32
  - Microphone is connected to 5001 port

  ## Server script
  - Python version - 3.9.4
  - Install pyaudio, threding , wave and socket libraries 
  - And run python main.py in cmd (dont run in ide some ides block terminal)
  - You can choose one of option play or record , then select out put speaker 
