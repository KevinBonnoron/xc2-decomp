#include "ssd/ssd_result.h"
#include "ssd/ssd_sound_core.h"

namespace ssd {

Result clear_result() {
  SoundCore::instance_->unknown08 = static_cast<Result>(0);
  return static_cast<Result>(0);
}

Result set_result(Result result) {
  SoundCore::instance_->unknown08 = result;
  return result;
}

} // namespace ssd
