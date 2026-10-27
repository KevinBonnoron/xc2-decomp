#include "ssd/ssd_audio_file.h"
#include "types.h"

namespace ssd {

Result AudioFileSadf::Open(IoStreamBase *stream) {
  unknown08 = stream;
  return static_cast<Result>(0);
}

Result AudioFileSadf::Close() {
  unknown08 = nullptr;
  return static_cast<Result>(0);
}

void AudioFileSadf::SetPositionBySample(u64 sample) {}

} // namespace ssd
