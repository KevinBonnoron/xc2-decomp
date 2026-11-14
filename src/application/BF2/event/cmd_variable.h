#pragma once
#include "types.h"

namespace event {

enum VARIABLE_TYPE {
  VARIABLE_TYPE_UNKNOWN_0, // Inferred role: none; original name unknown.
  VARIABLE_TYPE_UNKNOWN_1, // Inferred role: s32; original name unknown.
  VARIABLE_TYPE_UNKNOWN_2, // Inferred role: f32; original name unknown.
  VARIABLE_TYPE_UNKNOWN_3, // Inferred role: bool; original name unknown.
  VARIABLE_TYPE_UNKNOWN_4, // Inferred role: str; original name unknown.
  VARIABLE_TYPE_UNKNOWN_5, // Inferred role: userdata; original name unknown.
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
