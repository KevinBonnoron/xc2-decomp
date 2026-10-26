#include "dr/dr_calc_tex_stream_man.h"

#include "ml/work_cpu.h"

namespace ml {

void DrCalcTexStreamMan::entryJob() { WorkCpu::wakeup(unknown2498); }

void DrCalcTexStreamMan::jobWait() { WorkCpu::sync(unknown2498, WKCPU_SYNC_NONE, CPUID_ANY); }

void DrCalcTexStreamMan::callHlvTexOptimization() { unknown248c = 0xa0; }

void DrCalcTexStreamMan::callOptimization(u32 value) { unknown2488 += value; }

void DrCalcTexStreamMan::callReadStopMode() {
  unknown2068 |= 0x20;
  unknown248c = 0xa0;
  unknown248e = 0x000a;
}

} // namespace ml
