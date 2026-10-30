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
  mm::mtl::unknown027<FLAG_MAX> unknown08; // Inferred role: flags; original member name unknown.
  u32 unknown0c;                           // Inferred role: npc id; original member name unknown.
  f32 unknown10;                           // Inferred role: time; original member name unknown.
};

static_assert(sizeof(CharaHideWpn) == 0x18, "");

} // namespace event
