#pragma once
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ui {

struct EventData;

class UIObjectListener : public mm::mtl::ReferenceObject {
public:
  virtual void reciveEvent(const EventData &event, u32 handle);
};

class UIGameListener {
public:
  virtual void reciveEvent(const EventData &event, u32 handle) = 0;
};

} // namespace ui
