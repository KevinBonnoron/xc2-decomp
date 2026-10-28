#include "ml/dev_pad_util.h"

#include "ml/dev_pad.h"

namespace ml {

int DevPadUtil::getControlPadNo() {
  DevPad *pad = DevPad::get();
  int padNo = 0;
  if (pad != nullptr) {
    padNo = pad->isLocalConnect(4) ? 4 : 0;
  }
  return padNo;
}

int DevPadUtil::getDebugPadNo() { return 9; }

u32 DevPadUtil::getBtn(Type type) {
  if (type == TYPE_UNKNOWN_0) {
    return DevPad::getBtn(getControlPadNo());
  }
  return DevPad::getBtn(getDebugPadNo());
}

u32 DevPadUtil::getDown(Type type) {
  if (type == TYPE_UNKNOWN_0) {
    return DevPad::getDown(getControlPadNo());
  }
  return DevPad::getDown(getDebugPadNo());
}

u32 DevPadUtil::getUp(Type type) {
  if (type == TYPE_UNKNOWN_0) {
    return DevPad::getUp(getControlPadNo());
  }
  return DevPad::getUp(getDebugPadNo());
}

u32 DevPadUtil::getRepeat(Type type) {
  if (type == TYPE_UNKNOWN_0) {
    return DevPad::getRepeat(getControlPadNo());
  }
  return DevPad::getRepeat(getDebugPadNo());
}

u32 DevPadUtil::getDbl(Type type) {
  if (type == TYPE_UNKNOWN_0) {
    return DevPad::getDbl(getControlPadNo());
  }
  return DevPad::getDbl(getDebugPadNo());
}

f32 DevPadUtil::getALX(Type type) {
  if (type == TYPE_UNKNOWN_0) {
    return DevPad::getALX(getControlPadNo(), true);
  }
  return DevPad::getALX(getDebugPadNo(), true);
}

f32 DevPadUtil::getALY(Type type) {
  if (type == TYPE_UNKNOWN_0) {
    return DevPad::getALY(getControlPadNo(), true);
  }
  return DevPad::getALY(getDebugPadNo(), true);
}

f32 DevPadUtil::getARX(Type type) {
  if (type == TYPE_UNKNOWN_0) {
    return DevPad::getARX(getControlPadNo(), true);
  }
  return DevPad::getARX(getDebugPadNo(), true);
}

f32 DevPadUtil::getARY(Type type) {
  if (type == TYPE_UNKNOWN_0) {
    return DevPad::getARY(getControlPadNo(), true);
  }
  return DevPad::getARY(getDebugPadNo(), true);
}

} // namespace ml
