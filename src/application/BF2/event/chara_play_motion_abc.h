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

class CharaPlayMotionABC : public ICmd {
public:
  CharaPlayMotionABC();
  bool has(unsigned int index) const;
  virtual RESULT update(const Param &param);
  virtual void term();
  void stopMotion(gf::GfObj *obj);
  void render(const mm::Vec3 &position, f32 eyeOffset);

private:
  u32 unknown08; // Inferred role: flags; original member name unknown.
  u32 _0c;
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  CharaIKUpdater *unknown18;    // Inferred role: ik; original member name unknown.
  CharaDysUpdater *unknown20;   // Inferred role: dys; original member name unknown.
  s32 unknown28;                // Role and original member name unknown.
  f32 unknown2c;                // Role and original member name unknown.
  u8 _30[0x34 - 0x30];
  s32 unknown34[3];         // Inferred role: motion ids; original member name unknown.
  const char *unknown40[3]; // Inferred role: motion names; original member name unknown.
  f32 unknown58;            // Role and original member name unknown.
  f32 unknown5c;            // Role and original member name unknown.
  u64 unknown60;            // Role and original member name unknown.
  f32 unknown68;            // Role and original member name unknown.
  f32 unknown6c;            // Role and original member name unknown.
  f32 unknown70;            // Role and original member name unknown.
  f32 unknown74;            // Role and original member name unknown.
  f32 unknown78;            // Role and original member name unknown.
  f32 unknown7c;            // Role and original member name unknown.

  friend struct CharaPlayMotionABCLayout;
};

struct CharaPlayMotionABCLayout {
  static_assert(offsetof(CharaPlayMotionABC, unknown18) == 0x18, "");
  static_assert(offsetof(CharaPlayMotionABC, unknown20) == 0x20, "");
  static_assert(offsetof(CharaPlayMotionABC, unknown28) == 0x28, "");
  static_assert(offsetof(CharaPlayMotionABC, unknown2c) == 0x2c, "");
  static_assert(offsetof(CharaPlayMotionABC, unknown34) == 0x34, "");
  static_assert(offsetof(CharaPlayMotionABC, unknown40) == 0x40, "");
  static_assert(offsetof(CharaPlayMotionABC, unknown58) == 0x58, "");
  static_assert(offsetof(CharaPlayMotionABC, unknown60) == 0x60, "");
  static_assert(offsetof(CharaPlayMotionABC, unknown68) == 0x68, "");
  static_assert(offsetof(CharaPlayMotionABC, unknown7c) == 0x7c, "");
  static_assert(sizeof(CharaPlayMotionABC) == 0x80, "");
};

} // namespace event
