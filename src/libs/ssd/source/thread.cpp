#include "nn/os.h"
#include "nn/time_span.h"
#include "ssd/ssd_thread.h"
#include "types.h"

namespace ssd {
enum Result : long;

Thread::~Thread() {}

void Thread::ThreadEntryProc(void *argument) {
  Thread *thread = static_cast<Thread *>(argument);
  thread->unknown01 = true;
  thread->unknown210(thread->unknown208, thread->unknown218);
  thread->unknown01 = false;
}

Result Thread::Wakeup() {
  unknown03 = false;
  nn::os::SignalEvent(&unknown20);
  return static_cast<Result>(0);
}

Result Thread::Sleep(f32 time) {
  unknown03 = true;
  if (time == 0.0f) {
    nn::os::WaitEvent(&unknown20);
  } else {
    nn::os::TimedWaitEvent(&unknown20, nn::TimeSpan::FromNanoSeconds(static_cast<u64>(time * 1000000.0) * 1000));
  }
  return static_cast<Result>(0);
}

Result Thread::TimerSleep() {
  unknown03 = true;
  nn::os::WaitEvent(&unknown20);
  return static_cast<Result>(0);
}

} // namespace ssd
