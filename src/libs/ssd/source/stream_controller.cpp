#include "ssd/ssd_stream_controller.h"
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

template List<StreamController>::Node::~Node();

} // namespace ssd
