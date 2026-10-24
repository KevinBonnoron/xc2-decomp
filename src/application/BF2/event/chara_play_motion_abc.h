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

class CharaPlayMotionABC : public ICmd {
public:
  CharaPlayMotionABC();
  virtual RESULT update(const Param &param);
  virtual void term();
  void render(const mm::Vec3 &position, f32 eyeOffset);

private:
  u32 unknown08;                // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  u8 _18[0x80 - 0x18];
};

static_assert(sizeof(CharaPlayMotionABC) == 0x80, "");

} // namespace event
