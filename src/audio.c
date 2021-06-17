/*
  macrotone
  Copyright (C) 2021 Vlad-Stefan Harbuz <vlad@vladh.net>
  GNU General Public License v3 (https://www.gnu.org/licenses). Absolutely no warranty.
*/

#include <math.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include "types.h"
#include "audio.h"


void audio_update_state(AudioState *audio_state) {
  audio_state->idx_last_sample++;
  audio_state->duration_remaining -= 1.0f / (real64)AUDIO_SAMPLE_RATE;
}


uint16 audio_make_sample(AudioState *audio_state) {
  real64 sample_time = (real64)(audio_state->idx_last_sample) / (real64)AUDIO_SAMPLE_RATE;
  uint16 sample = (uint16)(
    AUDIO_AMPLITUDE * sin(2.0f * M_PI * audio_state->pitch * sample_time)
  );
  return sample;
}


void audio_fill_buffer(void *userdata, unsigned char *raw_buffer, int n_bytes) {
  // We are using AUDIO_S16SYS, so we have two bytes per sample.
  // Therefore, we want to address two bytes at a time.
  AudioState *audio_state = (AudioState*)userdata;
  uint16 *buffer = (uint16*)raw_buffer;
  uint32 n_samples_required = n_bytes / 2;

  // If we don't have to play a note, just return zeroes.
  if (audio_state->duration_remaining == 0.0f) {
    memset(buffer, 0, n_samples_required * sizeof(uint16));
    return;
  }

  for (uint32 idx_sample = 0; idx_sample < n_samples_required; idx_sample++) {
    audio_update_state(audio_state);

    // If our note is over, just return zeroes until we're done.
    if (audio_state->duration_remaining <= 0.0f) {
      buffer[idx_sample] = 0;
      continue;
    }

    buffer[idx_sample] = audio_make_sample(audio_state);
  }

  if (audio_state->duration_remaining < 0.0f) {
    audio_state->duration_remaining = 0.0f;
  }
}


void audio_play_note_blocking(AudioState *audio_state, Pitch pitch, Seconds duration) {
  audio_state->pitch = pitch;
  audio_state->duration_remaining = duration;
  SDL_Delay(1000);
}


void audio_destroy() {
  SDL_CloseAudio();
}


bool32 audio_init(SDL_AudioSpec target_spec) {
  if (SDL_Init(SDL_INIT_AUDIO) != 0) {
    SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    return false;
  }

  SDL_AudioSpec actual_spec;
  if (SDL_OpenAudio(&target_spec, &actual_spec) != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to open audio: %s", SDL_GetError());
    return false;
  }

  if (target_spec.format != actual_spec.format) {
    SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to get the desired AudioSpec");
    audio_destroy();
    return false;
  }

  return true;
}
