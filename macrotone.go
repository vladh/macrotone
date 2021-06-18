package main

/*
typedef unsigned char uint8;
typedef unsigned int uint16;
void makeSine(void *userdata, uint8 *stream, int len);
*/
import "C"

import (
  "log"
  "math"
  // "reflect"
  "unsafe"

  "github.com/veandco/go-sdl2/sdl"
)


type Pitch float64
type Seconds float64

type AudioState struct {
  idxLastSample uint32
  pitch Pitch
  durationRemaining Seconds
}


var gAudioState AudioState
const (
  AUDIO_SAMPLE_RATE = 44100
  AUDIO_AMPLITUDE = 28000
)


func updateAudioState() {
  gAudioState.idxLastSample += 1
}


func makeSample() uint16 {
  var sampleTime float64 = (float64)(gAudioState.idxLastSample) / AUDIO_SAMPLE_RATE
  var sample uint16 = uint16(
    AUDIO_AMPLITUDE * math.Sin(2.0 * math.Pi * 440.0 * sampleTime),
  )
  return sample
}


//export makeSine
func makeSine(userdata *C.void, rawBuffer *C.uint8, nCBytes C.int) {
  var nBytes int = int(nCBytes)

  buffer := (*[1 << 28]C.uint8)(unsafe.Pointer(rawBuffer))[:nBytes:nBytes]

  for idx := 0; idx < nBytes; idx += 2 {
    updateAudioState()
    sample := makeSample()
    buffer[idx] = (C.uint8)(sample & 0x00FF)
    buffer[idx + 1] = (C.uint8)((sample & 0xFF00) >> 8)
  }
}


func main() {
  targetSpec := sdl.AudioSpec{
		Freq: AUDIO_SAMPLE_RATE,
		Format: sdl.AUDIO_S16SYS,
		Channels: 1,
		Samples: 2048,
		Callback: sdl.AudioCallback(C.makeSine),
	}
  if err := sdl.OpenAudio(&targetSpec, nil); err != nil {
		log.Println(err)
		return
	}

	sdl.PauseAudio(false)
	sdl.Delay(5000)

	sdl.CloseAudio()
}
