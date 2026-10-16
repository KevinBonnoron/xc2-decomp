#include "event/param.h"

#include "mm_mtl/fixstr.h"

namespace event {

Param::Param() {}

void Param::clear() {
  for (u32 i = 0; i < VARIABLE_COUNT; i++) {
    mVariables[i].clear();
  }
}

ParamVariable &Param::val(u32 index) { return mVariables[index]; }

const ParamVariable &Param::val(u32 index) const { return mVariables[index]; }

void Param::createString(mm::mtl::FixStr<256> &string) {
  string = "";
  for (u32 i = 0; i < VARIABLE_COUNT; i++) {
    mm::mtl::FixStr<256> variable;
    mVariables[i].createString(variable);
    string += variable.c_str();
    string += " ";
  }
}

} // namespace event
