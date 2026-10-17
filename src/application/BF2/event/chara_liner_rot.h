#pragma once
#include "event/anm_vec.h"
#include "event/i_cmd.h"

namespace event {

class CharaDysUpdater;

class CharaLinerRot : public ICmd {
public:
  virtual RESULT update(const Param &param);

private:
  CharaDysUpdater *dysUpdater;
  AnmVec anm;
};

static_assert(sizeof(CharaLinerRot) == 0x200, "");

} // namespace event
