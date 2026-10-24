#pragma once
#include "event/i_cmd.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaStopAction : public ICmd {
public:
  virtual RESULT update(const Param &param);

private:
  gf::GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
};

static_assert(sizeof(CharaStopAction) == 0x10, "");

} // namespace event
