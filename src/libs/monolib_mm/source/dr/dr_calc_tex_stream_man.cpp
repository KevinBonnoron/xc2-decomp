#include "dr/dr_calc_tex_stream_man.h"

#include "ml/critical_section.h"
#include "ml/work_cpu.h"

namespace ml {

CriticalSection &DrCalcTexStreamMan::getCriticalSection() {
  static CriticalSection sect;
  return sect;
}

int DrCalcTexStreamMan::getUseMax() const {
  const DrCalcTexStmObj *obj = unknown08;
  if (obj != nullptr) {
    int count = 0;
    do {
      count += obj->unknown24 & 1;
      obj = obj->unknown10;
    } while (obj != nullptr);
    return count;
  }
  return 0;
}

int DrCalcTexStreamMan::getFreeMax() const {
  const DrCalcTexStmObj *obj = unknown08;
  if (obj != nullptr) {
    int count = 0;
    do {
      count += ~obj->unknown24 & 1;
      obj = obj->unknown10;
    } while (obj != nullptr);
    return count;
  }
  return 0;
}

int DrCalcTexStreamMan::getAllFreeSize() const {
  const DrCalcTexStmObj *obj = unknown08;
  if (obj != nullptr) {
    int size = 0;
    do {
      if ((obj->unknown24 & 1) == 0) {
        size += obj->unknown20;
      }
      obj = obj->unknown10;
    } while (obj != nullptr);
    return size;
  }
  return 0;
}

int DrCalcTexStreamMan::getAllUseSize() const {
  const DrCalcTexStmObj *obj = unknown08;
  if (obj != nullptr) {
    int size = 0;
    do {
      if ((obj->unknown24 & 1) != 0) {
        size += obj->unknown20;
      }
      obj = obj->unknown10;
    } while (obj != nullptr);
    return size;
  }
  return 0;
}

DrCalcTexStmObj *DrCalcTexStreamMan::getTopAheadFreeObj() {
  DrCalcTexStmObj *obj = unknown08;
  while (obj != nullptr && (obj->unknown24 & 1) != 0) {
    obj = obj->unknown10;
  }
  return obj;
}

void DrCalcTexStreamMan::entryJob() { WorkCpu::wakeup(unknown2498); }

u32 DrCalcTexStreamMan::jobUpdate(void *argument, void *userData) {
  static_cast<DrCalcTexStreamMan *>(argument)->update();
  return 0;
}

void DrCalcTexStreamMan::releaseFreeObj(DrCalcTexStmObj *&object) {
  if (object != nullptr) {
    clearMemObj(object);
    object = nullptr;
  }
}

void DrCalcTexStreamMan::jobWait() { WorkCpu::sync(unknown2498, WKCPU_SYNC_NONE, CPUID_ANY); }

void DrCalcTexStreamMan::callHlvTexOptimization() { unknown248c = 0xa0; }

void DrCalcTexStreamMan::callOptimization(u32 value) { unknown2488 += value; }

void DrCalcTexStreamMan::callReadStopMode() {
  unknown2068 |= 0x20;
  unknown248c = 0xa0;
  unknown248e = 0x000a;
}

} // namespace ml
