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
  u32 flags;
  gf::GF_OBJ_HANDLE *handle;
  u8 _18[0x80 - 0x18];
};

static_assert(sizeof(CharaPlayMotionABC) == 0x80, "");

} // namespace event
