#pragma once
#include <stddef.h>

#include "nn/result.h"
#include "types.h"

// Audio renderer of the SDK. The type and function names come from the imports of the game (for example
// _ZN2nn5audio17OpenAudioRendererEPNS0_19AudioRendererHandleEPNS_2os11SystemEventERKNS0_22AudioRendererParameterEPvm).
// The AudioDeviceName and AudioRendererParameter member names, the sizes of the opaque types and the return types are
// the ones of open-ead nnheaders include/nn/audio.h (https://github.com/open-ead/nnheaders), except where noted.
// BufferMixerType and I3dl2ReverbType are not in nnheaders: their size comes from the layout of
// ssd::SystemCorePlatform::EffectBusInfo, the return types of their functions from their use in
// ssd::SystemCorePlatform. The members of the opaque types are unknown.

namespace nn {
class TimeSpan;

namespace os {
struct SystemEvent;
} // namespace os

namespace audio {

struct AudioDeviceName {
  char raw_name[0x100];
};

static_assert(sizeof(AudioDeviceName) == 0x100, "");

// nnheaders declares a 0x3c byte structure; the stack layout of ssd::SystemCorePlatform::InitAudioDevice
// (0x71009967a0) leaves 0x38 bytes to it in this SDK version, so only the members it writes are declared.
struct AudioRendererParameter {
  u32 sampleRate;
  u32 sampleCount;
  u32 mixBufferCount;
  u32 subMixCount;
  u32 voiceCount;
  u32 sinkCount;
  u32 effectCount;
  u32 performanceFrameCount;
  u8 _20[0x38 - 0x20];
};

static_assert(offsetof(AudioRendererParameter, performanceFrameCount) == 0x1c, "");
static_assert(sizeof(AudioRendererParameter) == 0x38, "");

struct alignas(8) AudioRendererConfig {
  u8 _00[0x58];
};

struct alignas(8) AudioRendererHandle {
  u8 _00[0x10];
};

struct alignas(8) MemoryPoolType {
  u8 _00[0x08];
};

struct alignas(8) FinalMixType {
  u8 _00[0x08];
};

struct alignas(8) DeviceSinkType {
  u8 _00[0x08];
};

struct alignas(8) DelayType {
  u8 _00[0x08];
};

struct alignas(8) I3dl2ReverbType {
  u8 _00[0x08];
};

struct alignas(8) BufferMixerType {
  u8 _00[0x08];
};

struct alignas(8) VoiceType {
  enum PlayState : u32 {
    PlayState_Start,
    PlayState_Stop,
    PlayState_Pause,
  };

