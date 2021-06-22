/*
  macrotone
  Copyright (C) 2021 Vlad-Stefan Harbuz <vlad@vladh.net>
  GNU General Public License v3 (https://www.gnu.org/licenses). Absolutely no warranty.
*/

package main

import (
  "log"

  "github.com/veandco/go-sdl2/sdl"

  "net.vladh/macrotone/internal/audio"
  "net.vladh/macrotone/internal/theory"
)


func runMainLoop(audioState *audio.AudioState) {
  log.Println("Tick")

  pitches := theory.MakePythagoreanMajorScale(440.0)

  for _, pitch := range pitches {
    audio.PlayNoteBlocking(audioState, pitch, 500.0)
  }

  sdl.Delay(1000.0)
}


func main() {
  log.SetFlags(0)
  log.Println("Hello")

  var audioState audio.AudioState

  if err := audio.Init(&audioState); err != nil {
    log.Println(err)
    return
  }
  defer audio.Destroy()

  // Start playing audio
  sdl.PauseAudio(false)

  log.Println("Pythagorean interval ratios:")
  var i float64 = 0
  for i = -6; i <= 6; i++ {
    num, denom := theory.MakePythagoreanIntRatio(i)
    log.Printf("%2.0f: %2.2f / %2.2f\n", i, num, denom)
  }

  for {
    runMainLoop(&audioState)
  }
}
