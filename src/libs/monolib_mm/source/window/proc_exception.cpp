#include "ml/proc_exception.h"

namespace ml {

void ProcException::setInfo(EXCEPTION_PRIO prio) { unknown228 = prio; }

void ProcException::setInfo(u32 wid, const wchar_t *message) {
  unknown1f8 = wid;
  unknown200 = message;
}

bool ProcException::isCheckOK() const { return unknown20c == 0.8f; }

void ProcException::forceShutdown() {
  unknown224 = true;
  wkSetEvent(static_cast<EVT>(0));
}

void ProcException::renderWide(const wchar_t *message) {}

void ProcException::fatal(const wchar_t *message) {}

void ProcException::setMessage(const wchar_t *message) {
  if (get() != nullptr) {
    get()->unknown200 = message;
  }
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::ProcException>::~PtrSingleton();
