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

/*!
  Fills `pitches` with a 12-tone Pythagorean temperament.
  Returns the number of pitches put into `pitches`.
*/
uint32 make_pythagorean_scale(Pitch pitches[], uint32 const pitches_capacity, Pitch base_note);
