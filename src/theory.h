/*
  macrotone
  Copyright (C) 2021 Vlad-Stefan Harbuz <vlad@vladh.net>
  GNU General Public License v3 (https://www.gnu.org/licenses). Absolutely no warranty.
*/

#pragma once

#include <stdlib.h>
#include "types.h"

typedef real64 Pitch;
typedef real64 Seconds;

real64 const THEORY_A_HZ = 440.0f;
real64 const THEORY_RATIO_FIFTH = 3.0f / 2.0f;

/*!
  Fills `pitches` with some pitches.
  NOTE: `pitches` starts at index 1, `pitches[0]` should be discarded.
*/
void get_pitches(Pitch pitches[], uint32 const pitches_capacity);
