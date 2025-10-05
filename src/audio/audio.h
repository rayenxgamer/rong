#pragma once

#include "utils/general.h"

#include "miniaudio/miniaudio.h"

#define REN_AUDIO_DEFAULT_SAMPLE_RATE 44100
#define REN_AUDIO_DEFAULT_STUDIO_SAMPLE_RATE 48000
#define REN_AUDIO_DEFAULT_CHANNEL_COUNT 2
#define REN_AUDIO_DEFAULT_AUDIO_FORMAT maFloat32
typedef ma_sound Sound;

static ma_engine engine;

enum audio_flags {
  REN_AUDIO_PLAY,
  REN_AUDIO_LOOP
};

void ren_audio_init(size_t count, const char* audio_init_buffer_in [count], Sound output_sounds[count]);
void ren_audio_init_one_sound_debug(const char* sound_path , Sound* output_sounds);

void ren_audio_play(Sound* sound, int flags);
void ren_audio_play_engine(const char* filename);
void ren_audio_play_volume(Sound* sound, int flags,float volume);

void ren_audio_terminate(size_t count, Sound output_sounds[count]);
