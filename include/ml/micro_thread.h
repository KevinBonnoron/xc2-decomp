#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class MLTHG;

class MicroThread : public mm::mtl::PtrSingleton<MicroThread> {
public:
  struct MLTH {
    u8 _00[0x18];
    void *unknown18; // Inferred role: user data; original member name unknown.
    u8 _20[0x2c - 0x20];
    bool unknown2c; // Inferred role: exit request; original member name unknown.
    u8 _2d[0x30 - 0x2d];
    u64 unknown30; // Inferred role: thread id; original member name unknown.
  };

  struct unknown001 {
    u8 _000[0x670];
    MLTH *unknown670; // Inferred role: current thread; original member name unknown.
  };

  void sleep(unsigned int frame, bool isWait);
  void exit();
  u64 createHandle(MLTHG *group, u32 index);
  void *getCurrentUserData();
  static u64 getCurrentThreadID();

  u8 _08[0x294 - 0x08];
  u32 unknown294; // Inferred role: handle counter; original member name unknown.
  u8 _298[0x2c0 - 0x298];
  unknown001 *unknown2c0; // Inferred role: thread context; original member name unknown.
};

static_assert(offsetof(MicroThread, unknown294) == 0x294, "");
static_assert(offsetof(MicroThread, unknown2c0) == 0x2c0, "");
static_assert(offsetof(MicroThread::MLTH, unknown18) == 0x18, "");
static_assert(offsetof(MicroThread::MLTH, unknown2c) == 0x2c, "");
static_assert(offsetof(MicroThread::MLTH, unknown30) == 0x30, "");
static_assert(offsetof(MicroThread::unknown001, unknown670) == 0x670, "");

} // namespace ml
