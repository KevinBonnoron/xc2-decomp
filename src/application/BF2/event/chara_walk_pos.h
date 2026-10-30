#pragma once
#include <stddef.h>

#include "event/chara_walk_calculator.h"
#include "event/i_cmd.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaDysUpdater;
class CharaIKUpdater;

class CharaWalkPos : public ICmd {
public:
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  gf::GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  CharaIKUpdater *unknown10;    // Inferred role: ik updater; original member name unknown.
  CharaDysUpdater *unknown18;   // Inferred role: dys updater; original member name unknown.
  int unknown20;                // Inferred role: gravity off mode, gravity is restored when 0; original member name unknown.
  u8 _24[0x28 - 0x24];
  int unknown28;                 // Inferred role: walk state, 2 while turning; original member name unknown.
  CharaWalkCalculator unknown30; // Inferred role: calculator; original member name unknown.
  u8 unknownc0[0xd0 - 0xc0];     // Inferred role: c0; original member name unknown.

  friend struct CharaWalkPosLayout;
};

struct CharaWalkPosLayout {
  static_assert(offsetof(CharaWalkPos, unknown10) == 0x10, "");
  static_assert(offsetof(CharaWalkPos, unknown18) == 0x18, "");
  static_assert(offsetof(CharaWalkPos, unknown20) == 0x20, "");
  static_assert(offsetof(CharaWalkPos, unknown28) == 0x28, "");
  static_assert(sizeof(CharaWalkPos) == 0xd0, "");
};

} // namespace event
