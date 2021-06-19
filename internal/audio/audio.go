package audio

/*
typedef unsigned char uint8;
typedef unsigned int uint16;
void makeSine(void *userdata, uint8 *stream, int len);
*/
import "C"

import (
  "math"
  "unsafe"

  "github.com/veandco/go-sdl2/sdl"
)


type AudioState struct {
  idxLastSample uint32
  pitchHz float64
  msRemaining float64
}


// NOTE: We should only use this inside the SDL audio callback
var gAudioState *AudioState


const (
  AUDIO_SAMPLE_RATE = 44100
  AUDIO_AMPLITUDE = 32768
)


func updateAudioState(audioState *AudioState) {
  audioState.idxLastSample += 1
  audioState.msRemaining -= 1000.0 / (float64)(AUDIO_SAMPLE_RATE)
}


func makeSample(audioState *AudioState) uint16 {
  var sampleTime float64 = (float64)(audioState.idxLastSample) / AUDIO_SAMPLE_RATE
  var sample uint16 = uint16(
    AUDIO_AMPLITUDE * math.Sin(2.0 * math.Pi * audioState.pitchHz * sampleTime),
  )
  return sample
}


//export makeSine
func makeSine(userdata *C.void, rawBuffer *C.uint8, nCBytes C.int) {
  var nBytes int = int(nCBytes)

  buffer := (*[1 << 28]C.uint8)(unsafe.Pointer(rawBuffer))[:nBytes:nBytes]

  for idx := 0; idx < nBytes; idx += 2 {
    updateAudioState(gAudioState)

    if gAudioState.msRemaining <= 0.0 {
      buffer[idx] = 0
      buffer[idx + 1] = 0
      continue
    }

    sample := makeSample(gAudioState)
    buffer[idx] = (C.uint8)(sample & 0x00FF)
    buffer[idx + 1] = (C.uint8)((sample & 0xFF00) >> 8)
  }

  if gAudioState.msRemaining < 0.0 {
    gAudioState.msRemaining = 0.0
  }
}


func PlayNoteBlocking(audioState *AudioState, pitchHz float64, duration float64) {
  audioState.pitchHz = pitchHz
  audioState.msRemaining = duration
  sdl.Delay(uint32(duration))
}


func Destroy() {
  defer sdl.CloseAudio()
}


func Init(audioState *AudioState) error {
  gAudioState = audioState

  targetSpec := sdl.AudioSpec{
		Freq: AUDIO_SAMPLE_RATE,
		Format: sdl.AUDIO_S16SYS,
		Channels: 1,
		Samples: 2048,
		Callback: sdl.AudioCallback(C.makeSine),
	}

  var actualSpec sdl.AudioSpec;
  if err := sdl.OpenAudio(&targetSpec, &actualSpec); err != nil {
		return err
	}

  // NOTE: We would normally check that targetSpec and actualSpec are the same, but
  // gl-sdl2 adds some calculated fields which won't be equal, so whatever.

  return nil
}
