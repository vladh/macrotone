/*
  macrotone
  Copyright (C) 2021 Vlad-Stefan Harbuz <vlad@vladh.net>
  GNU General Public License v3 (https://www.gnu.org/licenses). Absolutely no warranty.
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include "types.h"
#include "theory.h"

uint32 const AUDIO_AMPLITUDE = 28000;
uint32 const AUDIO_SAMPLE_RATE = 44100;

typedef struct AudioState {
  uint32 idx_last_sample;
  Pitch pitch;
  Seconds duration_remaining;
} AudioState;

void audio_update_state(AudioState *audio_state);

uint16 audio_make_sample(AudioState *audio_state);

void audio_fill_buffer(void *userdata, unsigned char *raw_buffer, int n_bytes);

void audio_play_note_blocking(AudioState *audio_state, Pitch pitch, Seconds duration);

void audio_destroy();

bool32 audio_init(SDL_AudioSpec target_spec);
