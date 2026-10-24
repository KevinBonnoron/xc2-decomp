#include "ml/dev_pad.h"

#include "ml/dev_graph.h"
#include "ml/lib_main.h"
#include "ml/reslist.h"
#include "ml/work_system.h"

namespace ml {

void DevPad::setWirelessPadMax(u32 max) { s_nMaxWirelessPad = max > 5 ? 5 : max; }

u32 DevPad::getWirelessPadMax() { return s_nMaxWirelessPad; }

int DevPad::getPadMax() { return 11; }

void DevPad::setRepeatTime(float time) {
  DevPad *pad = get();
  if (pad != nullptr) {
    time = time < 0.03f ? 0.03f : time;
    for (int i = 0; i < 11; i++) {
      pad->unknown4b0[i].unknown00 = time;
    }
  }
}

bool DevPad::isInitialized() {
  DevPad *pad = get();
  if (pad == nullptr || pad->wkIsWaitException()) {
    return false;
  }

  return pad->wkIsActive();
}

bool DevPad::isConnectPad(int padNo) {
  DevPad *pad = get();
  if (pad != nullptr) {
    return pad->isLocalConnect(padNo);
  }

  return false;
}

u32 DevPad::getStylePad(int padNo) {
  DevPad *pad = get();
  if (pad != nullptr) {
    return pad->getLocalStyle(padNo);
  }

  return 0;
}

int DevPad::getUserSelectPadID() {
  DevPad *pad = get();
  if (pad != nullptr) {
    return pad->getLocalUserSelectPadID();
  }

  return 0;
}

bool DevPad::isDebugPad(int padNo) { return padNo == s_debugPadNo; }

u32 DevPad::getBtn(int padNo) {
  DevPad *pad = get();
  if (pad != nullptr) {
    return pad->unknown244[padNo];
  }

  return 0;
}

u32 DevPad::getDown(int padNo) {
  DevPad *pad = get();
  if (pad != nullptr) {
    return pad->unknown1ec[padNo];
  }

  return 0;
}

u32 DevPad::getUp(int padNo) {
  DevPad *pad = get();
  if (pad != nullptr) {
    return pad->unknown218[padNo];
  }

  return 0;
}

u32 DevPad::getRepeat(int padNo) {
  DevPad *pad = get();
  if (pad != nullptr) {
    return pad->unknown29c[padNo];
  }

  return 0;
}

u32 DevPad::getDbl(int padNo) {
  DevPad *pad = get();
  if (pad != nullptr) {
    return pad->unknown270[padNo];
  }

  return 0;
}

f32 DevPad::getALX(int padNo, bool isLowCut) {
  DevPad *pad = get();
  if (pad == nullptr) {
    return 0.0f;
  }

  f32 value = pad->getLocalALX(padNo);
  f32 lowAnalog = getLowAnalog();
  if (isLowCut && value < lowAnalog && value > -lowAnalog) {
    return 0.0f;
  }

  return value;
}

f32 DevPad::getLowAnalog() {
  DevPad *pad = get();
  if (pad != nullptr) {
    return pad->unknown540;
  }

  return 0.0f;
}

f32 DevPad::getALY(int padNo, bool isLowCut) {
  DevPad *pad = get();
  if (pad == nullptr) {
    return 0.0f;
  }

  f32 value = pad->getLocalALY(padNo);
  f32 lowAnalog = getLowAnalog();
  if (isLowCut && value < lowAnalog && value > -lowAnalog) {
    return 0.0f;
  }

  return value;
}

f32 DevPad::getARX(int padNo, bool isLowCut) {
  DevPad *pad = get();
  if (pad == nullptr) {
    return 0.0f;
  }

  f32 value = pad->getLocalARX(padNo);
  f32 lowAnalog = getLowAnalog();
  if (isLowCut && value < lowAnalog && value > -lowAnalog) {
    return 0.0f;
  }

  return value;
}

f32 DevPad::getARY(int padNo, bool isLowCut) {
  DevPad *pad = get();
  if (pad == nullptr) {
    return 0.0f;
  }

  f32 value = pad->getLocalARY(padNo);
  f32 lowAnalog = getLowAnalog();
  if (isLowCut && value < lowAnalog && value > -lowAnalog) {
    return 0.0f;
  }

  return value;
}

void DevPad::playVibration(int padNo, const PadVibrationInfo &info) {
  DevPad *pad = get();
  if (pad != nullptr) {
    pad->playLocalVibration(padNo, info);
  }
}

void DevPad::stopVibration(int padNo) {
  DevPad *pad = get();
  if (pad != nullptr) {
    pad->stopLocalVibration(padNo);
  }
}

void DevPad::loadVibration(u32 id, void *data, unsigned long size) {
  DevPad *pad = get();
  if (pad != nullptr) {
    pad->loadLocalVibration(id, data, size);
  }
}

void DevPad::setLowAnalog(f32 lowAnalog) {
  DevPad *pad = get();
  if (pad != nullptr) {
    pad->unknown540 = lowAnalog;
  }
}

void DevPad::initCaptureName(const char *name) {
  DevPad *pad = get();
  if (pad != nullptr) {
    pad->setCaptureName(name);
  }
}

void DevPad::capturePad(bool isCapture) {
  DevPad *pad = get();
  if (pad != nullptr) {
    pad->setCapture(isCapture);
  }
}

bool DevPad::isCaprurePad() {
  DevPad *pad = get();
  if (pad != nullptr) {
    return pad->isCapture();
  }

  return false;
}

void DevPad::wkUpdate() {}

bool DevPad::wkStandbyLogin() {
  if (!dg::s_bIgnore && !createDevice()) {
    return false;
  }

  return WorkObj::wkStandbyLogin();
}

bool DevPad::wkStandbyLogout() {
  if (unknown60.size() == 0 && WorkSystem::get() == nullptr && LibMain::get() == nullptr) {
    releaseDevice();
    return WorkObj::wkStandbyLogout();
  }

  return false;
}

void DevPad::viBeginFrame() { updateLocal(); }

void DevPad::fnSubCpuUpdate(void *pad) { static_cast<DevPad *>(pad)->updateLocal(); }

} // namespace ml
