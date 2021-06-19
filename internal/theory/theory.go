package theory

import (
  "math"
)


func MakePythagoreanScale(basePitchHz float64) []float64 {
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
