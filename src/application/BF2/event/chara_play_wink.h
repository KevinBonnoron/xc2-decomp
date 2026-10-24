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

class CharaPlayWink : public ICmd {
public:
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();
  void render(const mm::Vec3 &position, f32 eyeOffset);

private:
  u32 unknown08;                // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  u8 _18[0x90 - 0x18];
};

static_assert(sizeof(CharaPlayWink) == 0x90, "");

} // namespace event
