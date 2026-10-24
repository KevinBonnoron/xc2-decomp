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
  gf::GfEvtModel *unknown08;  // Inferred role: model; original member name unknown.
  gf::GfEvtModel *unknown10;  // Inferred role: parent; original member name unknown.
  CharaDysUpdater *unknown18; // Inferred role: dys updater; original member name unknown.
  mm::Vec3 unknown20;         // Inferred role: position; original member name unknown.
  mm::Quat unknown30;         // Inferred role: rotation; original member name unknown.
};

static_assert(sizeof(CharaMount) == 0x40, "");

} // namespace event
