#pragma once
#include <stddef.h>

#include "ml/work_cpu.h"
#include "ml/work_obj.h"
#include "types.h"

namespace ml {
class CriticalSection;
class Thread;
struct TJOB;

class WorkCpuThread : public WorkObj {
public:
  bool isSuspendThread() const;
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

  CPUID m_cpuId;
  u64 m_threadId;
  Thread *m_thread;
  u8 _1c0[0x1c8 - 0x1c0];
  u32 m_aboutJobNumC;
  long m_beginClock;
  long m_endClock;
  f32 m_jobClock;
  f32 m_jobCost;
  CriticalSection *m_cs;
  u8 _1f0[0x648 - 0x1f0];
  int m_jobNum;
  TJOB *m_workingJob;
  u32 m_color;
  unsigned long m_stackAddress;
  unsigned long m_stackSize;
  bool m_isBackground;
  bool m_isDirect;
  bool m_isBeginTerm;
};

static_assert(offsetof(WorkCpuThread, m_cpuId) == 0x1a8, "");
static_assert(offsetof(WorkCpuThread, m_thread) == 0x1b8, "");
static_assert(offsetof(WorkCpuThread, m_aboutJobNumC) == 0x1c8, "");
static_assert(offsetof(WorkCpuThread, m_beginClock) == 0x1d0, "");
static_assert(offsetof(WorkCpuThread, m_jobCost) == 0x1e4, "");
static_assert(offsetof(WorkCpuThread, m_cs) == 0x1e8, "");
static_assert(offsetof(WorkCpuThread, m_jobNum) == 0x648, "");
static_assert(offsetof(WorkCpuThread, m_color) == 0x658, "");
static_assert(offsetof(WorkCpuThread, m_stackAddress) == 0x660, "");
static_assert(offsetof(WorkCpuThread, m_isBeginTerm) == 0x672, "");

} // namespace ml
