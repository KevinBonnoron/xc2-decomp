#include "event/param.h"

#include "mm_mtl/fixstr.h"

namespace event {

Param::Param() {}

void Param::clear() {
  for (u32 i = 0; i < VARIABLE_COUNT; i++) {
    unknown08[i].clear();
  }
}

ParamVariable &Param::val(u32 index) { return unknown08[index]; }

const ParamVariable &Param::val(u32 index) const { return unknown08[index]; }

void Param::createString(mm::mtl::FixStr<256> &string) {
  string = "";
  for (u32 i = 0; i < VARIABLE_COUNT; i++) {
    mm::mtl::FixStr<256> variable;
    unknown08[i].createString(variable);
    string += variable.c_str();
    string += " ";
  }
}

} // namespace event
