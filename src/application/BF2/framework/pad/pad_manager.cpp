#include <ctype.h>
#include <string.h>

#include "framework/manager_object.h"
#include "framework/resource/common_resource.h"
#include "framework/sound/sound_manager.h"
#include "fw/fw_pad.h"
#include "fw/fw_update_info.h"
#include "ml/controller_applet.h"
#include "ml/dev_clock.h"
#include "ml/dev_pad.h"
#include "ml/dev_perf.h"
#include "ml/ml_mem.h"
#include "ml/work_cpu.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace fw {

namespace detail {

template <typename T> int getPadNo(const T &name) {
  static const char *padNames[] = {
      "pad0", "pad1", "pad2", "pad3", "pad4", "pad5", "pad6", "pad7"}; // Name from the game symbol _ZZN2fw6detail8getPadNoIN2mm3mtl6FixStrILi32EEEEEiRKT_E8padNames; also in torna.
  for (int i = 0; i < 8; i++) {
    if (strcmp(name.c_str(), padNames[i]) == 0) {
      return i;
    }
  }

  return -1;
}

template int getPadNo<mm::mtl::FixStr<32>>(const mm::mtl::FixStr<32> &);

} // namespace detail

PadManager::~PadManager() {}

bool PadManager::registListener(IPadListener *listener) {
  PadManager *manager = get();
  if (manager != nullptr) {
    if (manager->unknown3678.find(listener) == manager->unknown3678.end()) {
      manager->unknown3678.push(listener);
    }
  }
  return manager != nullptr;
}

IPadListener::IPadListener() { PadManager::registListener(this); }

IPadListener::~IPadListener() { PadManager::removeListener(this); }

void PadManager::removeListener(IPadListener *listener) {
  if (get() != nullptr) {
    get()->unknown3678.remove(listener);
  }
}

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

void PadManager::setFilter(int padNo, IPadFilter *filter) { get()->m_filter[padNo] = filter; }

int PadManager::getPadMax() { return ml::DevPad::getPadMax(); }

void PadManager::makePadData(int padNo) {
  IPadFilter *filter = m_filter[padNo];
  f32 alx = ml::DevPad::getALX(padNo, false);
  f32 aly = ml::DevPad::getALY(padNo, false);
  f32 arx = ml::DevPad::getARX(padNo, false);
  f32 ary = ml::DevPad::getARY(padNo, false);
  u32 btn = ml::DevPad::getBtn(padNo);
  u32 down = ml::DevPad::getDown(padNo);
  u32 up = ml::DevPad::getUp(padNo);
  u32 dbl = ml::DevPad::getDbl(padNo);
  if (__builtin_isnan(alx)) {
    alx = 0.0f;
  }
  if (__builtin_isnan(aly)) {
    aly = 0.0f;
  }
  if (__builtin_isnan(arx)) {
    arx = 0.0f;
  }
  if (__builtin_isnan(ary)) {
    ary = 0.0f;
  }
  unknown80[padNo].unknown00 = filter->filterBtn(btn);
  unknown80[padNo].unknown04 = filter->filterBtn(down);
  unknown80[padNo].unknown08 = filter->filterBtn(up);
  unknown80[padNo].unknown10 = filter->filterBtn(dbl);
  unknown80[padNo].unknown1c = filter->filterALX(alx, aly);
  unknown80[padNo].unknown20 = filter->filterALY(alx, aly);
  unknown80[padNo].unknown24 = filter->filterARX(arx, ary);
  unknown80[padNo].unknown28 = filter->filterARY(arx, ary);
  replacePadData(padNo);
}

