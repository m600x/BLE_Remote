# Bluetooth Low Energy remote controler for motorcycle

## Description
This repo contains code to run a BLE remote control for various mobile apps (mainly motorcycle navigation apps).

Has been tested on Android and iOS with the following software:
- OsmAnd+
- Scenic App
- Spotify (any music player in fact)

---

## Feature
- Support short and long press
- Support multiple profil with different keymapping (OsmAnd, Scenic, Spotify)
- OLED display because I like these smol screen for some reason

---

## Hardware BoM
The repo as it run with an Heltec LoRa ESP32 board.
- Heltec LoRa ESP32 board
- 2 waterproof button NO
- 1 RKJXT1F42001 (fingertip joystick 2 axis + center button + rotary encoder)
- A Voron

Note: As it, the joystick is **NOT** waterproof and sold as a PCB part not to be directly used. But with some imagination and a Mc Gyver vibe, you can work around it.

---

## Software requirement
- Visual Studio Code
- PlatformIO

---

## I want to thank my wonderful wife fo...
Idea spark from [BarButtons](https://jaxeadv.com/barbuttons/) by JaxeADV who kindly provided all required instructions, code and so forth to build something similar.

The issue is that I specifically wanted to use a mini joystick since on my motorcycle handlebar, it's fairly busy (2022 BMW S1000XR) so I had to search for parts and the code provided is not suited for it. Hence that derivated version.

Also use the following libraries:
- https://github.com/HelTecAutomation/Heltec_ESP32
- https://github.com/T-vK/ESP32-BLE-Keyboard