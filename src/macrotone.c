/*
  macrotone
  Copyright (C) 2021 Vlad-Stefan Harbuz <vlad@vladh.net>
  GNU General Public License v3 (https://www.gnu.org/licenses). Absolutely no warranty.
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

#include "types.h"
#include "audio.h"
#include "theory.h"


void run_main_loop(bool32 *should_stop, AudioState *audio_state) {
  uint32 const pitches_capacity = 128;
  Pitch pitches[pitches_capacity];
  uint32 n_pitches = make_pythagorean_scale(pitches, pitches_capacity, THEORY_A_HZ / 2.0f);
  for (uint32 idx = 0; idx < n_pitches; idx++) {
    audio_play_note_blocking(audio_state, pitches[idx], 500.0f);
  }
  SDL_Delay(3000);
}


int main(int argc, char *argv[]) {
  bool32 should_stop = false;
  AudioState audio_state = {0};
  SDL_AudioSpec target_spec = {
    .freq = AUDIO_SAMPLE_RATE,
    .format = AUDIO_S16SYS,
    .channels = 1,
    .samples = 2048,
    .callback = audio_fill_buffer,
    .userdata = &audio_state,
  };
  if (!audio_init(target_spec)) {
    goto cleanup_end;
  }

  // Start playing audio.
  SDL_PauseAudio(0);

  while (!should_stop) {
    run_main_loop(&should_stop, &audio_state);
  }

  audio_destroy();
cleanup_end:
  return EXIT_SUCCESS;
}
