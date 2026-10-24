#pragma once
#include "types.h"

namespace event {

enum VARIABLE_TYPE {
  VARIABLE_TYPE_NONE,
  VARIABLE_TYPE_S32,
  VARIABLE_TYPE_F32,
  VARIABLE_TYPE_BOOL,
  VARIABLE_TYPE_STR,
  VARIABLE_TYPE_USERDATA,
};

class CmdVariable {
public:
  CmdVariable();
  virtual ~CmdVariable();
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

private:
  VARIABLE_TYPE unknown08; // Inferred role: type; original member name unknown.
  union {
    s32 integer;
    f32 real;
    bool boolean;
    const char *string;
    void *userdata;
  } unknown10; // Inferred role: value; original member name unknown.
};

static_assert(sizeof(CmdVariable) == 0x18, "");

} // namespace event
