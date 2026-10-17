#pragma once
#include "types.h"

namespace ptlib {
namespace emitter {

class ComputeManager {
public:
  static ComputeManager *&getPtr();
  void resetUpdate();
  void update(u32 viewIndex);
};

} // namespace emitter
} // namespace ptlib
