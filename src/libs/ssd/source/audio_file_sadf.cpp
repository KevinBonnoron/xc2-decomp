#include "ssd/ssd_audio_file.h"
#include "types.h"

namespace ssd {

Result AudioFileSadf::Open(IoStreamBase *stream) {
  m_ioStreamBase = stream;
  return static_cast<Result>(0);
}

Result AudioFileSadf::Close() {
  m_ioStreamBase = nullptr;
  return static_cast<Result>(0);
}

void AudioFileSadf::SetPositionBySample(u64 sample) {}

} // namespace ssd
