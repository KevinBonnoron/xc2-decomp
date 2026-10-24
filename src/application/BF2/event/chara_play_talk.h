#pragma once
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
  virtual RESULT update(const Param &param);
  virtual void term();
  void render(const mm::Vec3 &position, f32 eyeOffset);

  bool isManual() const { return (unknown08 & FLAG_MANUAL) != 0; }

private:
  u32 unknown08;                // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  u8 _18[0x78 - 0x18];
};

static_assert(sizeof(CharaPlayTalk) == 0x78, "");

} // namespace event
