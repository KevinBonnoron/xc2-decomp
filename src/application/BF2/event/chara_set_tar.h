#pragma once
#include "event/i_cmd.h"
#include "event/tar_axis.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaSetTar : public ICmd {
public:
  void idle();
  virtual RESULT update(const Param &param);
  virtual void term();

  const mm::Vec3 &getTar() const { return unknown80; }

private:
  u32 unknown08;                // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  u8 _18[0x60 - 0x18];
  TarAxis unknown60;  // Inferred role: axis; original member name unknown.
  mm::Vec3 unknown80; // Inferred role: tar; original member name unknown.
  u8 _90[0xb0 - 0x90];
};

static_assert(sizeof(CharaSetTar) == 0xb0, "");

} // namespace event
