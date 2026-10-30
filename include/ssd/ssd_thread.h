#pragma once
#include <stddef.h>

#include "nn/os.h"
#include "ssd/ssd_result.h"
#include "types.h"

namespace ssd {

class Thread {
public:
  struct Param {
    Param();

    void *unknown00;  // Inferred role: function second argument; original member name unknown.
    int unknown08;    // Inferred role: priority; original member name unknown.
    int unknown0c;    // Inferred role: ideal core; original member name unknown.
    u64 unknown10;    // Inferred role: core mask; original member name unknown.
    void *unknown18;  // Inferred role: cleared by the constructor; original member name unknown.
    size_t unknown20; // Inferred role: stack size; original member name unknown.
    f32 unknown28;    // Inferred role: sleep time; original member name unknown.
  };

  ~Thread();
  static void ThreadEntryProc(void *argument);
  Result CloseThread();
  Result Wakeup();
  Result Sleep(f32 time);
  Result TimerSleep();

  bool unknown00; // Inferred role: created; original member name unknown.
  bool unknown01; // Inferred role: running; original member name unknown.
  bool unknown02; // Inferred role: close requested; original member name unknown.
  bool unknown03; // Inferred role: sleeping; original member name unknown.
  u8 _04[0x08 - 0x04];
  void *unknown08;                    // Inferred role: stack buffer; original member name unknown.
  size_t unknown10;                   // Inferred role: stack size; original member name unknown.
  f64 unknown18;                      // Inferred role: thread parameter; original member name unknown.
  nn::os::EventType unknown20;        // Inferred role: sleep event; original member name unknown.
  nn::os::ThreadType unknown48;       // Inferred role: thread; original member name unknown.
  void *unknown208;                   // Inferred role: function argument; original member name unknown.
  void (*unknown210)(void *, void *); // Inferred role: function; original member name unknown.
  void *unknown218;                   // Inferred role: function second argument; original member name unknown.
};

static_assert(offsetof(Thread, unknown08) == 0x8, "");
static_assert(offsetof(Thread, unknown18) == 0x18, "");
static_assert(offsetof(Thread, unknown20) == 0x20, "");
static_assert(offsetof(Thread, unknown48) == 0x48, "");
static_assert(offsetof(Thread, unknown208) == 0x208, "");
static_assert(sizeof(Thread) == 0x220, "");
static_assert(offsetof(Thread::Param, unknown10) == 0x10, "");
static_assert(offsetof(Thread::Param, unknown28) == 0x28, "");
static_assert(sizeof(Thread::Param) == 0x30, "");

} // namespace ssd
