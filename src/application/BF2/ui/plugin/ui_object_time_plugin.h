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
  u64 year : 13;
  u64 month : 4;
  u64 : 9;
  u64 day : 5;
  u64 hour : 7;
  u64 minute : 7;
  u64 second : 6;
  u64 millisecond : 10;
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

  uiDateTime time;
  const char *format;
  u8 type;
  u16 elapseHour;
};

static_assert(offsetof(UIObjectTimePlugin, time) == 0x80, "");
static_assert(offsetof(UIObjectTimePlugin, format) == 0x88, "");
static_assert(offsetof(UIObjectTimePlugin, type) == 0x90, "");
static_assert(offsetof(UIObjectTimePlugin, elapseHour) == 0x92, "");
static_assert(sizeof(UIObjectTimePlugin) == 0x98, "");

} // namespace ui
