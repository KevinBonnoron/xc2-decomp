#pragma once
#include "event/param_variable.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class Param {
public:
  static constexpr u32 VARIABLE_COUNT = 10;

  Param();
  virtual ~Param() {}
  void clear();
  ParamVariable &val(u32 index);
  const ParamVariable &val(u32 index) const;
  void createString(mm::mtl::FixStr<256> &string);

private:
  ParamVariable unknown08[VARIABLE_COUNT]; // Inferred role: variables; original member name unknown.
};

static_assert(sizeof(Param) == 0xf8, "");

} // namespace event
