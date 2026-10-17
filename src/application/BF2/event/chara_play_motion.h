#pragma once
#include "event/i_cmd.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaPlayMotion : public ICmd {
public:
  CharaPlayMotion();
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  u32 flags;
  gf::GF_OBJ_HANDLE *handle;
  u8 _18[0x50 - 0x18];
};

static_assert(sizeof(CharaPlayMotion) == 0x50, "");

} // namespace event
