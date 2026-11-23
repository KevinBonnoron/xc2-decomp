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
  CharaIKUpdater *m_charaIKUpdater;   // Inferred role: ik updater; original member name unknown.
  CharaDysUpdater *m_charaDysUpdater; // Inferred role: dys updater; original member name unknown.
  u32 unknown18;                      // Inferred role: offscr id; original member name unknown.
  AnmVec m_anmVec;                    // Inferred role: anm; original member name unknown.
};

static_assert(sizeof(CharaLinerPos) == 0x210, "");

} // namespace event
