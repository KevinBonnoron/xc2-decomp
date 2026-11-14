#include "event/cmd_variable.h"

namespace event {

CmdVariable::CmdVariable() : unknown08(VARIABLE_TYPE_UNKNOWN_0) { unknown10.integer = 0; }

CmdVariable::~CmdVariable() {}

void CmdVariable::clear() { unknown08 = VARIABLE_TYPE_UNKNOWN_0; }

void CmdVariable::setS32(s32 value) {
  unknown08 = VARIABLE_TYPE_UNKNOWN_1;
  this->unknown10.integer = value;
}

s32 CmdVariable::getS32() const {
  if (unknown08 == VARIABLE_TYPE_UNKNOWN_2) {
    return unknown10.real;
  }
  return unknown10.integer;
}

void CmdVariable::setF32(f32 value) {
  unknown08 = VARIABLE_TYPE_UNKNOWN_2;
  this->unknown10.real = value;
}

f32 CmdVariable::getF32() const {
  if (unknown08 == VARIABLE_TYPE_UNKNOWN_1) {
    return unknown10.integer;
  }
  return unknown10.real;
}

void CmdVariable::setBool(bool value) {
  unknown08 = VARIABLE_TYPE_UNKNOWN_3;
  this->unknown10.boolean = value;
}

bool CmdVariable::getBool() const { return unknown10.boolean; }

void CmdVariable::setStr(const char *value) {
  unknown08 = VARIABLE_TYPE_UNKNOWN_4;
  this->unknown10.string = value;
}

const char *CmdVariable::getStr() const { return unknown10.string; }

void CmdVariable::setUserdata(void *value) {
  unknown08 = VARIABLE_TYPE_UNKNOWN_5;
  this->unknown10.userdata = value;
}

void *CmdVariable::getUserdata() const { return unknown10.userdata; }

} // namespace event
