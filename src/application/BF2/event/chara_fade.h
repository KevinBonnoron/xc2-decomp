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
  gf::GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  AnmF32 unknown10;             // Inferred role: anm; original member name unknown.
};

static_assert(sizeof(CharaFade) == 0x120, "");

} // namespace event
