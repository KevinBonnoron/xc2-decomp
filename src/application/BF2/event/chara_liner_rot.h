#pragma once
#include "event/anm_vec.h"
#include "event/i_cmd.h"
#include "types.h"

namespace event {

class CharaLinerRot : public ICmd {
public:
  virtual RESULT update(const Param &param);

private:
  u8 _08[0x10 - 0x08];
  AnmVec anm;
};

static_assert(sizeof(CharaLinerRot) == 0x200, "");

} // namespace event
