#pragma once
#include "event/anm_vec.h"
#include "event/i_cmd.h"
#include "types.h"

namespace event {

class CharaLinerPos : public ICmd {
public:
  virtual RESULT update(const Param &param);

private:
  u8 _08[0x20 - 0x08];
  AnmVec anm;
};

static_assert(sizeof(CharaLinerPos) == 0x210, "");

} // namespace event
