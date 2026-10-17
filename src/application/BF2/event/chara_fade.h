#pragma once
#include "event/anm_f32.h"
#include "event/i_cmd.h"
#include "types.h"

namespace event {

class CharaFade : public ICmd {
public:
  virtual RESULT update(const Param &param);

private:
  u8 _08[0x10 - 0x08];
  AnmF32 anm;
};

static_assert(sizeof(CharaFade) == 0x120, "");

} // namespace event
