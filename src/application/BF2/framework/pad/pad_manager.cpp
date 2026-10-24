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
  if (manager != nullptr && manager->unknown2b40[0].unknown40 && manager->unknown2b40[0].unknown3c != -1) {
    ml::DevPad::stopVibration(manager->unknown2b40[0].unknown3c);
  }
}

void PadManager::setFilter(int padNo, IPadFilter *filter) { get()->unknown20[padNo] = filter; }

int PadManager::getPadMax() { return ml::DevPad::getPadMax(); }

u32 PadManager::updateRepeat(int padNo, const PadData &pad, PadWorkArray &works, f32 deltaTime) {
  u32 repeat = pad.unknown04;
  for (u32 i = 0; i < BUTTON_MAX; i++) {
    PadWork &work = works[padNo][i];
    if ((pad.unknown00 & 1 << i) != 0) {
      work.unknown00 += deltaTime;
      if (work.unknown00 >= (!work.unknown08 ? unknown3664 : unknown3660)) {
        repeat |= 1 << i;
        work.unknown00 = 0.0f;
        work.unknown08 = true;
      }
    } else {
      work.unknown00 = 0.0f;
      work.unknown08 = false;
    }
  }

  return repeat;
}

u32 PadManager::updateCnt(int padNo, const PadData &pad, PadWorkArray &works, f32 deltaTime) {
  u32 cnt = 0;
  for (u32 i = 0; i < BUTTON_MAX; i++) {
    PadWork &work = works[padNo][i];
    if ((pad.unknown00 & 1 << i) == 0 && unknown3668 < work.unknown04 && work.unknown04 < unknown366c) {
      cnt |= 1 << i;
    }
  }

  return cnt;
}

u32 PadManager::updateHold(int padNo, const PadData &pad, PadWorkArray &works, f32 deltaTime) {
  u32 hold = 0;
  for (u32 i = 0; i < BUTTON_MAX; i++) {
    PadWork &work = works[padNo][i];
    if ((pad.unknown00 & 1 << i) != 0) {
      if (work.unknown04 > unknown366c) {
        hold |= 1 << i;
      } else {
        work.unknown04 += deltaTime;
      }
    } else {
      work.unknown04 = 0.0f;
    }
  }

  return hold;
}

void PadManager::setRepeatTime(f32 time) {
  PadManager *manager = get();
  ml::DevPad::setRepeatTime(time);
  manager->unknown3660 = time;
}

void PadManager::setRepeatTimeFirst(f32 time) {
  PadManager *manager = get();
  ml::DevPad::setRepeatTime(time);
  manager->unknown3664 = time;
}

void PadManager::setCntTime(f32 time) { get()->unknown3668 = time; }

void PadManager::setHoldTime(f32 time) { get()->unknown366c = time; }

bool PadManager::isInitialized() const {
  if (!ml::DevPad::isInitialized()) {
    return false;
  }

  return ManagerObject::isInitialized();
}

const PadData *PadManager::getPadData(int padNo) {
  PadManager *manager = get();
  if (manager != nullptr && static_cast<u32>(padNo) < PAD_MAX) {
    return &manager->unknown80[padNo];
  }

  return &m_nullPad;
}

void PadManager::setControlPadNo(int index, int padNo) {
  PadManager *manager = get();
  if (manager != nullptr) {
    manager->unknown35f0[index] = padNo;
  }
}

void PadManager::setDebugPadNo(int index, int padNo) {
  PadManager *manager = get();
  if (manager != nullptr) {
    manager->unknown3620[index] = padNo;
  }
}

const PadData *PadManager::getControlPadData(int index) {
  PadManager *manager = get();
  return manager == nullptr ? &m_nullPad : &manager->unknown2b40[index];
}

const PadData *PadManager::getDebugPadData(int index) {
  PadManager *manager = get();
  return manager == nullptr ? &m_nullPad : &manager->unknown2ea0[index];
}

void PadManager::playVibration(const ml::PadVibrationInfo &info) {
  PadManager *manager = get();
  if (manager != nullptr && manager->unknown2b40[0].unknown40 && manager->unknown2b40[0].unknown3c != -1) {
    ml::DevPad::playVibration(manager->unknown2b40[0].unknown3c, info);
  }
}

const char *PadManager::getPadFilterName(int padNo) {
  IPadFilter *filter = get()->unknown20[padNo];
  if (filter != nullptr) {
    return filter->getFilterName();
  }

  return "none";
}

void PadManager::setARXThreshold(int padNo, f32 threshold) { get()->unknown80[padNo].unknown2c = threshold; }

void PadManager::setARYThreshold(int padNo, f32 threshold) { get()->unknown80[padNo].unknown30 = threshold; }

void PadManager::setALXThreshold(int padNo, f32 threshold) { get()->unknown80[padNo].unknown34 = threshold; }

void PadManager::setALYThreshold(int padNo, f32 threshold) { get()->unknown80[padNo].unknown38 = threshold; }

void PadManager::setEnable(int padNo, bool isEnable) { get()->unknown3650.set(padNo, isEnable); }

void PadManager::enableDebugDraw(bool isEnable) {
  PadManager *manager = get();
  if (manager != nullptr) {
    manager->unknown3654 = isEnable;
  }
}

bool PadManager::isDebugDraw() {
  PadManager *manager = get();
  if (manager != nullptr) {
    return manager->unknown3654;
  }

  return false;
}

void PadManager::setConfigData(int padNo, const PadConfigData &data) {
  PadManager *manager = get();
  if (manager != nullptr) {
    manager->unknown3200[padNo] = data;
  }
}

const char *PadManager::getName() const { return "PadManager"; }

} // namespace fw
