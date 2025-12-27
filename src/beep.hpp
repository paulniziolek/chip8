#pragma once
#include <SDL2/SDL.h>
#include <atomic>

struct Beeper {
    SDL_AudioDeviceID dev = 0;
    SDL_AudioSpec spec{};
    std::atomic<bool> enabled{false};

    // square wave state
    float phase = 0.0f;
    float freq = 440.0f;     // CHIP-8-ish beep; 440/480/1000 are all common
    float volume = 0.15f;    // 0..1, keep it low
};

bool init_beeper(Beeper* b, float freq_hz = 440.0f);
void set_beep(Beeper* b, bool on);
void shutdown_beeper(Beeper* b);
