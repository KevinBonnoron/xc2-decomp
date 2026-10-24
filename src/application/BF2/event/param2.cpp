#include "event/param2.h"

#include "mm_mtl/fixstr.h"

namespace event {

Param2::Param2() {}

void Param2::clear() {
  for (u32 i = 0; i < VARIABLE_COUNT; i++) {
    unknown08[i].clear();
  }
}

ParamVariable2 &Param2::val(u32 index) { return unknown08[index]; }

const ParamVariable2 &Param2::val(u32 index) const { return unknown08[index]; }

void Param2::createString(mm::mtl::FixStr<256> &string) {
  string = "";
  for (u32 i = 0; i < VARIABLE_COUNT; i++) {
    mm::mtl::FixStr<256> variable;
    unknown08[i].createString(variable);
    string += variable.c_str();
    string += " ";
  }
}

} // namespace event
