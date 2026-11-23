#pragma once
#include "event/anm_vec.h"
#include "event/i_cmd.h"

namespace event {

class CharaDysUpdater;

class CharaLinerRot : public ICmd {
public:
  virtual RESULT update(const Param &param);

private:
  CharaDysUpdater *m_charaDysUpdater; // Inferred role: dys updater; original member name unknown.
  AnmVec m_anmVec;                    // Inferred role: anm; original member name unknown.
};

static_assert(sizeof(CharaLinerRot) == 0x200, "");

} // namespace event
