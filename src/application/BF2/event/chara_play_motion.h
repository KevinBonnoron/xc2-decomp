#pragma once
#include <stddef.h>

#include "event/i_cmd.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
class GfObj;
} // namespace gf
namespace mm {
struct Vec3;
}

namespace event {

class CharaDysUpdater;
class CharaIKUpdater;

class CharaPlayMotion : public ICmd {
public:
  CharaPlayMotion();
  virtual RESULT update(const Param &param);
  virtual void term();
  void play(gf::GfObj *obj, void *motion, u64 size, f32 time);
  void stop(gf::GfObj *obj);
  void render(const mm::Vec3 &position, f32 eyeOffset);

private:
  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
  // Sets or clears flag bits. CharaPlayMotion::update (1.0.0: 0x71000d132c, 469 instructions) stores the flags with bit 1 set (0x71000d1854), then keeps a branch on the life (b.ls at 0x71000d1858)
  // with an and arm and an orr arm and stores the flags again (0x71000d186c): the arms were calls when the branch was first simplified.
  // Forms tried without the helper, written in update after unknown08 |= 2, all 464 instructions (a csel, one store): if (life <= 0.0f) unknown08 |= 8; else unknown08 &= ~8, the same with
  // unknown08 = unknown08 | 8, with the test negated, with the arms swapped, a ternary, and one if/else setting both bits in each arm; two tests (life <= 0.0f, then life > 0.0f) give 469
  // instructions that differ. A set helper and a clear helper called in the arms match too, with one of the two alone as well. The name and the shape are those of the helper of the sibling event
  // classes (SeObj::setFlag in se_obj.h, CharaWpnAsm::setFlag in chara_wpn_asm.h), which is why the bool form is kept over the set and clear pair.
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown08 |= flag;
    } else {
      unknown08 &= ~flag;
    }
  }

  u32 unknown08; // Inferred role: flags; original member name unknown.
  u32 _0c;
  gf::GF_OBJ_HANDLE *unknown10;       // Inferred role: handle; original member name unknown.
  CharaIKUpdater *m_charaIKUpdater;   // Inferred role: ik; original member name unknown.
  CharaDysUpdater *m_charaDysUpdater; // Inferred role: dys; original member name unknown.
  void *unknown28;                    // Inferred role: stream data; original member name unknown.
  u64 unknown30;                      // Role and original member name unknown.
  f32 unknown38;                      // Role and original member name unknown.
  f32 unknown3c;                      // Role and original member name unknown.
  f32 unknown40;                      // Role and original member name unknown.
  u8 _44[0x48 - 0x44];
  const char *unknown48; // Inferred role: motion name; original member name unknown.

  friend struct CharaPlayMotionLayout;
};

struct CharaPlayMotionLayout {
  static_assert(offsetof(CharaPlayMotion, m_charaIKUpdater) == 0x18, "");
  static_assert(offsetof(CharaPlayMotion, m_charaDysUpdater) == 0x20, "");
  static_assert(offsetof(CharaPlayMotion, unknown28) == 0x28, "");
  static_assert(offsetof(CharaPlayMotion, unknown30) == 0x30, "");
  static_assert(offsetof(CharaPlayMotion, unknown3c) == 0x3c, "");
  static_assert(offsetof(CharaPlayMotion, unknown40) == 0x40, "");
  static_assert(sizeof(CharaPlayMotion) == 0x50, "");
};

} // namespace event
