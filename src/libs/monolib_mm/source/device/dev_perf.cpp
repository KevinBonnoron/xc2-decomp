#include "ml/dev_perf.h"

namespace ml {

DevPerf::DevPerf(const char *name, WorkObj *parent) : WorkObj(name, parent, 0), m_impl(nullptr) {}

bool DevPerf::isInitialized() {
  DevPerf *perf = get();
  if (perf == nullptr || perf->wkIsWaitException()) {
    return false;
  }

  return perf->wkIsActive();
}

DevPerf::~DevPerf() {
  if (m_impl != nullptr) {
    delete m_impl;
    m_impl = nullptr;
  }
}

bool DevPerf::wkStandbyLogin() { return WorkObj::wkStandbyLogin(); }

bool DevPerf::wkStandbyLogout() { return WorkObj::wkStandbyLogout(); }

void DevPerf::initialize() {}

void DevPerf::finalize() {}

void DevPerf::wkUpdate() {
  if (get() != nullptr) {
    get()->m_impl->update();
  }
}

DevPerfOperationMode DevPerf::getOperationMode() {
  if (get() != nullptr) {
    return get()->m_impl->getOperationMode();
  }
  return DEV_PERF_OPERATION_MODE_CONSOLE;
}

DevPerfMode DevPerf::getPerformanceMode() {
  if (get() != nullptr) {
    return get()->m_impl->getPerformanceMode();
  }
  return DEV_PERF_MODE_NORMAL;
}

int DevPerf::getFocusState() {
  if (get() != nullptr) {
    return get()->m_impl->getFocusState();
  }
  return 0;
}

void DevPerf::setPerfConfig(DevPerfMode mode, DevPerfConfig config) {
  if (get() != nullptr) {
    get()->m_impl->setPerfConfig(mode, config);
  }
}

DevPerfConfig DevPerf::getPerfConfig(DevPerfMode mode) {
  if (get() != nullptr) {
    return get()->m_impl->getPerfConfig(mode);
  }
  return DEV_PERF_CONFIG_HIGH;
}

} // namespace ml
