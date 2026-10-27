#include "ml/dev_file_job.h"

#include "ml/file_handle_th.h"

namespace ml {
class IWorkEvent;

void DevFileJob::clearJob(IWorkEvent *event) {
  if (event == nullptr) {
    wkSetEvent(static_cast<EVT>(0));
  } else if (unknown1a8 != nullptr && unknown1a8->unknown60 == event) {
    wkSetEvent(static_cast<EVT>(0));
  }
}

const char *DevFileJob::getFileName() const { return reinterpret_cast<const char *>(&unknown1a8->unknown98); }

f32 DevFileJob::getTransferRatio() const {
  f32 ratio = 0.0f;
  if (unknown1a8 != nullptr && unknown1a8->unknown18 != 0) {
    ratio = static_cast<f32>(unknown1a8->m_currentPtr) / static_cast<f32>(static_cast<u32>(unknown1a8->unknown18));
  }
  return ratio;
}

void DevFileJob::shutdownForce() { unknown1fa = true; }

} // namespace ml
