#include "nn/os.h"
#include "nn/time_span.h"
#include "ssd/ssd_event.h"
#include "types.h"

namespace ssd {

void Event::Init(const char16_t *name) { nn::os::InitializeEvent(&unknown00, false, nn::os::EventClearMode_AutoClear); }

void Event::Quit() { nn::os::FinalizeEvent(&unknown00); }

int Event::Wait() {
  nn::os::WaitEvent(&unknown00);
  return 0;
}

int Event::Wait(f32 timeout) {
  nn::os::TimedWaitEvent(&unknown00, nn::TimeSpan::FromNanoSeconds(static_cast<u64>(timeout * 1000000.0) * 1000));
  return 0;
}

void Event::Signal() { nn::os::SignalEvent(&unknown00); }

} // namespace ssd
