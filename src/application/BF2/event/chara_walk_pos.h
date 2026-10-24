#pragma once
#include "event/chara_walk_calculator.h"
#include "event/i_cmd.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaWalkPos : public ICmd {
public:
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  gf::GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  u8 _10[0x30 - 0x10];
  CharaWalkCalculator unknown30; // Inferred role: calculator; original member name unknown.
  u8 unknownc0[0xd0 - 0xc0];     // Inferred role: c0; original member name unknown.
};

static_assert(sizeof(CharaWalkPos) == 0xd0, "");

} // namespace event
