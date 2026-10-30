#include <stddef.h>
#include <string.h>

#include "nn/audio.h"
#include "nn/diag.h"
#include "nn/mem.h"
#include "nn/os.h"
#include "nn/result.h"
#include "nn/time_span.h"
#include "ssd/ssd_result.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_text.h"
#include "types.h"

namespace ssd {

void SystemCorePlatform::InitPlatform(const InitParam &param) { unknown18 = static_cast<f64>(nn::os::GetSystemTickFrequency().GetInt64Value()); }

Result SystemCorePlatform::InitAudioDevice(const InitParam &param) {
  nn::audio::AudioRendererParameter parameter;
  nn::audio::InitializeAudioRendererParameter(&parameter);
  parameter.sampleRate = 48000;
  parameter.sampleCount = 240;
  parameter.voiceCount = 24;
  parameter.mixBufferCount = 10;
  parameter.subMixCount = 4;
  parameter.sinkCount = 1;
  parameter.effectCount = 3;
  parameter.performanceFrameCount = 0;
  NN_ABORT_UNLESS(nn::audio::IsValidAudioRendererParameter(parameter));
  if (param.unknown30 > 1024) {
    parameter.voiceCount = 1024;
  } else {
    parameter.voiceCount = param.unknown30;
  }
  NN_ABORT_UNLESS(nn::audio::IsValidAudioRendererParameter(parameter));
  unknown268 = parameter.sampleRate;
  unknown26c = parameter.sampleCount;

  unknown20 = {unknown001(0x100000), 0x100000};
  unknown30.Initialize(unknown20.unknown00, unknown20.unknown08);
  unknown78 = {unknown001(0x100000), 0x100000};
  unknown88.Initialize(unknown78.unknown00, unknown78.unknown08);
  unknownd8 = {unknown001(param.unknown44), param.unknown44};
  unknowne8.Initialize(unknownd8.unknown00, unknownd8.unknown08);

  for (int i = 0; i < 6; i++) {
    unknown1e8[i] = i;
  }
  for (int i = 0; i < 2; i++) {
    EffectBusInfo &info = unknown1f0[i];
    info.unknown00 = false;
    info.unknown01 = false;
    info.unknown03[0] = 6 + i * 2;
    info.unknown03[1] = 7 + i * 2;
    info.unknown02 = SoundEffecter::unknown001_255;
    info.unknown08 = 1.0f;
    info.unknown10 = nullptr;
    info.unknown18 = nullptr;
    info.unknown20 = nn::audio::BufferMixerType();
    info.unknown28 = nn::audio::DelayType();
  }

  size_t workBufferSize = nn::audio::GetAudioRendererWorkBufferSize(parameter);
  void *workBuffer = unknown30.Allocate(workBufferSize, 0x1000);
  NN_ABORT_UNLESS(nn::diag::detail::NotNullImpl(reinterpret_cast<u64>(workBuffer)));
  size_t configBufferSize = nn::audio::GetAudioRendererConfigWorkBufferSize(parameter);
  void *configBuffer = unknown30.Allocate(configBufferSize, 0x1000);
  NN_ABORT_UNLESS(nn::diag::detail::NotNullImpl(reinterpret_cast<u64>(configBuffer)));
  NN_ABORT_UNLESS(nn::audio::OpenAudioRenderer(&unknown1d8, &unknown138, parameter, workBuffer, workBufferSize).IsSuccess());
  nn::audio::InitializeAudioRendererConfig(&unknown168, parameter, configBuffer, configBufferSize);
  NN_ABORT_UNLESS(nn::audio::AcquireFinalMix(&unknown168, &unknown260, 10));
  NN_ABORT_UNLESS(nn::audio::AcquireMemoryPool(&unknown168, &unknown130, unknownd8.unknown00, unknownd8.unknown08));
  NN_ABORT_UNLESS(nn::audio::RequestAttachMemoryPool(&unknown130));
  NN_ABORT_UNLESS(nn::audio::AcquireMemoryPool(&unknown168, &unknownd0, unknown78.unknown00, unknown78.unknown08));
  NN_ABORT_UNLESS(nn::audio::RequestAttachMemoryPool(&unknownd0));
  nn::audio::DeviceSinkType sink;
  NN_ABORT_UNLESS(nn::audio::AddDeviceSink(&unknown168, &sink, &unknown260, unknown1e8, 6, "MainAudioOut").IsSuccess());
  NN_ABORT_UNLESS(nn::audio::RequestUpdateAudioRenderer(unknown1d8, &unknown168).IsSuccess());
  NN_ABORT_UNLESS(nn::audio::StartAudioRenderer(unknown1d8).IsSuccess());
  nn::audio::AudioDeviceName deviceNames[3];
  nn::audio::ListAudioDeviceName(deviceNames, 3);
  return set_result(static_cast<Result>(0));
}

Result SystemCorePlatform::QuitAudioDevice() {
  nn::audio::StopAudioRenderer(unknown1d8);
  nn::audio::CloseAudioRenderer(unknown1d8);
  nn::os::DestroySystemEvent(&unknown138.m_SystemEventType);
  unknowne8.Finalize();
  unknownd8.unknown004();
  unknown88.Finalize();
  unknown78.unknown004();
  unknown30.Finalize();
  unknown20.unknown004();
  return set_result(static_cast<Result>(0));
}

void SystemCorePlatform::UpdateDevice() { NN_ABORT_UNLESS(nn::audio::RequestUpdateAudioRenderer(unknown1d8, &unknown168).IsSuccess()); }

f64 SystemCorePlatform::GetSystemTime() { return nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetNanoSeconds() / 1000000000.0; }

void *SystemCorePlatform::GetPlatformDataImpl(const char *name) {
  if (strcmp(name, "AudioRendererConfig") == 0) {
    return &unknown168;
  }
  return nullptr;
}

void *SystemCorePlatform::AllocAudioDataBuffer(size_t size) { return unknowne8.Allocate(size, 64); }

void SystemCorePlatform::FreeAudioDataBuffer(void *buffer) { unknowne8.Free(buffer); }

Result SystemCorePlatform::InitEffect(u8 bus, SoundEffecter *effecter) {
  if (bus < 2) {
    if (effecter->unknown18 == SoundEffecter::unknown001_0) {
      return InitDelayEffect(bus, static_cast<SoundDelayEffecter *>(effecter));
    }
    if (effecter->unknown18 == SoundEffecter::unknown001_1) {
      return InitI3dl2ReverbEffect(bus, static_cast<SoundI3dl2ReverbEffecter *>(effecter));
    }
  }
  return static_cast<Result>(-1);
}

Result SystemCorePlatform::InitDelayEffect(u8 bus, SoundDelayEffecter *effecter) {
  EffectBusInfo &info = unknown1f0[bus];
  if (info.unknown10 != nullptr || info.unknown01 || effecter->unknown20 > effecter->unknown24) {
    return static_cast<Result>(-1);
  }
  info.unknown10 = effecter;
  info.unknown02 = SoundEffecter::unknown001_0;
  info.unknown08 = effecter->unknown1c;
  nn::TimeSpan delayTimeMax = nn::TimeSpan::FromMicroSeconds(effecter->unknown24 * 1000000.0);
  size_t size = nn::audio::GetRequiredBufferSizeForDelay(delayTimeMax, unknown268, 2);
  info.unknown18 = unknown88.Allocate(size);
  NN_ABORT_UNLESS(info.unknown18 != nullptr);
  NN_ABORT_UNLESS(nn::audio::AddDelay(&unknown168, &info.unknown28, info.unknown18, size, &unknown260, delayTimeMax, 2).IsSuccess());
  nn::audio::SetDelayInputOutput(&info.unknown28, info.unknown03, info.unknown03, 2);
  nn::audio::SetDelayTime(&info.unknown28, nn::TimeSpan::FromMicroSeconds(effecter->unknown20 * 1000000.0));
  nn::audio::SetDelayChannelSpread(&info.unknown28, effecter->unknown34);
  nn::audio::SetDelayDryGain(&info.unknown28, effecter->unknown30);
  nn::audio::SetDelayFeedbackGain(&info.unknown28, effecter->unknown2c);
  nn::audio::SetDelayInGain(&info.unknown28, effecter->unknown28);
  nn::audio::SetDelayLowPassAmount(&info.unknown28, effecter->unknown38);
  nn::audio::SetDelayEnabled(&info.unknown28, true);
  nn::audio::AddBufferMixer(&unknown168, &info.unknown20, &unknown260);
  nn::audio::SetBufferMixerVolume(&info.unknown20, 0, effecter->unknown1c);
  nn::audio::SetBufferMixerVolume(&info.unknown20, 1, effecter->unknown1c);
  nn::audio::SetBufferMixerInputOutput(&info.unknown20, info.unknown03, unknown1e8, 6);
  nn::audio::SetBufferMixerEnabled(&info.unknown20, true);
  info.unknown00 = true;
  info.unknown01 = false;
  effecter->unknown1a = bus;
  effecter->unknown19 = true;
  return static_cast<Result>(0);
}

Result SystemCorePlatform::InitI3dl2ReverbEffect(u8 bus, SoundI3dl2ReverbEffecter *effecter) {
  EffectBusInfo &info = unknown1f0[bus];
  if (info.unknown10 != nullptr || info.unknown01) {
    return static_cast<Result>(-1);
  }
  info.unknown10 = effecter;
  info.unknown02 = SoundEffecter::unknown001_1;
  info.unknown08 = effecter->unknown1c;
  size_t size = nn::audio::GetRequiredBufferSizeForI3dl2Reverb(unknown268, 2);
  info.unknown18 = unknown88.Allocate(size);
  NN_ABORT_UNLESS(info.unknown18 != nullptr);
  NN_ABORT_UNLESS(nn::audio::AddI3dl2Reverb(&unknown168, &info.unknown30, info.unknown18, size, &unknown260, 2).IsSuccess());
  nn::audio::SetI3dl2ReverbInputOutput(&info.unknown30, info.unknown03, info.unknown03, 2);
  f32 roomGain = effecter->unknown24;
  if (effecter->unknown20) {
    effecter->unknown20 = false;
  }
  nn::audio::SetI3dl2ReverbRoomGain(&info.unknown30, roomGain);
  nn::audio::SetI3dl2ReverbRoomHfGain(&info.unknown30, effecter->unknown28);
  nn::audio::SetI3dl2ReverbLateReverbDecayTime(&info.unknown30, nn::TimeSpan::FromMicroSeconds(effecter->unknown2c * 1000000.0));
  nn::audio::SetI3dl2ReverbLateReverbHfDecayRatio(&info.unknown30, effecter->unknown30);
  nn::audio::SetI3dl2ReverbReflectionsGain(&info.unknown30, effecter->unknown34);
  nn::audio::SetI3dl2ReverbReflectionDelayTime(&info.unknown30, nn::TimeSpan::FromMicroSeconds(effecter->unknown38 * 1000000.0));
  nn::audio::SetI3dl2ReverbReverbGain(&info.unknown30, effecter->unknown3c);
  nn::audio::SetI3dl2ReverbLateReverbDelayTime(&info.unknown30, nn::TimeSpan::FromMicroSeconds(effecter->unknown40 * 1000000.0));
  nn::audio::SetI3dl2ReverbLateReverbDiffusion(&info.unknown30, effecter->unknown44);
  nn::audio::SetI3dl2ReverbLateReverbDensity(&info.unknown30, effecter->unknown48);
  nn::audio::SetI3dl2ReverbHfReference(&info.unknown30, effecter->unknown4c);
  nn::audio::SetI3dl2ReverbDryGain(&info.unknown30, effecter->unknown50);
  nn::audio::SetI3dl2ReverbEnabled(&info.unknown30, true);
  nn::audio::AddBufferMixer(&unknown168, &info.unknown20, &unknown260);
  nn::audio::SetBufferMixerVolume(&info.unknown20, 0, info.unknown08);
  nn::audio::SetBufferMixerVolume(&info.unknown20, 1, info.unknown08);
  nn::audio::SetBufferMixerInputOutput(&info.unknown20, info.unknown03, unknown1e8, 6);
  nn::audio::SetBufferMixerEnabled(&info.unknown20, true);
  info.unknown00 = true;
  info.unknown01 = false;
  effecter->unknown1a = bus;
  effecter->unknown19 = true;
  return static_cast<Result>(0);
}

Result SystemCorePlatform::QuitEffect(SoundEffecter *effecter) {
  int bus = GetBusNumberFormEffecter(effecter);
  if (bus < 0 || unknown1f0[bus].unknown01) {
    return static_cast<Result>(-1);
  }
  Result result;
  if (effecter->unknown18 == SoundEffecter::unknown001_0) {
    result = QuitDelayEffect(bus);
  } else if (effecter->unknown18 == SoundEffecter::unknown001_1) {
    result = QuitI3dl2ReverbEffect(bus);
  } else {
    result = static_cast<Result>(-1);
  }
  effecter->unknown19 = false;
  return result;
}

int SystemCorePlatform::GetBusNumberFormEffecter(SoundEffecter *effecter) {
  if (unknown1f0[0].unknown10 == effecter) {
    return 0;
  }
  if (unknown1f0[1].unknown10 == effecter) {
    return 1;
  }
  return -1;
}

Result SystemCorePlatform::QuitDelayEffect(u8 bus) {
  EffectBusInfo &info = unknown1f0[bus];
  nn::audio::SetBufferMixerEnabled(&info.unknown20, false);
  nn::audio::SetDelayEnabled(&info.unknown28, false);
  info.unknown01 = true;
  info.unknown00 = false;
  info.unknown10 = nullptr;
  DeleteEffect(info);
  return static_cast<Result>(0);
}

Result SystemCorePlatform::QuitI3dl2ReverbEffect(u8 bus) {
  EffectBusInfo &info = unknown1f0[bus];
  nn::audio::SetBufferMixerEnabled(&info.unknown20, false);
  nn::audio::SetI3dl2ReverbEnabled(&info.unknown30, false);
  info.unknown01 = true;
  info.unknown00 = false;
  info.unknown10 = nullptr;
  DeleteEffect(info);
  return static_cast<Result>(0);
}

void SystemCorePlatform::DeleteEffect(EffectBusInfo &info) {
  if (!info.unknown01) {
    return;
  }
  if (info.unknown02 == SoundEffecter::unknown001_0) {
    if (!nn::audio::IsBufferMixerRemovable(&info.unknown20) || !nn::audio::IsDelayRemovable(&info.unknown28)) {
      return;
    }
    nn::audio::RemoveBufferMixer(&unknown168, &info.unknown20, &unknown260);
    nn::audio::RemoveDelay(&unknown168, &info.unknown28, &unknown260);
  } else if (info.unknown02 == SoundEffecter::unknown001_1) {
    if (!nn::audio::IsBufferMixerRemovable(&info.unknown20) || !nn::audio::IsI3dl2ReverbRemovable(&info.unknown30)) {
      return;
    }
    nn::audio::RemoveBufferMixer(&unknown168, &info.unknown20, &unknown260);
    nn::audio::RemoveI3dl2Reverb(&unknown168, &info.unknown30, &unknown260);
  } else {
    return;
  }
  unknown88.Free(info.unknown18);
  info.unknown18 = nullptr;
  info.unknown01 = false;
  info.unknown02 = SoundEffecter::unknown001_255;
}

void SystemCorePlatform::UpdateEffectVolume(SoundEffecter *effecter) {
  int bus = GetBusNumberFormEffecter(effecter);
  if (bus >= 0) {
    unknown1f0[bus].unknown08 = effecter->unknown1c;
  }
}

void SystemCorePlatform::UpdateEffectParam(SoundEffecter *effecter) {}

} // namespace ssd
