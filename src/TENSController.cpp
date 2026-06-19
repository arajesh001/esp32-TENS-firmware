#include "TENSController.h"

TENSController::TENSController() {
    _generator = nullptr;
    _session_start_ms = 0;
    _mode = 0;
    _running = false;
}

void TENSController::stopSession() {
    _running = false;
    delete _generator;
    _generator = nullptr;
}

void TENSController::startSession(uint8_t mode) {
    if (_running) {stopSession();}

    _generator = new WaveformGenerator(mode);
    _session_start_ms = millis();
    _running = true;
    _mode = mode;
}

void TENSController::update() {
    if (MAX_SESSION_DURATION_MS < (millis() - _session_start_ms)) {
        stopSession();
    }
    else if (_running && _generator != nullptr) {
        _generator->run();
    }
}