u32 PadManager::updateRepeat(int padNo, const PadData &pad, PadWorkArray &works, f32 deltaTime) {
  u32 repeat = pad.unknown04;
  for (u32 i = 0; i < BUTTON_UNKNOWN_32; i++) {
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
  for (u32 i = 0; i < BUTTON_UNKNOWN_32; i++) {
    PadWork &work = works[padNo][i];
    if ((pad.unknown00 & 1 << i) == 0 && m_cntTime < work.unknown04 && work.unknown04 < m_holdTime) {
      cnt |= 1 << i;
    }
  }

  return cnt;
}

u32 PadManager::updateHold(int padNo, const PadData &pad, PadWorkArray &works, f32 deltaTime) {
  u32 hold = 0;
  for (u32 i = 0; i < BUTTON_UNKNOWN_32; i++) {
    PadWork &work = works[padNo][i];
    if ((pad.unknown00 & 1 << i) != 0) {
      if (work.unknown04 > m_holdTime) {
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

void PadManager::setCntTime(f32 time) { get()->m_cntTime = time; }

void PadManager::setHoldTime(f32 time) { get()->m_holdTime = time; }

bool PadManager::isInitialized() const {
  if (!ml::DevPad::isInitialized()) {
    return false;
  }

  return ManagerObject::isInitialized();
}

const PadData *PadManager::getPadData(int padNo) {
  PadManager *manager = get();
  if (manager != nullptr && static_cast<u32>(padNo) < PAD_UNKNOWN_12) {
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
  IPadFilter *filter = get()->m_filter[padNo];
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

void PadManager::viBeginFrame() {
  if (get() != nullptr) {
    if (!isInitialized()) {
      ml::DevClock::getClockNow(unknown3658);
      return;
    }

    f32 time;
    ml::DevClock::getTimeNow(time, unknown3658);
    UpdateInfo info;
    info.unknown00 = time;
    info.unknown04 = time;
    update(info);
    ml::DevClock::getClockNow(unknown3658);
    for (mm::mtl::FixedQueue<IPadListener *, LISTENER_UNKNOWN_16>::iterator it = unknown3678.begin(); it != unknown3678.end(); ++it) {
      (*it)->unknown001();
    }
  }
}

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

void PadManager::updateControlPadNo(int padNo) {
  int userPadNo = ml::DevPad::getUserSelectPadID();
  if (userPadNo == -1) {
    unknown3670 = -1;
  } else {
    int prevPadNo = unknown3670;
    if (!unknown80[userPadNo].unknown40) {
      userPadNo = -1;
    }
    unknown3670 = userPadNo;
    if (prevPadNo != userPadNo && userPadNo != -1) {
      unknown35f0[padNo] = userPadNo;
      return;
    }
  }

  if (ml::DevPerf::getOperationMode() == ml::DEV_PERF_OPERATION_MODE_UNKNOWN_0) {
    if (padNo == 0) {
      const PadData &handheldPad = unknown80[4];
      if (handheldPad.unknown40 && handheldPad.unknown44 == 3) {
        unknown35f0[0] = 4;
        return;
      }
    }
    u32 index = padNo;
    if (unknown80[index].unknown40 && unknown80[index].unknown44 - 1 < 2) {
      unknown35f0[padNo] = padNo;
      return;
    }
  } else if (ml::DevPerf::getOperationMode() == ml::DEV_PERF_OPERATION_MODE_UNKNOWN_1) {
    for (u32 i = padNo; i < PAD_UNKNOWN_12; i++) {
      if (unknown80[i].unknown40 && unknown80[i].unknown44 - 1 < 2) {
        unknown35f0[padNo] = i;
        return;
      }
    }
  }

  SoundManager::get()->pauseAll(true, 0.0f);
  ml::WorkCpu::setBackground(true);
  ml::ControllerApplet::showApplet();
  ml::WorkCpu::setBackground(false);
  SoundManager::get()->pauseAll(false, 0.0f);
  unknown35f0[padNo] = -1;
}

void PadManager::initVibData() {
  static const char *names[] = {"INVALID",      "AUDIO_BAM_1",  "AUDIO_BAM_2", "AUDIO_BOOM_1", "AUDIO_BOOM_2", "AUDIO_BOOM_3", "AUDIO_BUBOOM", "AUDIO_BUBUBU",
                                "AUDIO_BUBU_1", "AUDIO_BUBU_2", "AUDIO_BU_1",  "AUDIO_BU_2",   "AUDIO_BU_3",   "BEAT_20",      "BEAT_40",      "DAMPED_1",
                                "DAMPED_2",     "DAMPED_3",     "DAMPED_FM_1", "DAMPED_FM_2",  "DAMPED_LONG",  "SIMPLE_1",     "SIMPLE_2",     "SIMPLE_3"};
  for (u32 i = 1; i < 24; i++) {
    mm::mtl::FixStr<256> path;
    path.format("/bnvib/%s.bnvib", names[i]);
    long length = path.length();
    char *chars = &path[0];
    for (long j = 0; j != length; j++) {
      chars[j] = tolower(chars[j]);
    }
    CommonResource *resource = CommonResource::blockRequest(ml::MlMem::getDebugMem(), path.c_str(), false);
    if (resource != nullptr) {
      if (resource->valid()) {
        ml::DevPad::loadVibration(i, resource->getAssetData(), resource->getAssetSize());
      }
      resource->release();
    }
  }
}

const char *PadManager::getName() const { return "PadManager"; }

} // namespace fw
