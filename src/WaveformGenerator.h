class WaveformParams
{
public:
    // Mode constructor
    // BASED ON MODES 1-3 that the bio team provides
    // VALUES ARE PLACEHOLDER RIGHT NOW
    explicit WaveformParams(uint8_t mode)
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
        }
        _biphasic = true;
        _enabled = true;
    }

    // Manual constructor
    WaveformParams(float frequency_hz, uint32_t pulse_width_us,
                   float amplitude_pct, bool biphasic, bool enabled)
    {
        _frequency_hz = frequency_hz;
        _pulse_width_us = pulse_width_us;
        _amplitude_pct = amplitude_pct;
        _biphasic = biphasic;
        _enabled = enabled;
    }

    float getFrequencyHz() const { return _frequency_hz; }
    uint32_t getPulseWidthUs() const { return _pulse_width_us; }
    float getAmplitudePct() const { return _amplitude_pct; }
    bool isBiphasic() const { return _biphasic; }
    bool isEnabled() const { return _enabled; }

private:
    float _frequency_hz;
    uint32_t _pulse_width_us;
    float _amplitude_pct;
    bool _biphasic;
    bool _enabled;


void outputWaveform(const WaveformParams& params);
void setPolarity(bool positive);

};