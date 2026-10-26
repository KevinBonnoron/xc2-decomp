#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
struct Col3;
} // namespace mm

namespace ml {

class CriticalSection;
class IThreadValue;
class IWorkInfomation;
class WorkCpuThread;

struct DEFHBM;
struct DEFIMM;

enum CPUID {
  CPUID_ANY,
  CPUID_CORE_0,
  CPUID_CORE_1,
  CPUID_CORE_2,
};

enum WKCPU_SYNC {
  WKCPU_SYNC_NONE,
  WKCPU_SYNC_WAIT,
};

enum DO_THREAD {};

namespace _mlwcpu {

extern bool s_bEnableLib;
extern bool s_bEShop;
extern bool s_bStallRender;
extern long s_aHearBeat[3];
extern s32 s_cpuStall;
extern bool s_bBackGround;

CriticalSection &getSwapLock();
CriticalSection &getHeartBeatLock();
CriticalSection &getListGrpLock();
CriticalSection &getJobBufLock();
CriticalSection &getListenerLock();
CriticalSection &getSuspendJobLock();
CriticalSection &getTermThreadLock();
CriticalSection &getAutoExecLock();
CriticalSection &getWaitingJobLock();

} // namespace _mlwcpu

class WorkCpu : public WorkObj, public mm::mtl::PtrSingleton<WorkCpu> {
public:
  static bool isInitialized();
  static void stallRender();
  static bool isGotoEShop();
  static void gotoEShop();
  static void setEnableSystem();
  static bool isEnableSystem();
  static u64 getCurrentThreadId();
  static u64 getMainThreadId();
  static bool checkTermThread();
  static void setProfiler(bool isProfiler);
  static f32 getAllCostSec();
  static void setRenderSubCpu(bool isRenderSubCpu);
  static mtl::ALLOC_HANDLE getMemWork();
  static mtl::ALLOC_HANDLE getMemStack();
  static CPUID getMainCPUID();
  static CPUID getRenderCPUID();
  static u32 getCpuNum();
  static CPUID getSubWorkCPUID();
  static CPUID getCurrentCPUID();
  static bool getStackInfo(u64 threadId, u64 &address, u64 &size);
  static f32 getJobCost(CPUID cpuId);
  static bool isSuspendThread(CPUID cpuId);
  static void beginRender();
  static WorkCpuThread *getCpuThread(CPUID cpuId);
  static void removeCpu(CPUID cpu, WorkCpuThread *thread);
  static void setThread(DO_THREAD thread);
  static DO_THREAD getThread();
  static u32 getEven();
  static void runThread(CPUID cpu, unsigned int (*function)(void *, void *), void *argument, void *userData, const mm::Col3 *color, bool isDebug, WKCPU_SYNC sync);
  static bool isShutdown();
  static void entrySwap(IThreadValue *value);
  static void removeSwap(IThreadValue *value);
  static u32 getFrameCountU32();
  static const unsigned long &getFrameCount();
  static bool getOdd();
  static bool isBackground();
  static void syncSubCpu();
  static void wakeup(int cpu);
  static void sync(int cpu, WKCPU_SYNC sync, CPUID cpuid);
  static void setHeartBeatCpu(CPUID cpu);
  static u32 getJobTrans();
  static const long &getBeginClock(bool isCurrent);
  static const long &getTailStartClock();
  static const long &getTailEndClock();
  static const long &getSyncClock();
  static u32 getCounter();
  static void gotoBackground();
  static void gotoForeground();
  static void backgroundProcess();
  static void backgroundProcess(CPUID cpu);
  static void addSystemInfoListener(IWorkInfomation *listener);
  static void removeSystemInfoListener(IWorkInfomation *listener);
  static u32 thForeground(void *argument, void *userData);
  static u32 thBackground(void *argument, void *userData);
  static void setAfterUpdateRender(bool isAfterUpdateRender);
  static bool isHomeMenuEnable();
  static int reqHomeMenuDisable();
  static int reqImm(bool isEnable);
  static void removeHomeMenuDisable(DEFHBM *&handle);
  static void removeImm(DEFIMM *&handle);
  static s32 getHeartBeatStall();
  static void clrHeartBeatStall();

  static bool s_bRenderSubCpu;

  u32 unknown1b0;               // Inferred role: flags; original member name unknown.
  mtl::ALLOC_HANDLE unknown1b4; // Inferred role: mem work; original member name unknown.
  mtl::ALLOC_HANDLE unknown1b8; // Inferred role: mem stack; original member name unknown.
  u32 unknown1bc;               // Inferred role: cpu num; original member name unknown.
  u8 _1c0[0x1738 - 0x1c0];
  DO_THREAD unknown1738;         // Inferred role: thread; original member name unknown.
  DO_THREAD unknown173c;         // Inferred role: next thread; original member name unknown.
  WorkCpuThread *unknown1740[3]; // Inferred role: cpu threads; original member name unknown.
  s32 unknown1758;               // Inferred role: render wakeup cpu; original member name unknown.
  u8 _175c[0x1764 - 0x175c];
  u32 unknown1764; // Inferred role: even; original member name unknown.
  u8 _1768[0x195c - 0x1768];
  u32 unknown195c; // Inferred role: counter; original member name unknown.
  u8 _1960[0x2020 - 0x1960];
  u64 unknown2020;    // Inferred role: main thread id; original member name unknown.
  u32 unknown2028[2]; // Inferred role: job trans; original member name unknown.
  u8 _2030[0x2034 - 0x2030];
  f32 unknown2034; // Inferred role: all cost sec; original member name unknown.
  u8 _2038[0x2048 - 0x2038];
  long unknown2048[5]; // Inferred role: begin clocks; original member name unknown.
  long unknown2070;    // Inferred role: tail start clock; original member name unknown.
  long unknown2078;    // Inferred role: tail end clock; original member name unknown.
  long unknown2080;    // Inferred role: sync clock; original member name unknown.
  u8 _2088[0x2090 - 0x2088];
  unsigned long unknown2090; // Inferred role: frame count; original member name unknown.
};

static_assert(offsetof(WorkCpu, unknown1b0) == 0x1b0, "");
static_assert(offsetof(WorkCpu, unknown1bc) == 0x1bc, "");
static_assert(offsetof(WorkCpu, unknown1738) == 0x1738, "");
static_assert(offsetof(WorkCpu, unknown1740) == 0x1740, "");
static_assert(offsetof(WorkCpu, unknown1758) == 0x1758, "");
static_assert(offsetof(WorkCpu, unknown1764) == 0x1764, "");
static_assert(offsetof(WorkCpu, unknown195c) == 0x195c, "");
static_assert(offsetof(WorkCpu, unknown2020) == 0x2020, "");
static_assert(offsetof(WorkCpu, unknown2034) == 0x2034, "");
static_assert(offsetof(WorkCpu, unknown2048) == 0x2048, "");
static_assert(offsetof(WorkCpu, unknown2080) == 0x2080, "");
static_assert(offsetof(WorkCpu, unknown2090) == 0x2090, "");

} // namespace ml
