#pragma once
#include <stddef.h>

#include "ml/work_cpu.h"
#include "ml/work_obj.h"
#include "types.h"

namespace ml {
class CriticalSection;
class Thread;
struct MLTHREAD;
struct TJOB;

class WorkCpuThread : public WorkObj {
public:
  bool isSuspendThread() const;
  bool isWaitEvent() const;
  MLTHREAD *getHandle() const;
  CPUID getCPUID() const;
  void getStackInfo(unsigned long &address, unsigned long &size);
  u64 getThreadID() const;
  f32 getJobCost() const;
  int getJobNum() const;
  void setEvent(bool isSignal);
  u32 updateDirect(bool isDirect);
  bool hasWorkingJob() const;
  u32 getAboutJobNumC() const;
  void beginUpdate();
  void calcPerformance(bool isCalc);
  void changeFrame();
  bool isStackOverFlow() const;
  static unsigned int threadFunc(void *argument);
  bool isBeginTerm() const;
  void addJobClock(f32 clock);
  void terminateWorkingJob(const TJOB *job);
  void waitEvent();
  WorkCpuThread(const char *name, WorkObj *parent);
  ~WorkCpuThread() override;
  void setWorkingJob(TJOB *job);
  void setup(CPUID cpuId);
  void setBackground(bool isBackground);
  bool isBackground() const;
  void setStackInfo(unsigned long address, unsigned long size, void *stack);
  void suspendThread();
  void resumeThread();
  void wkTail() override;
  bool wkStandbyLogin() override;
  void termThread();
  bool isTermThread();
  void exitThread();

  CPUID m_CPUID;
  u64 m_threadID;
  Thread *unknown1b8; // Inferred role: thread; original member name unknown.
  u8 _1c0[0x1c8 - 0x1c0];
  u32 m_aboutJobNumC;
  long unknown1d0;             // Inferred role: begin clock; original member name unknown.
  long unknown1d8;             // Inferred role: end clock; original member name unknown.
  f32 unknown1e0;              // Inferred role: job clock; original member name unknown.
  f32 unknown1e4;              // Inferred role: job cost; original member name unknown.
  CriticalSection *unknown1e8; // Inferred role: cs; original member name unknown.
  u8 _1f0[0x648 - 0x1f0];
  int unknown648;           // Inferred role: job num; original member name unknown.
  TJOB *unknown650;         // Inferred role: working job; original member name unknown.
  u32 unknown658;           // Inferred role: color; original member name unknown.
  unsigned long unknown660; // Inferred role: stack address; original member name unknown.
  unsigned long unknown668; // Inferred role: stack size; original member name unknown.
  bool m_background;
  bool unknown671; // Inferred role: direct; original member name unknown.
  bool m_beginTerm;
};

static_assert(offsetof(WorkCpuThread, m_CPUID) == 0x1a8, "");
static_assert(offsetof(WorkCpuThread, unknown1b8) == 0x1b8, "");
static_assert(offsetof(WorkCpuThread, m_aboutJobNumC) == 0x1c8, "");
static_assert(offsetof(WorkCpuThread, unknown1d0) == 0x1d0, "");
static_assert(offsetof(WorkCpuThread, unknown1e4) == 0x1e4, "");
static_assert(offsetof(WorkCpuThread, unknown1e8) == 0x1e8, "");
static_assert(offsetof(WorkCpuThread, unknown648) == 0x648, "");
static_assert(offsetof(WorkCpuThread, unknown658) == 0x658, "");
static_assert(offsetof(WorkCpuThread, unknown660) == 0x660, "");
static_assert(offsetof(WorkCpuThread, m_beginTerm) == 0x672, "");

} // namespace ml
