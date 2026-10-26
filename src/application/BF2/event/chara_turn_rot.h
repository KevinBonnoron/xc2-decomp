#pragma once
#include <stddef.h>

#include "event/i_cmd.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaDysUpdater;

class CharaTurnRot : public ICmd {
public:
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  u32 unknown08;                // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  CharaDysUpdater *unknown18;   // Inferred role: dys; original member name unknown.

  friend struct CharaTurnRotLayout;
};

struct CharaTurnRotLayout {
  static_assert(offsetof(CharaTurnRot, unknown18) == 0x18, "");
  static_assert(sizeof(CharaTurnRot) == 0x20, "");
};

} // namespace event
