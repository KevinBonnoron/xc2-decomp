#pragma once
#include <stddef.h>

#include <vector>

#include "nn/os.h"
#include "types.h"

class MediaClock;

class AudioOutRenderer {
public:
  struct audioData {
    int unknown00; // Inferred role: index; original member name unknown.
    s64 unknown08; // Inferred role: presentation time us; original member name unknown.
    u32 unknown10; // Inferred role: flags; original member name unknown.
  };

  void GenerateFixedSizeAudioFrame();
  void OnOutputAvailable(int index, s64 presentationTimeUs, u32 flags);
  u64 GetRendererSleepTimeMs();
  bool ExitThread();
  bool IsAudioOutStarted();
  s64 GetPlayedOutAudioDurationUs(s64 currentTimeUs);

  u8 _000[0x09 - 0x000];
  bool m_exitThread; // Named by the accessor ExitThread.
  u8 _0a[0x0b - 0x0a];
  bool m_audioOutStarted; // Named by the accessor IsAudioOutStarted.
  u8 _0c[0x10 - 0x0c];
  s32 unknown10; // Inferred role: sample rate; original member name unknown.
  u8 _14[0x430 - 0x14];
  std::vector<audioData> unknown430; // Inferred role: audio data list; original member name unknown.
  u8 _448[0x480 - 0x448];
  u64 m_rendererSleepTimeMs; // Named by the accessor GetRendererSleepTimeMs.
  u8 _488[0x490 - 0x488];
  nn::os::MutexType unknown490; // Inferred role: audio data mutex; original member name unknown.
  bool unknown4b0;              // Inferred role: flag tested by CMovie::isplaying; original member name unknown.
  u8 _4b1[0x4b8 - 0x4b1];
  MediaClock *unknown4b8; // Inferred role: media clock; original member name unknown.
  s64 unknown4c0;         // Inferred role: start time us; original member name unknown.
  s64 unknown4c8;         // Inferred role: played out start time us; original member name unknown.
  s64 unknown4d0;         // Inferred role: played out sample count; original member name unknown.
};

static_assert(offsetof(AudioOutRenderer, m_exitThread) == 0x09, "");
static_assert(offsetof(AudioOutRenderer, m_audioOutStarted) == 0x0b, "");
static_assert(offsetof(AudioOutRenderer, unknown10) == 0x10, "");
static_assert(offsetof(AudioOutRenderer, unknown430) == 0x430, "");
static_assert(offsetof(AudioOutRenderer, m_rendererSleepTimeMs) == 0x480, "");
static_assert(offsetof(AudioOutRenderer, unknown490) == 0x490, "");
static_assert(offsetof(AudioOutRenderer, unknown4b8) == 0x4b8, "");
static_assert(offsetof(AudioOutRenderer, unknown4b0) == 0x4b0, "");
static_assert(offsetof(AudioOutRenderer, unknown4c0) == 0x4c0, "");
static_assert(offsetof(AudioOutRenderer, unknown4c8) == 0x4c8, "");
static_assert(offsetof(AudioOutRenderer, unknown4d0) == 0x4d0, "");
