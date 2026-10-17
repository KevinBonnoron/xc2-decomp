#pragma once
#include "event/anm_vec.h"
#include "event/i_cmd.h"
#include "types.h"

namespace event {

class CharaDysUpdater;
class CharaIKUpdater;

class CharaLinerPos : public ICmd {
public:
  virtual RESULT update(const Param &param);

private:
  CharaIKUpdater *ikUpdater;
  CharaDysUpdater *dysUpdater;
  u32 offscrId;
  AnmVec anm;
};

static_assert(sizeof(CharaLinerPos) == 0x210, "");

} // namespace event
