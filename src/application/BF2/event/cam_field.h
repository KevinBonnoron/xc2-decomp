#pragma once
#include "event/cam_base.h"

namespace event {

class CamField : public CamBase {
public:
  CamField(bool isFocal);
  virtual ~CamField() {}
  virtual void update(const FrameInfo &info);
};

static_assert(sizeof(CamField) == 0x40, "");

} // namespace event
