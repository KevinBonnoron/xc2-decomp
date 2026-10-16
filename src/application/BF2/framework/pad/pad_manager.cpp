#include "framework/manager_object.h"
#include "fw/fw_pad.h"
#include "ml/dev_pad.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace ml {
struct PadVibrationInfo;
} // namespace ml

namespace fw {

bool PadManager::finalize() {
  stopVibration();
  return true;
}

void PadManager::stopVibration() {
  PadManager *manager = get();
  if (manager != nullptr && manager->controlPadData[0].isConnected && manager->controlPadData[0].padNo != -1) {
    ml::DevPad::stopVibration(manager->controlPadData[0].padNo);
  }
}

void PadManager::setFilter(int padNo, IPadFilter *filter) { get()->filters[padNo] = filter; }

int PadManager::getPadMax() { return ml::DevPad::getPadMax(); }

u32 PadManager::updateRepeat(int padNo, const PadData &pad, PadWorkArray &works, f32 deltaTime) {
  u32 repeat = pad.trigger;
  for (u32 i = 0; i < BUTTON_MAX; i++) {
    PadWork &work = works[padNo][i];
    if ((pad.hold & 1 << i) != 0) {
      work.repeatTime += deltaTime;
      if (work.repeatTime >= (!work.isRepeat ? repeatTimeFirst : repeatTime)) {
        repeat |= 1 << i;
        work.repeatTime = 0.0f;
        work.isRepeat = true;
      }
    } else {
      work.repeatTime = 0.0f;
      work.isRepeat = false;
    }
  }

  return repeat;
}

u32 PadManager::updateCnt(int padNo, const PadData &pad, PadWorkArray &works, f32 deltaTime) {
  u32 cnt = 0;
  for (u32 i = 0; i < BUTTON_MAX; i++) {
    PadWork &work = works[padNo][i];
    if ((pad.hold & 1 << i) == 0 && cntTime < work.holdTime && work.holdTime < holdTime) {
      cnt |= 1 << i;
    }
  }

  return cnt;
}

u32 PadManager::updateHold(int padNo, const PadData &pad, PadWorkArray &works, f32 deltaTime) {
  u32 hold = 0;
  for (u32 i = 0; i < BUTTON_MAX; i++) {
    PadWork &work = works[padNo][i];
    if ((pad.hold & 1 << i) != 0) {
      if (work.holdTime > holdTime) {
        hold |= 1 << i;
      } else {
        work.holdTime += deltaTime;
      }
    } else {
      work.holdTime = 0.0f;
    }
  }

  return hold;
}

void PadManager::setRepeatTime(f32 time) {
  PadManager *manager = get();
  ml::DevPad::setRepeatTime(time);
  manager->repeatTime = time;
}

void PadManager::setRepeatTimeFirst(f32 time) {
  PadManager *manager = get();
  ml::DevPad::setRepeatTime(time);
  manager->repeatTimeFirst = time;
}

void PadManager::setCntTime(f32 time) { get()->cntTime = time; }

void PadManager::setHoldTime(f32 time) { get()->holdTime = time; }

bool PadManager::isInitialized() const {
  if (!ml::DevPad::isInitialized()) {
    return false;
  }

  return ManagerObject::isInitialized();
}

const PadData *PadManager::getPadData(int padNo) {
  PadManager *manager = get();
  if (manager != nullptr && static_cast<u32>(padNo) < PAD_MAX) {
    return &manager->pads[padNo];
  }

  return &m_nullPad;
}

void PadManager::setControlPadNo(int index, int padNo) {
  PadManager *manager = get();
  if (manager != nullptr) {
    manager->controlPadNos[index] = padNo;
  }
}

void PadManager::setDebugPadNo(int index, int padNo) {
  PadManager *manager = get();
  if (manager != nullptr) {
    manager->debugPadNos[index] = padNo;
  }
}

const PadData *PadManager::getControlPadData(int index) {
  PadManager *manager = get();
  return manager == nullptr ? &m_nullPad : &manager->controlPadData[index];
}

const PadData *PadManager::getDebugPadData(int index) {
  PadManager *manager = get();
  return manager == nullptr ? &m_nullPad : &manager->debugPadData[index];
}

void PadManager::playVibration(const ml::PadVibrationInfo &info) {
  PadManager *manager = get();
  if (manager != nullptr && manager->controlPadData[0].isConnected && manager->controlPadData[0].padNo != -1) {
    ml::DevPad::playVibration(manager->controlPadData[0].padNo, info);
  }
}

const char *PadManager::getPadFilterName(int padNo) {
  IPadFilter *filter = get()->filters[padNo];
  if (filter != nullptr) {
    return filter->getFilterName();
  }

  return "none";
}

void PadManager::setARXThreshold(int padNo, f32 threshold) { get()->pads[padNo].arxThreshold = threshold; }

void PadManager::setARYThreshold(int padNo, f32 threshold) { get()->pads[padNo].aryThreshold = threshold; }

void PadManager::setALXThreshold(int padNo, f32 threshold) { get()->pads[padNo].alxThreshold = threshold; }

void PadManager::setALYThreshold(int padNo, f32 threshold) { get()->pads[padNo].alyThreshold = threshold; }

void PadManager::setEnable(int padNo, bool isEnable) { get()->enableFlags.set(padNo, isEnable); }

void PadManager::enableDebugDraw(bool isEnable) {
  PadManager *manager = get();
  if (manager != nullptr) {
    manager->debugDrawEnable = isEnable;
  }
}

bool PadManager::isDebugDraw() {
  PadManager *manager = get();
  if (manager != nullptr) {
    return manager->debugDrawEnable;
  }

  return false;
}

void PadManager::setConfigData(int padNo, const PadConfigData &data) {
  PadManager *manager = get();
  if (manager != nullptr) {
    manager->configs[padNo] = data;
  }
}

const char *PadManager::getName() const { return "PadManager"; }

} // namespace fw
