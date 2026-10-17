#pragma once
#include "event/i_cmd.h"
#include "types.h"

namespace event {

class CharaHideWpn : public ICmd {
public:
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  u8 _08[0x18 - 0x08];
};

static_assert(sizeof(CharaHideWpn) == 0x18, "");

} // namespace event
