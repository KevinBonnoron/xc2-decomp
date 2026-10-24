#include "ml/dev_perf.h"

namespace ml {

DevPerf::DevPerf(const char *name, WorkObj *parent) : WorkObj(name, parent, 0), unknown1b0(nullptr) {}

bool DevPerf::isInitialized() {
  DevPerf *perf = get();
  if (perf == nullptr || perf->wkIsWaitException()) {
    return false;
  }

  return perf->wkIsActive();
}

DevPerf::~DevPerf() {
  if (unknown1b0 != nullptr) {
    delete unknown1b0;
    unknown1b0 = nullptr;
  }
}

bool DevPerf::wkStandbyLogin() { return WorkObj::wkStandbyLogin(); }

bool DevPerf::wkStandbyLogout() { return WorkObj::wkStandbyLogout(); }

void DevPerf::initialize() {}

void DevPerf::finalize() {}

void DevPerf::wkUpdate() {
  if (get() != nullptr) {
    get()->unknown1b0->update();
  }
}

DevPerfOperationMode DevPerf::getOperationMode() {
  if (get() != nullptr) {
    return get()->unknown1b0->getOperationMode();
  }
  return DEV_PERF_OPERATION_MODE_CONSOLE;
}

DevPerfMode DevPerf::getPerformanceMode() {
  if (get() != nullptr) {
    return get()->unknown1b0->getPerformanceMode();
  }
  return DEV_PERF_MODE_NORMAL;
}

int DevPerf::getFocusState() {
  if (get() != nullptr) {
    return get()->unknown1b0->getFocusState();
  }
  return 0;
}

void DevPerf::setPerfConfig(DevPerfMode mode, DevPerfConfig config) {
  if (get() != nullptr) {
    get()->unknown1b0->setPerfConfig(mode, config);
  }
}

DevPerfConfig DevPerf::getPerfConfig(DevPerfMode mode) {
  if (get() != nullptr) {
    return get()->unknown1b0->getPerfConfig(mode);
  }
  return DEV_PERF_CONFIG_HIGH;
}

} // namespace ml
