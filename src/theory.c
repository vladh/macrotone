/*
  macrotone
  Copyright (C) 2021 Vlad-Stefan Harbuz <vlad@vladh.net>
  GNU General Public License v3 (https://www.gnu.org/licenses). Absolutely no warranty.
*/

#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "theory.h"


uint32 make_pythagorean_scale(Pitch pitches[], uint32 const pitches_capacity, Pitch base_note) {
  assert(pitches_capacity >= 13);

  // Unison
  pitches[0] = base_note;
  // Minor second
  pitches[1] = pitches[0] * pow(2.0f, 8.0f) / pow(3.0f, 5.0f);
  // Major second
  pitches[2] = pitches[0] * pow(3.0f, 2.0f) / pow(2.0f, 3.0f);
  // Minor third
  pitches[3] = pitches[0] * pow(2.0f, 5.0f) / pow(3.0f, 3.0f);
  // Major third
  pitches[4] = pitches[0] * pow(3.0f, 4.0f) / pow(2.0f, 6.0f);
  // Perfect fourth
  pitches[5] = pitches[0] * pow(2.0f, 2.0f) / pow(3.0f, 1.0f);
  // Augmented fourth
  pitches[6] = pitches[0] * pow(3.0f, 6.0f) / pow(2.0f, 9.0f);
  // Diminished fifth
  pitches[7] = pitches[0] * pow(2.0f, 10.0f) / pow(3.0f, 6.0f);
  // Perfect fifth
  pitches[8] = pitches[0] * pow(3.0f, 1.0f) / pow(2.0f, 1.0f);
  // Minor sixth
  pitches[9] = pitches[0] * pow(2.0f, 7.0f) / pow(3.0f, 4.0f);
  // Major sixth
  pitches[10] = pitches[0] * pow(3.0f, 3.0f) / pow(2.0f, 4.0f);
  // Minor seventh
  pitches[11] = pitches[0] * pow(2.0f, 4.0f) / pow(3.0f, 2.0f);
  // Major seventh
  pitches[12] = pitches[0] * pow(3.0f, 5.0f) / pow(2.0f, 7.0f);

  return 13;
}
