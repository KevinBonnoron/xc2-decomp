#pragma once
#include "types.h"
#include "ui/plugin/ui_object_disp_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

struct uiDateTime {
  u64 year : 13;
  u64 month : 4;
  u64 : 9;
  u64 day : 5;
  u64 hour : 7;
  u64 minute : 7;
  u64 second : 6;
  u64 millisecond : 13;
};

static_assert(sizeof(uiDateTime) == 8, "");

class UIObjectTimePlugin : public UIObjectDispPlugin {
public:
  static mm::mtl::RTTI m_rtti;

  static UIObjectTimePlugin *create(u32 handle, u8 format);
  void setYear(u16 year);
  void setMonth(u8 month);
  void setDay(u8 day);
  void setHour(u8 hour);
  void setMin(u8 minute);
  void setSec(u8 second);
  void setMSec(u8 millisecond);
  void setElapseHour(u16 hour);
};

} // namespace ui
