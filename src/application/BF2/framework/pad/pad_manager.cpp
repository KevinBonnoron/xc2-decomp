#include "framework/manager_object.h"
#include "fw/fw_pad.h"
#include "ml/dev_pad.h"
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace fw {

int PadManager::getPadMax() { return ml::DevPad::getPadMax(); }

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

const char *PadManager::getPadFilterName(int padNo) {
  IPadFilter *filter = get()->filters[padNo];
  if (filter != nullptr) {
    return filter->getFilterName();
  }

  return "none";
}

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

const char *PadManager::getName() const { return "PadManager"; }

} // namespace fw
