#pragma once
#include "event/i_cmd.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {
class GfEvtModel;
} // namespace gf

namespace event {

class CharaDysUpdater;

class CharaMount : public ICmd {
public:
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  gf::GfEvtModel *model;
  gf::GfEvtModel *parent;
  CharaDysUpdater *dysUpdater;
  mm::Vec3 position;
  mm::Quat rotation;
};

static_assert(sizeof(CharaMount) == 0x40, "");

} // namespace event
