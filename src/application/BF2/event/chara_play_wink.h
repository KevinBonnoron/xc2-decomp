#pragma once
#include <stddef.h>

#include "event/i_cmd.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaLensPlayer;
class CharaPlayFacial;
class CharaWinkPlayer;
class IAttachActor;
class ObjectChara;

class CharaPlayWink : public ICmd {
public:
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: manual lens flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: play flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: loop flag; original name unknown.
  };

  virtual void init();
  void update();
  void idle();
  virtual RESULT update(const Param &param);
  virtual void term();
  void render(const mm::Vec3 &position, f32 eyeOffset);

private:
  mm::Vec2 calcLensXYFromTarAxis(const mm::Vec3 &target);

  u32 unknown08;                // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  CharaPlayFacial *unknown18;   // Inferred role: facial; original member name unknown.
  CharaWinkPlayer *unknown20;   // Inferred role: wink player; original member name unknown.
  CharaLensPlayer *unknown28;   // Inferred role: lens player; original member name unknown.
  IAttachActor *unknown30;      // Inferred role: attach actor; original member name unknown.
  mm::Vec3 unknown40;           // Inferred role: lens direction; original member name unknown.
  mm::Vec3 unknown50;           // Inferred role: head position; original member name unknown.
  f32 unknown60;                // Inferred role: life; original member name unknown.
  const char *unknown68;        // Inferred role: bdat name; original member name unknown.
  mm::Vec2 unknown70;           // Inferred role: lens; original member name unknown.
  ObjectChara *unknown80;       // Inferred role: target; original member name unknown.

  friend struct CharaPlayWinkLayout;
};

struct CharaPlayWinkLayout {
  static_assert(offsetof(CharaPlayWink, unknown18) == 0x18, "");
  static_assert(offsetof(CharaPlayWink, unknown20) == 0x20, "");
  static_assert(offsetof(CharaPlayWink, unknown28) == 0x28, "");
  static_assert(offsetof(CharaPlayWink, unknown30) == 0x30, "");
  static_assert(offsetof(CharaPlayWink, unknown40) == 0x40, "");
  static_assert(offsetof(CharaPlayWink, unknown50) == 0x50, "");
  static_assert(offsetof(CharaPlayWink, unknown60) == 0x60, "");
  static_assert(offsetof(CharaPlayWink, unknown68) == 0x68, "");
  static_assert(offsetof(CharaPlayWink, unknown70) == 0x70, "");
  static_assert(offsetof(CharaPlayWink, unknown80) == 0x80, "");
  static_assert(sizeof(CharaPlayWink) == 0x90, "");
};

} // namespace event
