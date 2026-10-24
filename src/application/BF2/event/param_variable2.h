#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class ParamVariable2 {
public:
  ParamVariable2();
  virtual ~ParamVariable2();
  void clear();
  void setS32(s32 value);
  s32 getS32() const;
  void setF32(f32 value);
  f32 getF32() const;
  void setBool(bool value);
  bool getBool() const;
  void setStr(const char *value);
  const char *getStr() const;
  void setUserdata(void *value);
  void *getUserdata() const;
  void createString(mm::mtl::FixStr<256> &string);

private:
  mm::mtl::FixStr<256> m_str;
};

static_assert(sizeof(ParamVariable2) == 0x110, "");

} // namespace event
