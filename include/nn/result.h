#pragma once
#include "types.h"

namespace nn {

class Result {
public:
  bool IsSuccess() const { return value == 0; }

private:
  u32 value;
};

} // namespace nn
