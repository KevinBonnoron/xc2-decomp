#pragma once

namespace mm {
struct Col3;
} // namespace mm

namespace ml {

enum CPUID {};
enum WKCPU_SYNC {
  WKCPU_SYNC_NONE,
  WKCPU_SYNC_WAIT,
};

class WorkCpu {
public:
  static CPUID getRenderCPUID();
  static void runThread(CPUID cpu, unsigned int (*function)(void *, void *), void *argument, void *userData, const mm::Col3 *color, bool isDebug,
                        WKCPU_SYNC sync);
  static const unsigned long &getFrameCount();
};

} // namespace ml
