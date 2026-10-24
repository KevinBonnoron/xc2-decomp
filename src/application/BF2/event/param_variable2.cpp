#include "event/param_variable2.h"

#include <stdlib.h>

namespace event {

ParamVariable2::ParamVariable2() {}

ParamVariable2::~ParamVariable2() {}

void ParamVariable2::clear() { m_str = ""; }

void ParamVariable2::setS32(s32 value) { this->m_str.format("%d", value); }

s32 ParamVariable2::getS32() const { return atoi(m_str.c_str()); }

void ParamVariable2::setF32(f32 value) { this->m_str.format("%f", value); }

f32 ParamVariable2::getF32() const { return atof(m_str.c_str()); }

void ParamVariable2::setBool(bool value) { this->m_str = value ? "true" : "false"; }

bool ParamVariable2::getBool() const { return __builtin_strcmp(m_str.c_str(), "true") == 0; }

void ParamVariable2::setStr(const char *value) { this->m_str = value; }

const char *ParamVariable2::getStr() const { return m_str.c_str(); }

void ParamVariable2::setUserdata(void *value) { this->m_str.format("%lld", value); }

void *ParamVariable2::getUserdata() const { return reinterpret_cast<void *>(static_cast<s64>(atoi(m_str.c_str()))); }

void ParamVariable2::createString(mm::mtl::FixStr<256> &string) { string = m_str.c_str(); }

} // namespace event
