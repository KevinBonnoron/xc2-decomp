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
  gf::GF_OBJ_HANDLE *handle;
  u8 _10[0x30 - 0x10];
  CharaWalkCalculator calculator;
  u8 _C0[0xd0 - 0xc0];
};

static_assert(sizeof(CharaWalkPos) == 0xd0, "");

} // namespace event
