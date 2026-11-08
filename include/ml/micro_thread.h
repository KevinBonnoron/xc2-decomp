#pragma once
#include <stddef.h>

#include "ml/critical_section.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "nn/os.h"
#include "types.h"

namespace ml {

class MLTH;
class MLTHG;

// The vtable of the game has null (pure virtual) slots for destroyThread, switchThreadMain, switchThread and
// setupThread, which MicroThreadNx overrides.
class MicroThread : public mm::mtl::PtrSingleton<MicroThread> {
public:
  // Name from the game symbol mm::mtl::FixedList<ml::MicroThread::MTHREAD*, 64>::erase.
  struct MTHREAD {
    u32 unknown00;                 // Inferred role: priority, set to 50; original member name unknown.
    void *unknown08;               // Inferred role: cleared at creation, never read here; original member name unknown.
    void *unknown10;               // Inferred role: platform fiber (MicroThreadNx::FiberParam); original member name unknown.
    void *unknown18;               // Inferred role: user data; original member name unknown.
    long unknown20;                // Inferred role: clock at the start of the sleep; original member name unknown.
    u32 unknown28;                 // Inferred role: sleep length in frames or milliseconds; original member name unknown.
    bool unknown2c;                // Inferred role: exit request; original member name unknown.
    bool unknown2d;                // Inferred role: sleep counted in frames; original member name unknown.
    nn::os::ThreadType *unknown30; // Inferred role: creating thread, used as thread id; original member name unknown.
    MLTH *unknown38;               // Inferred role: handle; original member name unknown.
  };

  // Inferred role: thread group; original type name unknown.
  struct unknown001 {
    MLTHG *unknown00;                             // Inferred role: group handle; original member name unknown.
    int unknown08;                                // Inferred role: thread count; original member name unknown.
    MTHREAD *unknown10[64];                       // Inferred role: threads by slot; original member name unknown.
    mm::mtl::FixedList<MTHREAD *, 64> unknown210; // Inferred role: scheduling order; original member name unknown.
    MTHREAD *unknown670;                          // Inferred role: current thread; original member name unknown.
  };

  MicroThread();
  virtual ~MicroThread();
  static MicroThread *create();
  static void destroy();
  void destroyAll();
  u64 createHandle(MLTHG *group, u32 index);
  MLTHG *createGroup();
  u64 createThread(MLTHG *group, nn::os::FiberFunction function, void *userData);
  void releaseGroup(MLTHG *group);
  void releaseThread(MLTH *handle);
  void sleep(unsigned int frame, bool isWait);
  void update(MLTHG *group);
  void tail();
  void *getCurrentUserData();
  static u64 getCurrentThreadID();
  void exit();

  virtual void destroyThread(MTHREAD *thread) = 0;
  virtual void switchThreadMain(MTHREAD *thread) = 0;
  virtual void switchThread(MTHREAD *current, MTHREAD *next) = 0;
  virtual void setupThread(MTHREAD *thread, nn::os::FiberFunction function) = 0;

  unknown001 *unknown08[16];                     // Inferred role: groups; original member name unknown.
  mm::mtl::FixedVector<MTHREAD *, 64> unknown88; // Inferred role: threads created since the last tail; original member name unknown.
  u32 unknown290;                                // Inferred role: group count; original member name unknown.
  u32 unknown294;                                // Inferred role: handle counter; original member name unknown.
  CriticalSection unknown298;                    // Inferred role: lock; original member name unknown.
  unknown001 *unknown2c0;                        // Inferred role: group being updated; original member name unknown.
};

class MicroThreadNx : public MicroThread {
public:
  // Name from the game symbol ml::MicroThreadNx::isExistThread(ml::MicroThreadNx::FiberParam*).
  struct FiberParam {
    FiberParam() : unknown58(nullptr), unknown60(0), unknown68(nullptr) {}

    nn::os::FiberType unknown00; // Inferred role: fiber; original member name unknown.
    void *unknown58;             // Inferred role: stack; original member name unknown.
    int unknown60;               // Inferred role: use count; original member name unknown.
    void *unknown68;             // Inferred role: cleared at construction, never read here; original member name unknown.
  };

  MicroThreadNx();
  virtual ~MicroThreadNx();
  bool isExistThread(FiberParam *param);
  virtual void destroyThread(MTHREAD *thread);
  virtual void switchThreadMain(MTHREAD *thread);
  virtual void switchThread(MTHREAD *current, MTHREAD *next);
  virtual void setupThread(MTHREAD *thread, nn::os::FiberFunction function);

  FiberParam unknown2c8[16]; // Inferred role: fibers; original member name unknown.
};

static_assert(sizeof(MicroThread) == 0x2c8, "");
static_assert(sizeof(MicroThreadNx) == 0x9c8, "");
static_assert(offsetof(MicroThread, unknown08) == 0x8, "");
static_assert(offsetof(MicroThread, unknown88) == 0x88, "");
static_assert(offsetof(MicroThread, unknown290) == 0x290, "");
static_assert(offsetof(MicroThread, unknown294) == 0x294, "");
static_assert(offsetof(MicroThread, unknown298) == 0x298, "");
static_assert(offsetof(MicroThread, unknown2c0) == 0x2c0, "");
static_assert(offsetof(MicroThreadNx, unknown2c8) == 0x2c8, "");
static_assert(sizeof(MicroThread::MTHREAD) == 0x40, "");
static_assert(offsetof(MicroThread::MTHREAD, unknown18) == 0x18, "");
static_assert(offsetof(MicroThread::MTHREAD, unknown20) == 0x20, "");
static_assert(offsetof(MicroThread::MTHREAD, unknown28) == 0x28, "");
static_assert(offsetof(MicroThread::MTHREAD, unknown2c) == 0x2c, "");
static_assert(offsetof(MicroThread::MTHREAD, unknown2d) == 0x2d, "");
static_assert(offsetof(MicroThread::MTHREAD, unknown30) == 0x30, "");
static_assert(offsetof(MicroThread::MTHREAD, unknown38) == 0x38, "");
static_assert(sizeof(MicroThread::unknown001) == 0x678, "");
static_assert(offsetof(MicroThread::unknown001, unknown08) == 0x8, "");
static_assert(offsetof(MicroThread::unknown001, unknown10) == 0x10, "");
static_assert(offsetof(MicroThread::unknown001, unknown210) == 0x210, "");
static_assert(offsetof(MicroThread::unknown001, unknown670) == 0x670, "");
static_assert(sizeof(MicroThreadNx::FiberParam) == 0x70, "");
static_assert(offsetof(MicroThreadNx::FiberParam, unknown58) == 0x58, "");
static_assert(offsetof(MicroThreadNx::FiberParam, unknown60) == 0x60, "");
static_assert(offsetof(MicroThreadNx::FiberParam, unknown68) == 0x68, "");

} // namespace ml
