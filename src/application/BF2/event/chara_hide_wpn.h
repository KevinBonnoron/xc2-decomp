#pragma once
#include "event/i_cmd.h"
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace event {

class CharaHideWpn : public ICmd {
public:
  enum {
    FLAG_VALID = 0,
    FLAG_LEFT = 1,
    FLAG_HIDE = 2,
    FLAG_ENDLESS = 3,
    FLAG_MAX = 32,
  };

  virtual RESULT update(const Param &param);
  virtual void term();

private:
  mm::mtl::BitFlag<FLAG_MAX> flags;
  u32 npcId;
  f32 time;
};

static_assert(sizeof(CharaHideWpn) == 0x18, "");

} // namespace event
