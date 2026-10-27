#pragma once

#include "ml/dev_keyboard.h"

namespace ml {
class WorkObj;

class DevKeyboardNx : public DevKeyboard {
public:
  DevKeyboardNx(const char *name, WorkObj *parent);
  void wkUpdate() override;
  bool wkStandbyLogin() override;
  bool createDevice();
  void releaseDevice();
};

} // namespace ml
