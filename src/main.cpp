#include <Arduino.h>
#include "heltec.h"
#include <BleKeyboard.h>
#include "Images.h"
#include "Definitions.h"

BleKeyboard bleKeyboard(BLE_NAME, BLE_AUTHOR, 100);

int app_index = 0;
unsigned long scr_timeout = 0;
int previousButton = -1;
bool previousButtonIsLong = false;

void displayProfil(bool splash=false) {
    Heltec.display->wakeup();
    Heltec.display->clear();
    Heltec.display->setFont(ArialMT_Plain_16);
    if (splash) {
        Heltec.display->drawXbm(0, 0, 128, 64, SPLASH);
        Heltec.display->display();
        delay(SPLASH_TIMEOUT_MS);
        Heltec.display->clear();
    }
    Heltec.display->drawString(120, 0, "Mode:");
    Heltec.display->drawXbm(0, 0, 128, 64, apps[app_index].logo);
    Heltec.display->display();
    scr_timeout = millis() + SCREEN_TIMEOUT_MS;
}

void setup() {
    Heltec.begin(true, false, false);
    Heltec.display->init();
    Heltec.display->screenRotate(ANGLE_180_DEGREE);
    Heltec.display->setTextAlignment(TEXT_ALIGN_RIGHT);
    displayProfil(true);
    bleKeyboard.begin();
    pinMode(LED, OUTPUT);
    pinMode(PIN_A, INPUT_PULLUP);
    pinMode(PIN_B, INPUT_PULLUP);
    pinMode(PIN_C, INPUT_PULLUP);
    pinMode(PIN_D, INPUT_PULLUP);
    pinMode(PIN_CENTER, INPUT_PULLUP);
    pinMode(PIN_BTN_A, INPUT_PULLUP);
    pinMode(PIN_BTN_B, INPUT_PULLUP);
}

void displayKey(String payload) {
    Heltec.display->wakeup();
    Heltec.display->clear();
    Heltec.display->drawXbm(0, 0, 128, 64, apps[app_index].logo);
    Heltec.display->drawString(120, 40, payload);
    Heltec.display->display();
    scr_timeout = millis() + SCREEN_TIMEOUT_MS;
}

bool checkLongPress(int pin) {
    if (digitalRead(pin) == 0 && previousButton == pin && previousButtonIsLong)
        return true;
    unsigned long timeout = millis() + LONG_KEYPRESS_THRESHOLD_MS;
    int currentState = digitalRead(pin);
    while (millis() < timeout) {
        if (digitalRead(pin) != currentState)
            return false;
        delay(10);
    }
    previousButton = pin;
    previousButtonIsLong = true;
    return true;
}

void sendKey(int pin, int id) {
    digitalWrite(LED, HIGH);
    bool isLongPress = checkLongPress(pin);
    displayKey(isLongPress ? apps[app_index].keyLongName[id] : apps[app_index].keyShortName[id]);
    if (apps[app_index].name == "Spotify") {
        bleKeyboard.write(keymap_media[id]);
    }
    else {
        uint8_t key = apps[app_index].keyShortMap[id];
        if (isLongPress && apps[app_index].keyLongMap[id] != 0)
            key = apps[app_index].keyLongMap[id];
        bleKeyboard.write(key);
    }
    delay(isLongPress ? LONG_KEYPRESS_DELAY_MS : SHORT_KEYPRESS_DELAY_MS);
    bleKeyboard.releaseAll();
    digitalWrite(LED, LOW);
}

void readJoystick() {
    if (previousButtonIsLong && digitalRead(previousButton) == 1) {
        previousButtonIsLong = false;
        previousButton = -1;
    }
    if (digitalRead(PIN_A) == 1 && digitalRead(PIN_B) == 1 &&
                digitalRead(PIN_C) == 1 && digitalRead(PIN_D) == 1 && digitalRead(PIN_CENTER) == 0)
        return sendKey(PIN_CENTER, 4);
    if (digitalRead(PIN_A) == 0)
        return sendKey(PIN_A, 0);
    if (digitalRead(PIN_B) == 0)
        return sendKey(PIN_B, 1);
    if (digitalRead(PIN_C) == 0)
        return sendKey(PIN_C, 2);
    if (digitalRead(PIN_D) == 0)
        return sendKey(PIN_D, 3);
}

void readButton() {
    if (digitalRead(PIN_BTN_B) == 0) {
        app_index++;
        if (app_index >= APP_UNITS)
            app_index = 0;
        displayProfil();
        delay(500);
    }
}

void loop()
{
    if (bleKeyboard.isConnected()) {
        readJoystick();
        readButton();
    }
    if (millis() > scr_timeout && scr_timeout != 0) {
        scr_timeout = 0;
        Heltec.display->clear();
        Heltec.display->sleep();
    }
    delay(20);
}