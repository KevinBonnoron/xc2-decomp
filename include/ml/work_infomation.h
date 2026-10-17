#pragma once
#include "ml/dev_perf.h"

namespace ml {

class IWorkInfomation {
public:
  virtual ~IWorkInfomation() {}
  virtual void changeOperationMode(DevPerfOperationMode mode) = 0;
  virtual void changePerformanceMode(DevPerfMode mode) = 0;
  virtual void resumeApplication() = 0;
};

} // namespace ml
