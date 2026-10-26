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

class CharaPlayFacial;

class CharaPlayTalk : public ICmd {
public:
  enum {
    FLAG_PLAY = 1 << 0,
    FLAG_LOOP = 1 << 1,
    FLAG_UNKNOWN_2 = 1 << 2, // Role and original name unknown.
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
  CharaPlayFacial *unknown18;   // Role and original member name unknown.
  u8 _20[0x28 - 0x20];
  f32 unknown28; // Role and original member name unknown.
  u8 _2c[0x38 - 0x2c];
  const char *unknown38; // Role and original member name unknown.
  bool unknown40;        // Role and original member name unknown.
  bool unknown41;        // Role and original member name unknown.
  u8 _42[0x44 - 0x42];
  f32 unknown44; // Role and original member name unknown.
  f32 unknown48; // Role and original member name unknown.
  f32 unknown4c; // Role and original member name unknown.
  f32 unknown50; // Role and original member name unknown.
  f32 unknown54; // Role and original member name unknown.
  f32 unknown58; // Role and original member name unknown.
  f32 unknown5c; // Role and original member name unknown.
  f32 unknown60; // Role and original member name unknown.
  f32 unknown64; // Role and original member name unknown.
  f32 unknown68; // Role and original member name unknown.
  f32 unknown6c; // Role and original member name unknown.
  f32 unknown70; // Role and original member name unknown.
  f32 unknown74; // Role and original member name unknown.

  friend struct CharaPlayTalkLayout;
};

struct CharaPlayTalkLayout {
  static_assert(offsetof(CharaPlayTalk, unknown18) == 0x18, "");
  static_assert(offsetof(CharaPlayTalk, unknown28) == 0x28, "");
  static_assert(offsetof(CharaPlayTalk, unknown38) == 0x38, "");
  static_assert(offsetof(CharaPlayTalk, unknown40) == 0x40, "");
  static_assert(offsetof(CharaPlayTalk, unknown44) == 0x44, "");
  static_assert(offsetof(CharaPlayTalk, unknown64) == 0x64, "");
  static_assert(offsetof(CharaPlayTalk, unknown68) == 0x68, "");
  static_assert(offsetof(CharaPlayTalk, unknown74) == 0x74, "");
  static_assert(sizeof(CharaPlayTalk) == 0x78, "");
};

} // namespace event
