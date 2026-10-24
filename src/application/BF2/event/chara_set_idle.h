#pragma once
#include "event/i_cmd.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaDysUpdater;

class CharaSetIdle : public ICmd {
public:
  static const char *type2stat(int type);
  static const char *type2name(int type);
  virtual void init();
  virtual RESULT update(const Param &param);

  int getType() const { return unknown20; }

private:
  u32 unknown08;                // Inferred role: step; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  CharaDysUpdater *unknown18;   // Inferred role: dys; original member name unknown.
  int unknown20;                // Inferred role: type; original member name unknown.
};

static_assert(sizeof(CharaSetIdle) == 0x28, "");

} // namespace event
