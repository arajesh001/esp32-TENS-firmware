#include "WaveformGenerator.h"
#include "safety.h"

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
void WaveformGenerator::_setPolarity(bool positive) {
    digitalWrite(POLARITY_PIN, positive ? HIGH:LOW);
}

void WaveformGenerator::_outputWaveform() {
    // clamp params to safe ranges
    float freq = constrain(_frequency_hz, MIN_FREQ_HZ, MAX_FREQ_HZ);
    uint32_t pw = constrain(_pulse_width_us, MIN_PULSE_WIDTH_US, MAX_PULSE_WIDTH_US);
    float amp = constrain(_amplitude_pct, MIN_AMPLITUDE_PCT, MAX_AMPLITUDE_PCT);

    // deriving timings 
    uint32_t period_us = static_cast<uint32_t>(1.0f / freq * 1000000.0f);
    uint32_t interphase_us = INTERPHASE_GAP_US;
    uint32_t duty = static_cast<uint32_t>(amp * 1023);

    // deriving pos phase
    _setPolarity(true);
    ledcWrite(LEDC_CHANNEL, duty);
    delayMicroseconds(pw);
    ledcWrite(LEDC_CHANNEL, 0);

    // deriving neg phase if _biphasic
    if (_biphasic) {
        delayMicroseconds(interphase_us);
        _setPolarity(false);
        ledcWrite(LEDC_CHANNEL, duty);
        delayMicroseconds(pw);
        ledcWrite(LEDC_CHANNEL, 0);
        _setPolarity(true);
    }

    // wait the rest of the period
    uint32_t pulse_time = _biphasic ? (2 * pw + interphase_us) : pw;
    if (period_us > pulse_time) {
        delayMicroseconds(period_us - pulse_time);
    }
}