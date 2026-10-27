#pragma once

#include "ml/dev_touch.h"

namespace ml {
class WorkObj;

class DevTouchNx : public DevTouch {
public:
  DevTouchNx(const char *name, WorkObj *parent);
  void updateDevice() override;
  bool createDevice() override;
  void releaseDevice() override;
};

} // namespace ml
