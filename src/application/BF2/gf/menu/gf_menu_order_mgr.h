#pragma once
#include "types.h"

namespace ui {
struct EventData;
} // namespace ui

namespace gf {

class GfMenuOrderMgr {
public:
  static void setOrder(int order, u32 handle, const ui::EventData &event);
  static void cancelOrder(int order);
};

} // namespace gf
