#pragma once
#include "ml/work_obj.h"
#include "types.h"

namespace ml {

class DevBase : public WorkObj {
public:
  ~DevBase() override {}

  u8 _1a8[0x1ac - 0x1a8];
};

} // namespace ml
