#pragma once
#include <stddef.h>

#include "ml/critical_section.h"
#include "ml/work_obj.h"
#include "mm_math/mm_col3.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {

class IThreadValue;
class IErrorCB;
class IWorkBackground;
class IWorkEvent;
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

struct TJOB {
  u32 (*unknown00)(void *, void *); // Inferred role: job function; original member name unknown.
  u32 unknown08;                    // Inferred role: priority; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  void *unknown10; // Inferred role: first argument; original member name unknown.
  void *unknown18; // Inferred role: second argument; original member name unknown.
  u32 unknown20;   // Inferred role: result; original member name unknown.
  s32 unknown24;   // Inferred role: group handle; original member name unknown.
  u32 unknown28;   // Inferred role: color; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  s32 unknown30;  // Inferred role: cpu id; original member name unknown.
  bool unknown34; // Inferred role: debug; original member name unknown.
  u8 _35[0x38 - 0x35];
  s32 unknown38;  // Inferred role: executed cpu id; original member name unknown.
  bool unknown3c; // Inferred role: background; original member name unknown.
  u8 _3d[0x40 - 0x3d];
};

static_assert(offsetof(TJOB, unknown10) == 0x10, "");
static_assert(offsetof(TJOB, unknown20) == 0x20, "");
static_assert(offsetof(TJOB, unknown24) == 0x24, "");
static_assert(offsetof(TJOB, unknown28) == 0x28, "");
static_assert(offsetof(TJOB, unknown30) == 0x30, "");
static_assert(offsetof(TJOB, unknown34) == 0x34, "");
static_assert(offsetof(TJOB, unknown38) == 0x38, "");
static_assert(offsetof(TJOB, unknown3c) == 0x3c, "");
static_assert(sizeof(TJOB) == 0x40, "");

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
  static u64 getThreadId(CPUID cpuId);
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
  static u32 getOdd();
  static bool isBackground();
  static void syncSubCpu();
  static void wakeup(int cpu);
  static void removeAutoExecGrp(int group);
  static void releaseGroupHandle(int group);
  static void sync(int cpu, WKCPU_SYNC sync, CPUID cpuid);
  static void setHeartBeatCpu(CPUID cpu);
  static u32 getJobTrans();
  static const long &getBeginClock(bool isCurrent);
  static const long &getTailStartClock();
  static const long &getTailEndClock();
  static const long &getSyncClock();
  static u32 getCounter();
  static void gotoBackground();
  static void setBackground(bool isBackground);
  static void gotoForeground();
  static void backgroundProcess();
  static void backgroundProcess(CPUID cpu);
  static bool unregistErrorCB(IErrorCB *callback);
  static void addShutdownForceListener(IWorkEvent *listener);
  static void removeShutdownForceListener(IWorkEvent *listener);
  static void addBackgroundListener(IWorkBackground *listener);
  static void removeBackgroundListener(IWorkBackground *listener);
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
  static void attachJobCol(const mm::Col3 &color);

  // Inferred role: packs a color into an ABGR word; original name unknown.
  static u32 unknown001(const mm::Col3 &color) { return static_cast<u32>(color.r * 255.0f) | static_cast<u32>(color.g * 255.0f) << 8 | static_cast<u32>(color.b * 255.0f) << 16 | 0xff000000; }
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
  u8 _1768[0x1798 - 0x1768];
  TJOB *unknown1798; // Inferred role: last entered job; original member name unknown.
  u8 _17a0[0x195c - 0x17a0];
  u32 unknown195c;                                       // Inferred role: counter; original member name unknown.
  mm::mtl::FixedList<IWorkEvent *, 32> unknown1960;      // Inferred role: shutdown force listeners; original member name unknown.
  mm::mtl::FixedList<IWorkBackground *, 32> unknown1ba0; // Inferred role: background listeners; original member name unknown.
  mm::mtl::FixedList<IWorkInfomation *, 32> unknown1de0; // Inferred role: system info listeners; original member name unknown.
  u64 unknown2020;                                       // Inferred role: main thread id; original member name unknown.
  u32 unknown2028[2];                                    // Inferred role: job trans; original member name unknown.
  u8 _2030[0x2034 - 0x2030];
  f32 unknown2034; // Inferred role: all cost sec; original member name unknown.
  u8 _2038[0x2048 - 0x2038];
  long unknown2048[5]; // Inferred role: begin clocks; original member name unknown.
  long unknown2070;    // Inferred role: tail start clock; original member name unknown.
  long unknown2078;    // Inferred role: tail end clock; original member name unknown.
  long unknown2080;    // Inferred role: sync clock; original member name unknown.
  u8 _2088[0x2090 - 0x2088];
  unsigned long unknown2090; // Inferred role: frame count; original member name unknown.
  u8 _2098[0x20a0 - 0x2098];
  mm::mtl::FixedList<IErrorCB *, 32> unknown20a0; // Inferred role: error callbacks; original member name unknown.
  CriticalSectionNC unknown22e0;                  // Inferred role: error callbacks lock; original member name unknown.
};

static_assert(offsetof(WorkCpu, unknown1b0) == 0x1b0, "");
static_assert(offsetof(WorkCpu, unknown1bc) == 0x1bc, "");
static_assert(offsetof(WorkCpu, unknown1738) == 0x1738, "");
static_assert(offsetof(WorkCpu, unknown1740) == 0x1740, "");
static_assert(offsetof(WorkCpu, unknown1758) == 0x1758, "");
static_assert(offsetof(WorkCpu, unknown1764) == 0x1764, "");
static_assert(offsetof(WorkCpu, unknown1798) == 0x1798, "");
static_assert(offsetof(WorkCpu, unknown195c) == 0x195c, "");
static_assert(offsetof(WorkCpu, unknown1960) == 0x1960, "");
static_assert(offsetof(WorkCpu, unknown1ba0) == 0x1ba0, "");
static_assert(offsetof(WorkCpu, unknown1de0) == 0x1de0, "");
static_assert(offsetof(WorkCpu, unknown2020) == 0x2020, "");
static_assert(offsetof(WorkCpu, unknown2034) == 0x2034, "");
static_assert(offsetof(WorkCpu, unknown2048) == 0x2048, "");
static_assert(offsetof(WorkCpu, unknown2080) == 0x2080, "");
static_assert(offsetof(WorkCpu, unknown2090) == 0x2090, "");
static_assert(offsetof(WorkCpu, unknown20a0) == 0x20a0, "");
static_assert(offsetof(WorkCpu, unknown22e0) == 0x22e0, "");

} // namespace ml
