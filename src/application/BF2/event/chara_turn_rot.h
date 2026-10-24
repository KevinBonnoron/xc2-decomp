#pragma once
#include "event/i_cmd.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaTurnRot : public ICmd {
public:
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  u32 unknown08;                // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  u8 _18[0x20 - 0x18];
};

static_assert(sizeof(CharaTurnRot) == 0x20, "");

} // namespace event
