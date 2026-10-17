#pragma once
#include "event/i_cmd.h"
#include "types.h"

namespace event {

class CharaPlayEva : public ICmd {
public:
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  u8 _08[0x40 - 0x08];
};

static_assert(sizeof(CharaPlayEva) == 0x40, "");

} // namespace event
