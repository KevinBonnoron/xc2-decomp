#pragma once
#include "mm_mtl/singleton.h"

namespace ml {

class MicroThread : public mm::mtl::PtrSingleton<MicroThread> {
public:
  void sleep(unsigned int frame, bool isWait);
};

} // namespace ml
