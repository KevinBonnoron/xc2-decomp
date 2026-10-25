#pragma once
#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"

namespace ml {

class WorkControl : public WorkObj, public mm::mtl::PtrSingleton<WorkControl> {
public:
  ~WorkControl() override;
  void wkTail() override;
  static bool hasFlow();
};

} // namespace ml
