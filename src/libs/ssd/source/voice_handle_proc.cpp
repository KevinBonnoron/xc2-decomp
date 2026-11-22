#include "nn/audio.h"
#include "ssd/ssd_allocator.h"
#include "ssd/ssd_behavior_impl.h" // IWYU pragma: keep
#include "ssd/ssd_debug.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_stream_controller.h"
#include "ssd/ssd_voice_handle.h"
#include "ssd/ssd_wave_source.h"
#include "types.h"

namespace ssd {
enum Result : long;

void VoiceHandle::UpdateAudioFrame(f32 deltaTime) {
  if (m_streamController != nullptr) {
    UpdateAudioStream(deltaTime);
  } else {
    UpdateAudioInternal(deltaTime);
  }
}

void VoiceHandle::UpdateAudioInternal(f32 deltaTime) {
  if (unknown44 == 6) {
    unknown44 = 8;
  }
  if (unknown44 == 8) {
    if (unknown31) {
      AcquireBuffer();
      EnableBuffer();
    }
  }
  unknown3d = true;
  UpdateAudioVoice(deltaTime);
  if (unknown44 == 4) {
    unknown30 = false;
    unknown44 = 3;
    ReleaseBuffer();
  }
}

void VoiceHandle::UpdateAudioVoice(f32 deltaTime) {
  if (unknown44 == 9 || unknown44 == 11 || unknown44 == 13) {
    if (!nn::audio::IsVoiceValid(&unknown90[0].unknown00)) {
      unknown33 = false;
      unknown34 = false;
      unknown44 = 4;
      unknown3e = false;
      unknown88 = 0;
      return;
    }
    SSD_ASSERT(unknown78 != nullptr, u"Assert : \"%s\" = nullptr, %s:%d", u"bufferProcess_", u"D:/ssd/ssd51/ssd/sources/voice_handle_proc.cpp", 0x1ba);
    (this->*unknown78)();
    u64 playedSample = nn::audio::GetVoicePlayedSampleCount(&unknown90[0].unknown00);
    if (m_waveSource->unknown34 == WaveSource::unknown001_3) {
      unknown680 = playedSample * 8 / 14;
    } else {
      unknown680 = m_waveSource->unknown40 * playedSample;
    }
    int waveBufferCount = nn::audio::GetWaveBufferCount(&unknown90[0].unknown00);
    unknown3e = waveBufferCount != 0;
    if (!unknown3d || (waveBufferCount != 0 && !unknown37)) {
      if (m_soundHandle != nullptr) {
        m_soundHandle->UpdateAudioFrame(deltaTime);
        UpdateOutputParam(deltaTime);
      }
    } else {
      unknown33 = false;
      unknown34 = false;
      unknown44 = 4;
      unknown3e = false;
      unknown88 = 0;
    }
  }
  if (unknown34 && unknown6d0.unknown00 == 0.0f) {
    unknown33 = true;
    unknown34 = false;
    if (unknown32) {
      for (int i = 0; i < unknown4c; i++) {
        nn::audio::SetVoicePlayState(&unknown90[i].unknown00, nn::audio::VoiceType::PlayState_Pause);
      }
      unknown44 = 10;
    }
  }
  if (unknown35) {
    unknown35 = false;
    unknown33 = false;
    for (int i = 0; i < unknown4c; i++) {
      nn::audio::SetVoicePlayState(&unknown90[i].unknown00, nn::audio::VoiceType::PlayState_Start);
    }
  }
  if (unknown36 && (unknown6d0.unknown00 == 0.0f || !nn::audio::IsVoiceValid(&unknown90[0].unknown00))) {
    unknown36 = false;
    DisableBuffer();
    unknown44 = 9;
  }
}

Result VoiceHandle::EnableBuffer() {
  UpdateOutputParam(0.0f);
  if (!unknown33) {
    for (int i = 0; i < unknown4c; i++) {
      if (nn::audio::IsVoiceValid(&unknown90[i].unknown00)) {
        nn::audio::SetVoicePlayState(&unknown90[i].unknown00, nn::audio::VoiceType::PlayState_Start);
      }
    }
  }
  return static_cast<Result>(0);
}

Result VoiceHandle::ReleaseBuffer() {
  if (nn::audio::IsVoiceValid(&unknown90[0].unknown00)) {
    for (int i = 0; i < unknown4c; i++) {
      if (nn::audio::IsVoiceValid(&unknown90[i].unknown00)) {
        nn::audio::ReleaseVoiceSlot(&m_systemCore->unknown168, &unknown90[i].unknown00);
        SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
        core->m_hWAllocVoiceCount -= unknown90[i].unknownb4;
        unknown90[i].unknownb4 = 0;
      }
    }
  }
  return static_cast<Result>(0);
}

Result VoiceHandle::SetPlayPositionImpl() {
  StreamController *stream = m_streamController;
  u64 position;
  if (stream == nullptr) {
    position = static_cast<u32>(unknown6a0.unknown00);
  } else {
    WaveSource *source = &stream->m_waveSource;
    if (unknown669 == 3) {
      position = source->TimeToSample(unknown6a0.unknown01) * source->unknown40;
    } else if (unknown669 == 2) {
      position = source->SampleToPosition(static_cast<u32>(unknown6a0.unknown00));
    } else {
      position = static_cast<u32>(unknown6a0.unknown00);
    }
  }
  unknown44 = 6;
  unknown88 = 0;
  unknown669 = 0;
  unknown668 = false;
  unknown688 = position;
  unknown690 = position;
  if (m_streamController != nullptr) {
    m_streamController->SetReadPosition(position);
  }
  return static_cast<Result>(1);
}

Result VoiceHandle::DisableBuffer() {
  if (nn::audio::IsVoiceValid(&unknown90[0].unknown00)) {
    SetHWVoiceState(nn::audio::VoiceType::PlayState_Stop);
    unknown37 = true;
  }
  unknown668 = false;
  return static_cast<Result>(0);
}

void VoiceHandle::DeleteStream() {
  if (m_streamController != nullptr) {
    m_streamController->QuitStream();
    StreamController *stream = m_streamController;
    SoundMemory::allocator_->unknown001(stream);
    unknown44 = 1;
    m_streamController = nullptr;
  }
}

void VoiceHandle::StreamingBufferProcess() {
  for (int i = 0; i < unknown4c; i++) {
    nn::audio::WaveBuffer *buffer = nn::audio::GetReleasedWaveBuffer(&unknown90[i].unknown00);
    if (i == 0 && buffer != nullptr) {
      unknown690 += buffer->bufferSize;
      unknown680 = 0;
      unknown8c++;
      unknown88--;
    }
  }
  if (unknown8c != 0) {
    AddStreamingBuffer();
  }
  unknown40 |= unknown88 == 0;
}

void VoiceHandle::SetHWVoiceState(nn::audio::VoiceType::PlayState state) {
  for (int i = 0; i < unknown4c; i++) {
    if (nn::audio::IsVoiceValid(&unknown90[i].unknown00)) {
      // Original game bug: the requested state is ignored and every voice is stopped.
      nn::audio::SetVoicePlayState(&unknown90[i].unknown00, nn::audio::VoiceType::PlayState_Stop);
    }
  }
}

void VoiceHandle::NullBufferProcess() {}

void VoiceHandle::OneShotBufferProcess() {
  if (nn::audio::GetReleasedWaveBuffer(&unknown90[0].unknown00) != nullptr) {
    unknown88--;
  }
}

void VoiceHandle::LooppingBufferProcess() {}

void VoiceHandle::AddLooppingBuffer() { unknown88++; }

} // namespace ssd
