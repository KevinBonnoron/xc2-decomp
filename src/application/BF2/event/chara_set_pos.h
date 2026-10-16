#pragma once
#include "event/i_cmd.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaSetPos : public ICmd {
public:
  virtual RESULT update(const Param &param);

private:
  gf::GF_OBJ_HANDLE *handle;
};

static_assert(sizeof(CharaSetPos) == 0x10, "");

} // namespace event
