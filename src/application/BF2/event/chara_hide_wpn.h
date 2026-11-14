#pragma once
#include "event/i_cmd.h"
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace event {

class CharaHideWpn : public ICmd {
public:
  enum {
    FLAG_UNKNOWN_0 = 0,   // Inferred role: valid flag; original name unknown.
    FLAG_UNKNOWN_1 = 1,   // Inferred role: left flag; original name unknown.
    FLAG_UNKNOWN_2 = 2,   // Inferred role: hide flag; original name unknown.
    FLAG_UNKNOWN_3 = 3,   // Inferred role: endless flag; original name unknown.
    FLAG_UNKNOWN_32 = 32, // Inferred role: max flag; original name unknown.
  };

  virtual RESULT update(const Param &param);
  virtual void term();

private:
  mm::mtl::unknown027<FLAG_UNKNOWN_32> unknown08; // Inferred role: flags; original member name unknown.
  u32 unknown0c;                                  // Inferred role: npc id; original member name unknown.
  f32 unknown10;                                  // Inferred role: time; original member name unknown.
};

static_assert(sizeof(CharaHideWpn) == 0x18, "");

} // namespace event
