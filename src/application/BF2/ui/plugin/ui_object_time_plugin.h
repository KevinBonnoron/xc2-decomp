#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/plugin/ui_object_disp_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

struct uiDateTime {
  u64 unknown00_0 : 13; // Inferred role: year; original member name unknown.
  u64 unknown01_5 : 4;  // Inferred role: month; original member name unknown.
  u64 : 9;
  u64 unknown03_2 : 5;  // Inferred role: day; original member name unknown.
  u64 unknown03_7 : 7;  // Inferred role: hour; original member name unknown.
  u64 unknown04_6 : 7;  // Inferred role: minute; original member name unknown.
  u64 unknown05_5 : 6;  // Inferred role: second; original member name unknown.
  u64 unknown06_3 : 10; // Inferred role: millisecond; original member name unknown.
};

static_assert(sizeof(uiDateTime) == 8, "");

class UIObjectTimePlugin : public UIObjectDispPlugin {
public:
  enum TimeType {
    TIME_TYPE_NONE = 0,
    TIME_TYPE_DATE = 1,
    TIME_TYPE_MONTH_DAY = 2,
    TIME_TYPE_HOUR_MIN_SEC = 3,
    TIME_TYPE_MIN_SEC = 4,
    TIME_TYPE_SEC_MSEC = 5,
    TIME_TYPE_HOUR_MIN = 6,
    TIME_TYPE_ELAPSE = 7,
  };

  static mm::mtl::RTTI m_rtti;

  UIObjectTimePlugin();
  virtual ~UIObjectTimePlugin();
  static UIObjectTimePlugin *create(u32 handle, u8 type);
  static bool checkTimeTextFormat(const char *text, u8 type);
  void setYear(u16 year);
  void setMonth(u8 month);
  void setDay(u8 day);
  void setHour(u8 hour);
  void setMin(u8 minute);
  void setSec(u8 second);
  void setMSec(u8 millisecond);
  void setElapseHour(u16 hour);
  virtual void reload(UIObjectAcc &acc);
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;

  uiDateTime unknown80;  // Inferred role: time; original member name unknown.
  const char *unknown88; // Inferred role: format; original member name unknown.
  u8 unknown90;          // Inferred role: type; original member name unknown.
  u16 unknown92;         // Inferred role: elapse hour; original member name unknown.
};

static_assert(offsetof(UIObjectTimePlugin, unknown80) == 0x80, "");
static_assert(offsetof(UIObjectTimePlugin, unknown88) == 0x88, "");
static_assert(offsetof(UIObjectTimePlugin, unknown90) == 0x90, "");
static_assert(offsetof(UIObjectTimePlugin, unknown92) == 0x92, "");
static_assert(sizeof(UIObjectTimePlugin) == 0x98, "");

} // namespace ui
