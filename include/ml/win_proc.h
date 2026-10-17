#pragma once
#include "ml/work_obj.h"
#include "types.h"

namespace ml {

class WinProc : public WorkObj {
public:
  WinProc(const char *name, WorkObj *parent, s16 childNum);
  ~WinProc() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;

  u8 _1a8[0x1f0 - 0x1a8];
};

static_assert(sizeof(WinProc) == 0x1f0, "");

} // namespace ml
