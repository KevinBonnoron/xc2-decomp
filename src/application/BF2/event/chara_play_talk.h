#pragma once
#include <stddef.h>

#include "event/i_cmd.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf
namespace mm {
struct Vec3;
}

namespace event {

class CharaPlayTalk : public ICmd {
public:
  enum {
    FLAG_PLAY = 1 << 0,
    FLAG_LOOP = 1 << 1,
    FLAG_MANUAL = 1 << 3,
  };

  virtual void init();
  void idle();
  virtual RESULT update(const Param &param);
  virtual void term();
  void render(const mm::Vec3 &position, f32 eyeOffset);

  bool isManual() const { return (unknown08 & FLAG_MANUAL) != 0; }

private:
  u32 unknown08;                // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  u8 _18[0x68 - 0x18];
  f32 unknown68; // Role and original member name unknown.
  f32 unknown6c; // Role and original member name unknown.
  f32 unknown70; // Role and original member name unknown.
  f32 unknown74; // Role and original member name unknown.

  friend struct CharaPlayTalkLayout;
};

struct CharaPlayTalkLayout {
  static_assert(offsetof(CharaPlayTalk, unknown68) == 0x68, "");
  static_assert(offsetof(CharaPlayTalk, unknown74) == 0x74, "");
  static_assert(sizeof(CharaPlayTalk) == 0x78, "");
};

} // namespace event