  u8 _00[0x08];
};

struct WaveBuffer {
  void *buffer;
  size_t bufferSize;
  s32 startSampleOffset;
  s32 endSampleOffset;
  bool shouldLoop;
  bool isEndOfStream;
  void *context;
  size_t contextSize;
};

static_assert(sizeof(WaveBuffer) == 0x30, "");

int ListAudioDeviceName(AudioDeviceName *buffer, int bufferCount);

void InitializeAudioRendererParameter(AudioRendererParameter *parameter);
bool IsValidAudioRendererParameter(const AudioRendererParameter &parameter);
size_t GetAudioRendererWorkBufferSize(const AudioRendererParameter &parameter);
size_t GetAudioRendererConfigWorkBufferSize(const AudioRendererParameter &parameter);
Result InitializeAudioRendererConfig(AudioRendererConfig *config, const AudioRendererParameter &parameter, void *buffer, size_t bufferSize);
Result OpenAudioRenderer(AudioRendererHandle *handle, os::SystemEvent *event, const AudioRendererParameter &parameter, void *workBuffer, size_t workBufferSize);
void CloseAudioRenderer(AudioRendererHandle handle);
Result StartAudioRenderer(AudioRendererHandle handle);
Result StopAudioRenderer(AudioRendererHandle handle);
Result RequestUpdateAudioRenderer(AudioRendererHandle handle, const AudioRendererConfig *config);

bool AcquireMemoryPool(AudioRendererConfig *config, MemoryPoolType *pool, void *address, size_t size);
bool RequestAttachMemoryPool(MemoryPoolType *pool);

bool IsVoiceValid(const VoiceType *voice);
void ReleaseVoiceSlot(AudioRendererConfig *config, VoiceType *voice);
void SetVoicePlayState(VoiceType *voice, VoiceType::PlayState state);
WaveBuffer *GetReleasedWaveBuffer(VoiceType *voice);

bool AcquireFinalMix(AudioRendererConfig *config, FinalMixType *mix, int bufferCount);

Result AddDeviceSink(AudioRendererConfig *config, DeviceSinkType *sink, FinalMixType *mix, const s8 *input, int inputCount, const char *deviceName);

size_t GetRequiredBufferSizeForDelay(TimeSpan delayTimeMax, int sampleRate, int channelCount);
Result AddDelay(AudioRendererConfig *config, DelayType *delay, void *buffer, size_t bufferSize, FinalMixType *mix, TimeSpan delayTimeMax, int channelCount);
void *RemoveDelay(AudioRendererConfig *config, DelayType *delay, FinalMixType *mix);
bool IsDelayRemovable(const DelayType *delay);
void SetDelayInputOutput(DelayType *delay, const s8 *input, const s8 *output, int count);
void SetDelayTime(DelayType *delay, TimeSpan time);
void SetDelayChannelSpread(DelayType *delay, float channelSpread);
void SetDelayDryGain(DelayType *delay, float dryGain);
void SetDelayFeedbackGain(DelayType *delay, float feedbackGain);
void SetDelayInGain(DelayType *delay, float inGain);
void SetDelayLowPassAmount(DelayType *delay, float lowPassAmount);
void SetDelayEnabled(DelayType *delay, bool enable);

size_t GetRequiredBufferSizeForI3dl2Reverb(int sampleRate, int channelCount);
Result AddI3dl2Reverb(AudioRendererConfig *config, I3dl2ReverbType *reverb, void *buffer, size_t bufferSize, FinalMixType *mix, int channelCount);
void *RemoveI3dl2Reverb(AudioRendererConfig *config, I3dl2ReverbType *reverb, FinalMixType *mix);
bool IsI3dl2ReverbRemovable(const I3dl2ReverbType *reverb);
void SetI3dl2ReverbInputOutput(I3dl2ReverbType *reverb, const s8 *input, const s8 *output, int count);
void SetI3dl2ReverbRoomGain(I3dl2ReverbType *reverb, float gain);
void SetI3dl2ReverbRoomHfGain(I3dl2ReverbType *reverb, float gain);
void SetI3dl2ReverbLateReverbDecayTime(I3dl2ReverbType *reverb, TimeSpan time);
void SetI3dl2ReverbLateReverbHfDecayRatio(I3dl2ReverbType *reverb, float ratio);
void SetI3dl2ReverbReflectionsGain(I3dl2ReverbType *reverb, float gain);
void SetI3dl2ReverbReflectionDelayTime(I3dl2ReverbType *reverb, TimeSpan time);
void SetI3dl2ReverbReverbGain(I3dl2ReverbType *reverb, float gain);
void SetI3dl2ReverbLateReverbDelayTime(I3dl2ReverbType *reverb, TimeSpan time);
void SetI3dl2ReverbLateReverbDiffusion(I3dl2ReverbType *reverb, float diffusion);
void SetI3dl2ReverbLateReverbDensity(I3dl2ReverbType *reverb, float density);
void SetI3dl2ReverbHfReference(I3dl2ReverbType *reverb, float hfReference);
void SetI3dl2ReverbDryGain(I3dl2ReverbType *reverb, float gain);
void SetI3dl2ReverbEnabled(I3dl2ReverbType *reverb, bool enable);

void AddBufferMixer(AudioRendererConfig *config, BufferMixerType *mixer, FinalMixType *mix);
void RemoveBufferMixer(AudioRendererConfig *config, BufferMixerType *mixer, FinalMixType *mix);
bool IsBufferMixerRemovable(const BufferMixerType *mixer);
void SetBufferMixerInputOutput(BufferMixerType *mixer, const s8 *input, const s8 *output, int count);
void SetBufferMixerVolume(BufferMixerType *mixer, int index, float volume);
void SetBufferMixerEnabled(BufferMixerType *mixer, bool enable);

} // namespace audio
} // namespace nn
