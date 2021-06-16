#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include "types.h"

uint32 const AUDIO_AMPLITUDE = 28000;
uint32 const AUDIO_SAMPLE_RATE = 44100;
real64 const AUDIO_A_HZ = 440.0f;

typedef struct AudioState {
  uint32 idx_last_sample;
  real64 pitch;
  real64 duration_remaining;
} AudioState;

void audio_update_state(AudioState *audio_state);
uint16 audio_make_sample(AudioState *audio_state);
void audio_fill_buffer(void *userdata, unsigned char *raw_buffer, int n_bytes);
void audio_play_note(AudioState *audio_state, real64 pitch, real64 duration);
void audio_destroy();
bool32 audio_init(SDL_AudioSpec target_spec);
