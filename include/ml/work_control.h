#pragma once
#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"

namespace ml {
class CriticalSection;

class WorkControl : public WorkObj, public mm::mtl::PtrSingleton<WorkControl> {
public:
  ~WorkControl() override;
  void wkTail() override;
  static bool hasFlow();
  static CriticalSection &getCriticalSection();
};

} // namespace ml
