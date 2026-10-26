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
  u32 unknown08; // Inferred role: flags; original member name unknown.
  u32 _0c;
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  CharaIKUpdater *unknown18;    // Inferred role: ik; original member name unknown.
  CharaDysUpdater *unknown20;   // Inferred role: dys; original member name unknown.
  void *unknown28;              // Inferred role: stream data; original member name unknown.
  u64 unknown30;                // Role and original member name unknown.
  f32 unknown38;                // Role and original member name unknown.
  f32 unknown3c;                // Role and original member name unknown.
  f32 unknown40;                // Role and original member name unknown.
  u8 _44[0x50 - 0x44];

  friend struct CharaPlayMotionLayout;
};

struct CharaPlayMotionLayout {
  static_assert(offsetof(CharaPlayMotion, unknown18) == 0x18, "");
  static_assert(offsetof(CharaPlayMotion, unknown20) == 0x20, "");
  static_assert(offsetof(CharaPlayMotion, unknown28) == 0x28, "");
  static_assert(offsetof(CharaPlayMotion, unknown30) == 0x30, "");
  static_assert(offsetof(CharaPlayMotion, unknown3c) == 0x3c, "");
  static_assert(offsetof(CharaPlayMotion, unknown40) == 0x40, "");
  static_assert(sizeof(CharaPlayMotion) == 0x50, "");
};

} // namespace event
