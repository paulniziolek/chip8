#include "beep.hpp"
#include <cstring>
#include <cmath>

static void audio_callback(void* userdata, Uint8* stream, int len) {
    auto* b = reinterpret_cast<Beeper*>(userdata);

    // We asked for AUDIO_F32SYS below
    float* out = reinterpret_cast<float*>(stream);
    int frames = len / (int)sizeof(float);

    if (!b->enabled.load(std::memory_order_relaxed)) {
        std::memset(stream, 0, (size_t)len);
        return;
    }

    float sample_rate = (float)b->spec.freq;
    float phase = b->phase;
    float inc = b->freq / sample_rate;

    // simple square wave
    for (int i = 0; i < frames; i++) {
        phase += inc;
        if (phase >= 1.0f) phase -= 1.0f;
        float s = (phase < 0.5f) ? 1.0f : -1.0f;
        out[i] = s * b->volume;
    }

    b->phase = phase;
}

bool init_beeper(Beeper* b, float freq_hz) {
    b->freq = freq_hz;

    SDL_AudioSpec want{};
    want.freq = 48000;
    want.format = AUDIO_F32SYS;
    want.channels = 1;
    want.samples = 512;
    want.callback = audio_callback;
    want.userdata = b;

    b->dev = SDL_OpenAudioDevice(nullptr, 0, &want, &b->spec, 0);
    if (b->dev == 0) return false;

    // Start audio device. We'll output silence unless enabled=true.
    SDL_PauseAudioDevice(b->dev, 0);
    return true;
}

void set_beep(Beeper* b, bool on) {
    b->enabled.store(on, std::memory_order_relaxed);
}

void shutdown_beeper(Beeper* b) {
    if (b->dev != 0) {
        SDL_CloseAudioDevice(b->dev);
        b->dev = 0;
    }
}
