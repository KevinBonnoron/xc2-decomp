#pragma once
#include "types.h"

namespace ml {

class WorkProfiler {
public:
  WorkProfiler();
  virtual ~WorkProfiler();
  void start();
  void stop();
  void heartbeat();

  u64 _08;
  bool _10;
};

} // namespace ml
