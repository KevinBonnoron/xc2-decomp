#include "event/param.h"

#include "mm_mtl/fixstr.h"

namespace event {

Param::Param() {}

void Param::clear() {
  for (u32 i = 0; i < VARIABLE_UNKNOWN_10; i++) {
    m_paramVariable[i].clear();
  }
}

ParamVariable &Param::val(u32 index) { return m_paramVariable[index]; }

const ParamVariable &Param::val(u32 index) const { return m_paramVariable[index]; }

void Param::createString(mm::mtl::FixStr<256> &string) {
  string = "";
  for (u32 i = 0; i < VARIABLE_UNKNOWN_10; i++) {
    mm::mtl::FixStr<256> variable;
    m_paramVariable[i].createString(variable);
    string += variable.c_str();
    string += " ";
  }
}

} // namespace event
