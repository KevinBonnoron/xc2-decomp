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

  int getType() const { return mType; }

private:
  u32 mStep;
  gf::GF_OBJ_HANDLE *handle;
  CharaDysUpdater *mDys;
  int mType;
};

static_assert(sizeof(CharaSetIdle) == 0x28, "");

} // namespace event
