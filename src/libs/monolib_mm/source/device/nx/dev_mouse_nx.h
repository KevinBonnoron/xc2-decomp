#pragma once

#include "ml/dev_mouse.h"

namespace ml {
class WorkObj;

class DevMouseNx : public DevMouse {
public:
  DevMouseNx(const char *name, WorkObj *parent);
  ~DevMouseNx() override;
  void updateDevice() override;
  bool createDevice() override;
  void releaseDevice() override;
};

} // namespace ml
