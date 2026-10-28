#pragma once

#include <stddef.h>

#include "ml/dev_keyboard.h"
#include "types.h"

namespace ml {
class WorkObj;

class DevKeyboardNx : public DevKeyboard {
public:
  DevKeyboardNx(const char *name, WorkObj *parent);
  ~DevKeyboardNx() override;
  void wkUpdate() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  bool createDevice();
  void releaseDevice();

  u64 unknowna70[6]; // Inferred role: keyboard input state; original member name unknown.
};

static_assert(offsetof(DevKeyboardNx, unknowna70) == 0xa70, "");
static_assert(sizeof(DevKeyboardNx) == 0xaa0, "");

} // namespace ml
