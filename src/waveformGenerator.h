#pragma once
#include <Arduino.h>
#include "config.h"
#include "safety.h"

class WaveformGenerator {
public:
    explicit WaveformGenerator(uint8_t mode);
    WaveformGenerator(float frequency_hz, uint32_t pulse_width_us,
                      float amplitude_pct, bool biphasic, bool enabled);

    void run();
    void enable();
    void disable();

    void setFrequencyHz(float hz);
    void setPulseWidthUs(uint32_t us);
    void setAmplitudePct(float pct);
    void setBiphasic(bool biphasic);

    float getFrequencyHz() const { return _frequency_hz; }
    uint32_t getPulseWidthUs() const { return _pulse_width_us; }
    float getAmplitudePct() const { return _amplitude_pct; }
    bool isBiphasic() const {return _biphasic; }
    bool isEnabled() const {return _enabled;}

private:
    float _frequency_hz;
    uint32_t _pulse_width_us;
    float _amplitude_pct;
    bool _biphasic;
    bool _enabled;

    void _outputWaveform();
    void _setPolarity(bool positive);
};