#include "ssd/ssd_allocator.h"
#include "ssd/ssd_file_stream.h"
#include "ssd/ssd_memory_buffer.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_stream_buffer.h"
#include "ssd/ssd_stream_controller.h"
#include "ssd/ssd_wave_source.h"
#include "types.h"

namespace ssd {
enum Result : long;

StreamController::~StreamController() {}

s64 StreamController::ResetStream() {
  unknownf8 = 4;
  return 0;
}

u32 StreamController::SampleToPosition(int sample) { return 0; }

void StreamController::SetReadPosition(u64 position) {
  if (unknownf0) {
    unknownf7 = true;
    unknownf1 = false;
    unknown208 = position;
    unknownf6 = true;
  }
}

int StreamController::PositionToFrame(u64 position) {
  if (unknown1c0 != nullptr) {
    for (int i = 0; i < unknown248; i++) {
      if (unknown1c0[i] <= position && position < unknown1c0[i + 1]) {
        return i;
      }
    }
  }
  return 0;
}

void StreamController::ExecAdpcmDecode() {}

void StreamController::ClearReadBuffer() { m_streamBuffer.Clear(); }

int StreamController::OutData(u8 *buffer, u64 size, u64 *outSize, bool *isMark) {
  switch (m_waveSource.unknown1a) {
  case 4:
    if (unknown1f0 == 1) {
      unknown1c8 = buffer;
      unknown1d0 = size >> (m_waveSource.unknown35 == 1);
      unknown1d8 = 0;
      unknown1f0 = 2;
      *outSize = 0;
      return unknown1f0;
    }
    if (unknown1f0 == 4) {
      *outSize = unknown1d8;
      unknown1f0 = 1;
      return 4;
    }
    return unknown1f0;
  case 3:
    SoundCore::instance_->LockAudio();
    m_streamBuffer.OutData64(buffer, size, outSize, isMark);
    SoundCore::instance_->UnlockAudio();
    return 4;
  default:
    SoundCore::instance_->LockAudio();
    m_streamBuffer.OutData16(buffer, size, outSize, isMark);
    SoundCore::instance_->UnlockAudio();
    return 4;
  }
}

s64 StreamController::CloseStream() {
  if (unknownf5) {
    return 0;
  }
  unknownf1 = false;
  unknownee = true;
  unknownf8 = 3;
  return 1;
}

void StreamController::ExecCloseStream() {
  unknown148 = nullptr;
  unknown138 = nullptr;
  m_fileStream.Close();
  Allocator *allocator = SoundMemory::allocator_;
  if (unknown1b8 != nullptr) {
    Allocator::Block *block = allocator->GetMemoryBlock(unknown1b8);
    allocator->DeleteBufferImpl(block);
    unknown1b8 = nullptr;
  }
  if (unknown1c0 != nullptr) {
    Allocator::Block *block = allocator->GetMemoryBlock(unknown1c0);
    allocator->DeleteBufferImpl(block);
    unknown1c0 = nullptr;
  }
  unknown1f0 = 0;
  if (unknown1f8 != nullptr) {
    Allocator::Block *block = allocator->GetMemoryBlock(unknown1f8);
    allocator->DeleteBufferImpl(block);
    unknown1f8 = nullptr;
  }
  unknownf8 = 1;
  unknownec = false;
}

void StreamController::ExecSetPosition() {
  m_streamBuffer.Clear();
  if (unknown1f0 == 4) {
    unknown1f0 = 1;
  }
  unknownf1 = false;
  unknownf3 = false;
  unknownf4 = false;
  u64 dataSize = m_waveSource.unknown24;
  u64 readPosition;
  switch (m_waveSource.unknown34) {
  case WaveSource::unknown001_4: {
    int frame = 0;
    if (m_waveSource.unknown40 != 0) {
      frame = unknown208 / m_waveSource.unknown40;
    }
    int index = frame / m_waveSource.unknown5c;
    if (index >= m_waveSource.unknown68) {
      index = m_waveSource.unknown68;
    }
    unknown1ec = index;
    readPosition = unknown1c0[index];
    break;
  }
  case WaveSource::unknown001_3:
    readPosition = (unknown208 & ~0xfULL) * m_waveSource.unknown35;
    if (readPosition >= dataSize) {
      readPosition = dataSize;
    }
    break;
  default:
    readPosition = unknown208;
    if (readPosition >= dataSize) {
      readPosition = dataSize;
    }
    break;
  }
  if (unknown208 == dataSize) {
    unknownf1 = true;
    unknownf3 = true;
    unknownf4 = true;
  }
  unknown218 = readPosition;
  unknown208 = 0;
  unknownf6 = false;
  unknownf7 = false;
}

s64 StreamController::QuitStream() {
  unknownef = false;
  unknownf8 = 0;
  static_cast<SystemCore *>(SoundCore::instance_)->RemoveStreamController(this);
  m_memoryBuffer.Free();
  m_streamBuffer.Free();
  m_fileStream.Close();
  m_waveSource.Quit();
  return 0;
}

void StreamController::ExecReadStream(Result (StreamBuffer::*read)(const void *data, u64 size, bool mark)) {
  if (unknownf6) {
    return;
  }
  if (m_streamBuffer.m_dataSize >= 0x20000) {
    unknownf1 = true;
  }
  SoundCore::instance_->LockAudio();
  u64 freeSize = m_streamBuffer.m_bufferSize - m_streamBuffer.m_dataSize;
  SoundCore::instance_->UnlockAudio();
  if (freeSize >= 0x10000 && !unknownf6) {
    u64 remain = unknown230 - unknown218;
    if (remain == 0) {
      if (!unknownf2 && !unknownf3) {
        unknownf1 = true;
      }
      unknownf3 = true;
    } else {
      u64 size = freeSize;
      if (remain <= freeSize) {
        size = remain;
      }
      if (size > 0x20000) {
        size = 0x20000;
      }
      bool mark;
      if (unknown24c == 0) {
        mark = false;
      } else {
        mark = unknown228 == unknown218;
      }
      u64 offset = unknown210 + unknown218;
      u64 readSize;
      m_fileStream.GetData(offset, size, m_memoryBuffer.unknown08, &readSize);
      if (!unknownf6) {
        SoundCore::instance_->LockAudio();
        (m_streamBuffer.*read)(m_memoryBuffer.unknown08, size, mark);
        SoundCore::instance_->UnlockAudio();
        unknown218 += size;
        if (unknownf2 && unknown250 != 0 && unknown218 >= unknown230) {
          unknown24c++;
          unknown218 = unknown228;
          if (unknown250 > 0) {
            unknown250--;
          }
        }
      }
    }
  }
}

u64 StreamController::SizeToReadPosition(u64 size) {
  if (m_waveSource.unknown34 == WaveSource::unknown001_3) {
    return m_waveSource.unknown35 * (size & ~0xfULL);
  }
  if (m_waveSource.unknown34 == WaveSource::unknown001_4) {
    int frame = 0;
    if (m_waveSource.unknown40 != 0) {
      frame = size / m_waveSource.unknown40;
    }
    int index = frame / m_waveSource.unknown5c;
    unknown1ec = index;
    size = unknown1c0[index];
  }
  return size;
}

u32 StreamController::PlayTimeToPosition(f32 time) {
  int index = static_cast<int>(m_waveSource.unknown2c * time) / m_waveSource.unknown5c;
  if (index > m_waveSource.unknown68) {
    index = m_waveSource.unknown68;
  }
  return unknown1c0[index];
}

template List<StreamController>::Node::~Node();

} // namespace ssd
