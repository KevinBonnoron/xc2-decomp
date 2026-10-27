#include "ssd/ssd_file_stream.h"
#include "ssd/ssd_memory_buffer.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_stream_buffer.h"
#include "ssd/ssd_stream_controller.h"
#include "ssd/ssd_wave_source.h"
#include "types.h"

namespace ssd {

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

void StreamController::ClearReadBuffer() { unknown158.Clear(); }

s64 StreamController::CloseStream() {
  if (unknownf5) {
    return 0;
  }
  unknownf1 = false;
  unknownee = true;
  unknownf8 = 3;
  return 1;
}

s64 StreamController::QuitStream() {
  unknownef = false;
  unknownf8 = 0;
  static_cast<SystemCore *>(SoundCore::instance_)->RemoveStreamController(this);
  unknown258.Free();
  unknown158.Free();
  unknown100.Close();
  WaveSource::Quit();
  return 0;
}

u64 StreamController::SizeToReadPosition(u64 size) {
  if (unknown34 == unknown001_3) {
    return unknown35 * (size & ~0xfULL);
  }
  if (unknown34 == unknown001_4) {
    if (unknown40 != 0) {
      int frame = size / unknown40;
      int index = frame / unknown5c;
      unknown1ec = index;
      size = unknown1c0[index];
    }
  }
  return size;
}

u32 StreamController::PlayTimeToPosition(f32 time) {
  int index = static_cast<int>(unknown2c * time) / unknown5c;
  if (index > unknown68) {
    index = unknown68;
  }
  return unknown1c0[index];
}

template List<StreamController>::Node::~Node();

} // namespace ssd
