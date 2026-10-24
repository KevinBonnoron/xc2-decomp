#pragma once
#include "event/anm_vec.h"
#include "event/i_cmd.h"

namespace event {

class CharaDysUpdater;

class CharaLinerRot : public ICmd {
public:
  virtual RESULT update(const Param &param);

private:
  CharaDysUpdater *unknown08; // Inferred role: dys updater; original member name unknown.
  AnmVec unknown10;           // Inferred role: anm; original member name unknown.
};

static_assert(sizeof(CharaLinerRot) == 0x200, "");

} // namespace event
