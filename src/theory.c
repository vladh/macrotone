/*
  macrotone
  Copyright (C) 2021 Vlad-Stefan Harbuz <vlad@vladh.net>
  GNU General Public License v3 (https://www.gnu.org/licenses). Absolutely no warranty.
*/

#include <stdlib.h>
#include "theory.h"


void get_pitches(Pitch pitches[], uint32 const pitches_capacity) {
  pitches[0] = 0.0f;
  pitches[1] = THEORY_A_HZ / 2.0f;
  pitches[5] = pitches[1] * THEORY_RATIO_FIFTH;
}
