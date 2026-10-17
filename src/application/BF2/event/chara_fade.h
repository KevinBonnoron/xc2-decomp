#pragma once
#include "event/anm_f32.h"
#include "event/i_cmd.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaFade : public ICmd {
public:
  virtual RESULT update(const Param &param);

private:
  gf::GF_OBJ_HANDLE *handle;
  AnmF32 anm;
};

static_assert(sizeof(CharaFade) == 0x120, "");

} // namespace event
