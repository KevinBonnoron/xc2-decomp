#include "event/param2.h"

#include "mm_mtl/fixstr.h"

namespace event {

Param2::Param2() {}

void Param2::clear() {
  for (u32 i = 0; i < VARIABLE_UNKNOWN_10; i++) {
    m_paramVariable2[i].clear();
  }
}

ParamVariable2 &Param2::val(u32 index) { return m_paramVariable2[index]; }

const ParamVariable2 &Param2::val(u32 index) const { return m_paramVariable2[index]; }

void Param2::createString(mm::mtl::FixStr<256> &string) {
  string = "";
  for (u32 i = 0; i < VARIABLE_UNKNOWN_10; i++) {
    mm::mtl::FixStr<256> variable;
    m_paramVariable2[i].createString(variable);
    string += variable.c_str();
    string += " ";
  }
}

} // namespace event
