#include "event/param_variable.h"

#include "mm_mtl/fixstr.h"

namespace event {

ParamVariable::ParamVariable() : mType(VARIABLE_TYPE_NONE) { value.integer = 0; }

ParamVariable::~ParamVariable() {}

void ParamVariable::clear() { mType = VARIABLE_TYPE_NONE; }

void ParamVariable::setS32(s32 value) {
  mType = VARIABLE_TYPE_S32;
  this->value.integer = value;
}

s32 ParamVariable::getS32() const {
  if (mType == VARIABLE_TYPE_F32) {
    return value.real;
  }
  return value.integer;
}

void ParamVariable::setF32(f32 value) {
  mType = VARIABLE_TYPE_F32;
  this->value.real = value;
}

f32 ParamVariable::getF32() const {
  if (mType == VARIABLE_TYPE_S32) {
    return value.integer;
  }
  return value.real;
}

void ParamVariable::setBool(bool value) {
  mType = VARIABLE_TYPE_BOOL;
  this->value.boolean = value;
}

bool ParamVariable::getBool() const { return value.boolean; }

void ParamVariable::setStr(const char *value) {
  mType = VARIABLE_TYPE_STR;
  this->value.string = value;
}

const char *ParamVariable::getStr() const { return value.string; }

void ParamVariable::setUserdata(void *value) {
  mType = VARIABLE_TYPE_USERDATA;
  this->value.userdata = value;
}

void *ParamVariable::getUserdata() const { return value.userdata; }

void ParamVariable::createString(mm::mtl::FixStr<256> &string) {
  string = "";
  switch (mType) {
  case VARIABLE_TYPE_S32:
    string.format("%d", value.integer);
    break;
  case VARIABLE_TYPE_F32:
    string.format("%f", value.integer);
    break;
  case VARIABLE_TYPE_BOOL:
    string = value.boolean ? "true" : "false";
    break;
  case VARIABLE_TYPE_STR:
    string = value.string;
    break;
  case VARIABLE_TYPE_USERDATA:
    string.format("%lld", value.userdata);
    break;
  default:
    break;
  }
}

} // namespace event
