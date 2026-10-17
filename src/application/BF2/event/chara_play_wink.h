#pragma once
#include "event/i_cmd.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaPlayWink : public ICmd {
public:
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  u32 flags;
  gf::GF_OBJ_HANDLE *handle;
  u8 _18[0x90 - 0x18];
};

static_assert(sizeof(CharaPlayWink) == 0x90, "");

} // namespace event
