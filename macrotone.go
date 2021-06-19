package main

import (
  "log"

  "github.com/veandco/go-sdl2/sdl"

  "net.vladh/macrotone/internal/audio"
  "net.vladh/macrotone/internal/theory"
)


func runMainLoop(audioState *audio.AudioState) {
  pitches := theory.MakePythagoreanScale(220.0)

  for _, pitch := range pitches {
    audio.PlayNoteBlocking(audioState, pitch, 1000.0)
  }

  sdl.Delay(1000.0)
}


func main() {
  var audioState audio.AudioState

  if err := audio.Init(&audioState); err != nil {
    log.Println(err)
    return
  }
  defer audio.Destroy()

  // Start playing audio
	sdl.PauseAudio(false)

  for {
    runMainLoop(&audioState)
  }
}
