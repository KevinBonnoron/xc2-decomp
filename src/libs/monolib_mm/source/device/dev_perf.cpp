#include "ml/dev_perf.h"

namespace ml {

bool DevPerf::isInitialized() {
  DevPerf *perf = get();
  if (perf == nullptr || perf->wkIsWaitException()) {
    return false;
  }

  return perf->wkIsActive();
}

bool DevPerf::wkStandbyLogin() { return WorkObj::wkStandbyLogin(); }

bool DevPerf::wkStandbyLogout() { return WorkObj::wkStandbyLogout(); }

} // namespace ml
