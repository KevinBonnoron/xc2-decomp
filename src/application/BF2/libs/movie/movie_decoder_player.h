#pragma once
#include <stddef.h>
#include <vector>

#include "libs/movie/movie_status.h"
#include "nn/os.h"
#include "types.h"

class AudioOutRenderer;
class VideoRenderer;

class MovieDecoderPlayer {
public:
  movie::Status AddBufferToAudioIndexList(int index);
  movie::Status RemoveBufferFromAudioIndexList(int *index);
  movie::Status GetAudioIndexListSize(int *size);
  movie::Status GetVideoIndexListSize(int *size);
  movie::Status AddBufferToVideoIndexList(int index);
  movie::Status RemoveBufferFromVideoIndexList(int *index);
  movie::Status SignalAudioVideoWorkerThreadExit();
  void StopAndDestroyAudioVideoWorkerThread();
  movie::Status SignalVideoInputReadThreadExit();
  movie::Status SignalAudioInputReadThreadExit();
  movie::Status SignalVideoInputBufferAvailable();
  movie::Status SignalAudioInputBufferAvailable();
  void StopAndDestroyVideoInputReaderThread();
  void StopAndDestroyAudioInputReaderThread();
  void StartVideoInputReaderThread();
  void StartAudioInputReaderThread();
  void StartAudioVideoWorkerThread();
  void ResetPlaybackComplete();
  movie::Status AudioFormatChangedEvent();

  u8 _000[0x18 - 0x000];
  nn::os::EventType unknown18; // Inferred role: worker thread exit event; signalled by SignalAudioVideoWorkerThreadExit; original member name unknown.
  u8 _40[0x430 - 0x40];
  AudioOutRenderer *unknown430; // Inferred role: audio renderer; original member name unknown.
  VideoRenderer *unknown438;    // Inferred role: video renderer; original member name unknown.
  u8 _440[0x478 - 0x440];
  void *unknown478; // Inferred role: stack of the video input reader thread, allocated by CreateThreadForVideoInputReader; original member name unknown.
  bool unknown480;  // Inferred role: video input reader thread stop requested; set before its message queue is signalled; original member name unknown.
  bool unknown481;  // Inferred role: video input reader thread exists; guards its shutdown; original member name unknown.
  u8 _482[0x488 - 0x482];
  nn::os::ThreadType unknown488; // Inferred role: video input reader thread, waited and destroyed by StopAndDestroyVideoInputReaderThread; original member name unknown.
  void *unknown648;              // Inferred role: stack of the audio input reader thread, allocated by CreateThreadForAudioInputReader; original member name unknown.
  bool unknown650;               // Inferred role: audio input reader thread stop requested; set before its message queue is signalled; original member name unknown.
  bool unknown651;               // Inferred role: audio input reader thread exists; guards its shutdown; original member name unknown.
  u8 _652[0x658 - 0x652];
  nn::os::ThreadType unknown658; // Inferred role: audio input reader thread, waited and destroyed by StopAndDestroyAudioInputReaderThread; original member name unknown.
  u8 _818[0x820 - 0x818];
  bool unknown820; // Inferred role: worker thread stop requested; set before the worker event is signalled; original member name unknown.
  bool unknown821; // Inferred role: worker thread exists; guards the worker thread shutdown; original member name unknown.
  u8 _822[0x828 - 0x822];
  nn::os::ThreadType unknown828; // Inferred role: worker thread, waited and destroyed by StopAndDestroyAudioVideoWorkerThread; original member name unknown.
  std::vector<int> unknown9e8;   // Inferred role: audio index list; original member name unknown.
  std::vector<int> unknowna00;   // Inferred role: video index list; original member name unknown.
  nn::os::MutexType unknowna18;  // Inferred role: audio index list mutex; original member name unknown.
  nn::os::MutexType unknowna38;  // Inferred role: video index list mutex; original member name unknown.
  u8 _a58[0xa68 - 0xa58];
  nn::os::MessageQueueType
      unknowna68; // Inferred role: video input reader message queue; messages sent by SignalVideoInputReadThreadExit and SignalVideoInputBufferAvailable; original member name unknown.
  nn::os::MessageQueueType
      unknownab8; // Inferred role: audio input reader message queue; messages sent by SignalAudioInputReadThreadExit and SignalAudioInputBufferAvailable; original member name unknown.
  u8 _b08[0xb30 - 0xb08];
  bool unknownb30; // Inferred role: playback finished; original member name unknown.
  u8 _b31[0xb48 - 0xb31];
  bool unknownb48; // Inferred role: cleared by ResetPlaybackComplete; original member name unknown.
  bool unknownb49; // Inferred role: cleared by ResetPlaybackComplete; original member name unknown.
};

static_assert(offsetof(MovieDecoderPlayer, unknown9e8) == 0x9e8, "");
static_assert(offsetof(MovieDecoderPlayer, unknowna00) == 0xa00, "");
static_assert(offsetof(MovieDecoderPlayer, unknowna18) == 0xa18, "");
static_assert(offsetof(MovieDecoderPlayer, unknown430) == 0x430, "");
static_assert(offsetof(MovieDecoderPlayer, unknown438) == 0x438, "");
static_assert(offsetof(MovieDecoderPlayer, unknownb30) == 0xb30, "");
static_assert(offsetof(MovieDecoderPlayer, unknowna38) == 0xa38, "");
static_assert(offsetof(MovieDecoderPlayer, unknown18) == 0x18, "");
static_assert(offsetof(MovieDecoderPlayer, unknown478) == 0x478, "");
static_assert(offsetof(MovieDecoderPlayer, unknown480) == 0x480, "");
static_assert(offsetof(MovieDecoderPlayer, unknown481) == 0x481, "");
static_assert(offsetof(MovieDecoderPlayer, unknown488) == 0x488, "");
static_assert(offsetof(MovieDecoderPlayer, unknown648) == 0x648, "");
static_assert(offsetof(MovieDecoderPlayer, unknown650) == 0x650, "");
static_assert(offsetof(MovieDecoderPlayer, unknown651) == 0x651, "");
static_assert(offsetof(MovieDecoderPlayer, unknown658) == 0x658, "");
static_assert(offsetof(MovieDecoderPlayer, unknown820) == 0x820, "");
static_assert(offsetof(MovieDecoderPlayer, unknown821) == 0x821, "");
static_assert(offsetof(MovieDecoderPlayer, unknown828) == 0x828, "");
static_assert(offsetof(MovieDecoderPlayer, unknowna68) == 0xa68, "");
static_assert(offsetof(MovieDecoderPlayer, unknownab8) == 0xab8, "");
