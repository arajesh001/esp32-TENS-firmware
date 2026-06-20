#pragma once
#include <Arduino.h>
#include "WaveformGenerator.h"
#include "safety.h"

class TENSController {
public:
    TENSController();

    void startSession(uint8_t mode);
    void stopSession();
    void update();

    bool isRunning() const { return _running; }
    uint8_t getMode() const { return _mode; }

private:
    WaveformGenerator* _generator;
    uint32_t _session_start_ms;
    uint8_t _mode;
    bool _running;
};