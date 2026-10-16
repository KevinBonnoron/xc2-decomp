#pragma once
#include "event/cmd_variable.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class ParamVariable {
public:
  ParamVariable();
  virtual ~ParamVariable();
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
  VARIABLE_TYPE mType;
  union {
    s32 integer;
    f32 real;
    bool boolean;
    const char *string;
    void *userdata;
  } value;
};

static_assert(sizeof(ParamVariable) == 0x18, "");

} // namespace event
