#include <Arduino.h>
#include "TENSController.h"
#include "config.h"
#include "safety.h"

TENSController controller;

void setup() {
    Serial.begin(115200);

    ledcSetup(LEDC_CHANNEL, LEDC_CARRIER_HZ, LEDC_RESOLUTION);
    ledcAttachPin(OUTPUT_PIN, LEDC_CHANNEL);

    pinMode(POLARITY_PIN, OUTPUT);
    pinMode(ENABLE_PIN, OUTPUT);

    digitalWrite(POLARITY_PIN, HIGH);
    digitalWrite(ENABLE_PIN, LOW);
    digitalWrite(ENABLE_PIN, HIGH);

    // swap mode to 2, or 3 to test other modes
    controller.startSession(1);
}

void loop() {
    controller.update();
}