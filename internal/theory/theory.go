/*
  macrotone
  Copyright (C) 2021 Vlad-Stefan Harbuz <vlad@vladh.net>
  GNU General Public License v3 (https://www.gnu.org/licenses). Absolutely no warranty.
*/

/*
This file contains various functions to construct musical tuning systems “from scratch”.
This includes deriving our Western pitch set from fifths using the Pythagorean method
and continues from there.

The methods in this file are based on the following book:
  “The Structure of Recognizable Diatonic Tunings” by Easley Blackwood
*/

package theory

import (
  "math"
)


/*
This is the function `int(i)` described in chapter 2 of Blackwood.
It returns the ratio itself for `int(i)` as two floats.
*/
func MakePythagoreanIntRatio(i float64) (float64, float64) {
  /*
  We calculate 3^i / 2^p
  i is the power of three, which we receive as an argument
  p is the power of two, which we calculate as follows
    * if i > 0, we choose p such that 2^p is the greatest value such that 2^p < 3^|i|
    * if i < 0, we choose p such that 2^p is the smallest value such that 2^p > 3^|i|
  */

  // For i = 0, the interval is simply the unison
  if i == 0 {
    return 1, 1
  }

  threeTermAbs := math.Pow(3, math.Abs(i))

  // Find our power of two p
  var p float64 = 0
  for {
    if math.Pow(2, p + 1) >= threeTermAbs {
      if i < 0 {
        p++
      }
      break
    }
    p++
  }

  twoTerm := math.Pow(2, p)

  // If i is negative, we flip the fraction so as to only return num/denom >= 1
  if i < 0 {
    return twoTerm, threeTermAbs
  } else {
    return threeTermAbs, twoTerm
  }
}


/*
This simply returns the actual numeric ratio for `int(i)`.
*/
func MakePythagoreanInt(i float64) float64 {
  num, denom := MakePythagoreanIntRatio(i)
  return num / denom
}


func MakePythagoreanFullScale(basePitchHz float64) []float64 {
  pitches := make([]float64, 13)

  // Unison
  pitches[0] = basePitchHz;
  // Minor second
  pitches[1] = pitches[0] * math.Pow(2.0, 8.0) / math.Pow(3.0, 5.0);
  // Major second
  pitches[2] = pitches[0] * math.Pow(3.0, 2.0) / math.Pow(2.0, 3.0);
  // Minor third
  pitches[3] = pitches[0] * math.Pow(2.0, 5.0) / math.Pow(3.0, 3.0);
  // Major third
  pitches[4] = pitches[0] * math.Pow(3.0, 4.0) / math.Pow(2.0, 6.0);
  // Perfect fourth
  pitches[5] = pitches[0] * math.Pow(2.0, 2.0) / math.Pow(3.0, 1.0);
  // Augmented fourth
  pitches[6] = pitches[0] * math.Pow(3.0, 6.0) / math.Pow(2.0, 9.0);
  // Diminished fifth
  pitches[7] = pitches[0] * math.Pow(2.0, 10.0) / math.Pow(3.0, 6.0);
  // Perfect fifth
  pitches[8] = pitches[0] * math.Pow(3.0, 1.0) / math.Pow(2.0, 1.0);
  // Minor sixth
  pitches[9] = pitches[0] * math.Pow(2.0, 7.0) / math.Pow(3.0, 4.0);
  // Major sixth
  pitches[10] = pitches[0] * math.Pow(3.0, 3.0) / math.Pow(2.0, 4.0);
  // Minor seventh
  pitches[11] = pitches[0] * math.Pow(2.0, 4.0) / math.Pow(3.0, 2.0);
  // Major seventh
  pitches[12] = pitches[0] * math.Pow(3.0, 5.0) / math.Pow(2.0, 7.0);

  return pitches
}


func MakePythagoreanDiatonicScale(basePitchHz float64) []float64 {
  pitches := make([]float64, 8)

  pitches[0] = basePitchHz * MakePythagoreanInt(0);
  pitches[1] = basePitchHz * MakePythagoreanInt(2);
  pitches[2] = basePitchHz * MakePythagoreanInt(4);
  pitches[3] = basePitchHz * MakePythagoreanInt(6);
  pitches[4] = basePitchHz * MakePythagoreanInt(1);
  pitches[5] = basePitchHz * MakePythagoreanInt(3);
  pitches[6] = basePitchHz * MakePythagoreanInt(5);
  pitches[7] = basePitchHz * MakePythagoreanInt(0) * 2.0;

  return pitches
}


func MakePythagoreanMajorScale(basePitchHz float64) []float64 {
  pitches := make([]float64, 8)

  pitches[0] = basePitchHz * MakePythagoreanInt(1);
  pitches[1] = basePitchHz * MakePythagoreanInt(3);
  pitches[2] = basePitchHz * MakePythagoreanInt(5);
  pitches[3] = basePitchHz * MakePythagoreanInt(0) * 2.0;
  pitches[4] = basePitchHz * MakePythagoreanInt(2) * 2.0;
  pitches[5] = basePitchHz * MakePythagoreanInt(4) * 2.0;
  pitches[6] = basePitchHz * MakePythagoreanInt(6) * 2.0;
  pitches[7] = basePitchHz * MakePythagoreanInt(1) * 2.0;

  return pitches
}
