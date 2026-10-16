#include "event/cmd_variable.h"

namespace event {

CmdVariable::CmdVariable() : mType(VARIABLE_TYPE_NONE) { value.integer = 0; }

CmdVariable::~CmdVariable() {}

void CmdVariable::clear() { mType = VARIABLE_TYPE_NONE; }

void CmdVariable::setS32(s32 value) {
  mType = VARIABLE_TYPE_S32;
  this->value.integer = value;
}

s32 CmdVariable::getS32() const {
  if (mType == VARIABLE_TYPE_F32) {
    return value.real;
  }
  return value.integer;
}

void CmdVariable::setF32(f32 value) {
  mType = VARIABLE_TYPE_F32;
  this->value.real = value;
}

f32 CmdVariable::getF32() const {
  if (mType == VARIABLE_TYPE_S32) {
    return value.integer;
  }
  return value.real;
}

void CmdVariable::setBool(bool value) {
  mType = VARIABLE_TYPE_BOOL;
  this->value.boolean = value;
}

bool CmdVariable::getBool() const { return value.boolean; }

void CmdVariable::setStr(const char *value) {
  mType = VARIABLE_TYPE_STR;
  this->value.string = value;
}

const char *CmdVariable::getStr() const { return value.string; }

void CmdVariable::setUserdata(void *value) {
  mType = VARIABLE_TYPE_USERDATA;
  this->value.userdata = value;
}

void *CmdVariable::getUserdata() const { return value.userdata; }

} // namespace event
