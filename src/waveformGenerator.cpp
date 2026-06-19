#include "waveform.h"

// Mode constructor
// BASED ON MODES 1-3 that the bio team provides
// VALUES ARE PLACEHOLDER RIGHT NOW
WaveformGenerator::WaveformGenerator(uint8_t mode)
{
    switch (mode)
    {
    case 1:
        _frequency_hz = 100.0f;
        _pulse_width_us = 100;
        _amplitude_pct = 0.5f;
        break;
    case 2:
        _frequency_hz = 4.0f;
        _pulse_width_us = 300;
        _amplitude_pct = 0.75f;
        break;
    case 3:
        _frequency_hz = 50.0f;
        _pulse_width_us = 200;
        _amplitude_pct = 0.5f;
        break;
    default:
        // unknown mode — apply minimum safe values (safety.h)
        _frequency_hz = MIN_FREQ_HZ;
        _pulse_width_us = MIN_PULSE_WIDTH_US;
        _amplitude_pct = MIN_AMPLITUDE_PCT;
        break;
    }
    _biphasic = true;
    _enabled  = true;
}

// MANUAL CONSTRUCTOR
WaveformGenerator::WaveformGenerator(float frequency_hz, uint32_t pulse_width_us,
                                     float amplitude_pct, bool biphasic, bool enabled)
    : _frequency_hz(frequency_hz),
      _pulse_width_us(pulse_width_us),
      _amplitude_pct(amplitude_pct),
      _biphasic(biphasic),
      _enabled(enabled)
{}

// run() called from void loop()
void WaveformGenerator::run()
{
    if (!_enabled) return;
    _outputWaveform();
}

// enable() / disable() 
void WaveformGenerator::enable() { _enabled = true;}
void WaveformGenerator::disable() { _enabled = false;}

// setters
void WaveformGenerator::setFrequencyHz(float hz) { _frequency_hz = hz;}
void WaveformGenerator::setPulseWidthUs(uint32_t us) { _pulse_width_us = us;}
void WaveformGenerator::setAmplitudePct(float pct) { _amplitude_pct = pct;}
void WaveformGenerator::setBiphasic(bool biphasic) { _biphasic = biphasic; }

// TODOs
void WaveformGenerator::_outputWaveform() {}
void WaveformGenerator::_setPolarity(bool positive) {}