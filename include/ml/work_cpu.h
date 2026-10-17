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
  static void setThread(DO_THREAD thread);
  static DO_THREAD getThread();
  static u32 getEven();
  static void runThread(CPUID cpu, unsigned int (*function)(void *, void *), void *argument, void *userData, const mm::Col3 *color, bool isDebug,
                        WKCPU_SYNC sync);
  static bool isShutdown();
  static u32 getFrameCountU32();
  static const unsigned long &getFrameCount();
  static bool getOdd();
  static bool isBackground();
  static void syncSubCpu();
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
  static u32 thForeground(void *argument, void *userData);
  static u32 thBackground(void *argument, void *userData);
  static void setAfterUpdateRender(bool isAfterUpdateRender);
  static bool isHomeMenuEnable();
  static s32 getHeartBeatStall();
  static void clrHeartBeatStall();

  static bool s_bRenderSubCpu;

  u32 m_flags;
  mtl::ALLOC_HANDLE m_memWork;
  mtl::ALLOC_HANDLE m_memStack;
  u32 m_cpuNum;
  u8 _1c0[0x1738 - 0x1c0];
  DO_THREAD m_thread;
  DO_THREAD m_nextThread;
  u8 _1740[0x1764 - 0x1740];
  u32 m_even;
  u8 _1768[0x195c - 0x1768];
  u32 m_counter;
  u8 _1960[0x2020 - 0x1960];
  u64 m_mainThreadId;
  u32 m_jobTrans[2];
  u8 _2030[0x2034 - 0x2030];
  f32 m_allCostSec;
  u8 _2038[0x2048 - 0x2038];
  long m_beginClocks[5];
  long m_tailStartClock;
  long m_tailEndClock;
  long m_syncClock;
  u8 _2088[0x2090 - 0x2088];
  unsigned long m_frameCount;
};

static_assert(offsetof(WorkCpu, m_flags) == 0x1b0, "");
static_assert(offsetof(WorkCpu, m_cpuNum) == 0x1bc, "");
static_assert(offsetof(WorkCpu, m_thread) == 0x1738, "");
static_assert(offsetof(WorkCpu, m_even) == 0x1764, "");
static_assert(offsetof(WorkCpu, m_counter) == 0x195c, "");
static_assert(offsetof(WorkCpu, m_mainThreadId) == 0x2020, "");
static_assert(offsetof(WorkCpu, m_allCostSec) == 0x2034, "");
static_assert(offsetof(WorkCpu, m_beginClocks) == 0x2048, "");
static_assert(offsetof(WorkCpu, m_syncClock) == 0x2080, "");
static_assert(offsetof(WorkCpu, m_frameCount) == 0x2090, "");

} // namespace ml
