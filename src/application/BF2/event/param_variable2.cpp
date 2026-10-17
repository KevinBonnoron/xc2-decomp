#include "event/param_variable2.h"

#include <stdlib.h>

namespace event {

ParamVariable2::ParamVariable2() {}

ParamVariable2::~ParamVariable2() {}

void ParamVariable2::clear() { value = ""; }

void ParamVariable2::setS32(s32 value) { this->value.format("%d", value); }

s32 ParamVariable2::getS32() const { return atoi(value.c_str()); }

void ParamVariable2::setF32(f32 value) { this->value.format("%f", value); }

f32 ParamVariable2::getF32() const { return atof(value.c_str()); }

void ParamVariable2::setBool(bool value) { this->value = value ? "true" : "false"; }

bool ParamVariable2::getBool() const { return __builtin_strcmp(value.c_str(), "true") == 0; }

void ParamVariable2::setStr(const char *value) { this->value = value; }

const char *ParamVariable2::getStr() const { return value.c_str(); }

void ParamVariable2::setUserdata(void *value) { this->value.format("%lld", value); }

void *ParamVariable2::getUserdata() const { return reinterpret_cast<void *>(static_cast<s64>(atoi(value.c_str()))); }

void ParamVariable2::createString(mm::mtl::FixStr<256> &string) { string = value.c_str(); }

} // namespace event
