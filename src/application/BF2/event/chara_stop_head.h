#pragma once
#include "event/i_cmd.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaStopHead : public ICmd {
public:
  virtual RESULT update(const Param &param);

private:
  gf::GF_OBJ_HANDLE *handle;
  u8 _10[0x18 - 0x10];
};

static_assert(sizeof(CharaStopHead) == 0x18, "");

} // namespace event
