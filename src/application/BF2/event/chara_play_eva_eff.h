#pragma once
#include "event/i_cmd.h"
#include "types.h"

namespace event {

class CharaPlayEvaEff : public ICmd {
public:
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  u8 _08[0x30 - 0x08];
};

static_assert(sizeof(CharaPlayEvaEff) == 0x30, "");

} // namespace event
