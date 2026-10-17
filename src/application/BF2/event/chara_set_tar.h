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

  const mm::Vec3 &getTar() const { return tar; }

private:
  u32 flags;
  gf::GF_OBJ_HANDLE *handle;
  u8 _18[0x60 - 0x18];
  TarAxis axis;
  mm::Vec3 tar;
  u8 _90[0xb0 - 0x90];
};

static_assert(sizeof(CharaSetTar) == 0xb0, "");

} // namespace event
