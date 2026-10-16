#pragma once
#include "event/param_variable2.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class Param2 {
public:
  static constexpr u32 VARIABLE_COUNT = 10;

  Param2();
  virtual ~Param2() {}
  void clear();
  ParamVariable2 &val(u32 index);
  const ParamVariable2 &val(u32 index) const;
  void createString(mm::mtl::FixStr<256> &string);

private:
  ParamVariable2 mVariables[VARIABLE_COUNT];
};

static_assert(sizeof(Param2) == 0xaa8, "");

} // namespace event
