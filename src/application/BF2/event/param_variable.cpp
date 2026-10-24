#include "event/param_variable.h"

#include "mm_mtl/fixstr.h"

namespace event {

ParamVariable::ParamVariable() : unknown08(VARIABLE_TYPE_NONE) { unknown10.integer = 0; }

ParamVariable::~ParamVariable() {}

void ParamVariable::clear() { unknown08 = VARIABLE_TYPE_NONE; }

void ParamVariable::setS32(s32 value) {
  unknown08 = VARIABLE_TYPE_S32;
  this->unknown10.integer = value;
}

s32 ParamVariable::getS32() const {
  if (unknown08 == VARIABLE_TYPE_F32) {
    return unknown10.real;
  }
  return unknown10.integer;
}

void ParamVariable::setF32(f32 value) {
  unknown08 = VARIABLE_TYPE_F32;
  this->unknown10.real = value;
}

f32 ParamVariable::getF32() const {
  if (unknown08 == VARIABLE_TYPE_S32) {
    return unknown10.integer;
  }
  return unknown10.real;
}

void ParamVariable::setBool(bool value) {
  unknown08 = VARIABLE_TYPE_BOOL;
  this->unknown10.boolean = value;
}

bool ParamVariable::getBool() const { return unknown10.boolean; }

void ParamVariable::setStr(const char *value) {
  unknown08 = VARIABLE_TYPE_STR;
  this->unknown10.string = value;
}

const char *ParamVariable::getStr() const { return unknown10.string; }

void ParamVariable::setUserdata(void *value) {
  unknown08 = VARIABLE_TYPE_USERDATA;
  this->unknown10.userdata = value;
}

void *ParamVariable::getUserdata() const { return unknown10.userdata; }

void ParamVariable::createString(mm::mtl::FixStr<256> &string) {
  string = "";
  switch (unknown08) {
  case VARIABLE_TYPE_S32:
    string.format("%d", unknown10.integer);
    break;
  case VARIABLE_TYPE_F32:
    string.format("%f", unknown10.integer);
    break;
  case VARIABLE_TYPE_BOOL:
    string = unknown10.boolean ? "true" : "false";
    break;
  case VARIABLE_TYPE_STR:
    string = unknown10.string;
    break;
  case VARIABLE_TYPE_USERDATA:
    string.format("%lld", unknown10.userdata);
    break;
  default:
    break;
  }
}

} // namespace event
