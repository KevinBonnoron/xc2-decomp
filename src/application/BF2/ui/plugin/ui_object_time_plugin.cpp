#include "ui/plugin/ui_object_time_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectTimePlugin::UIObjectTimePlugin() : unknown80(), unknown90(TIME_TYPE_NONE), unknown92(0) {}

UIObjectTimePlugin::~UIObjectTimePlugin() { ; }

UIObjectTimePlugin *UIObjectTimePlugin::create(u32 handle, u8 type) {
// __LINE__ is the line argument of the operator new call.
#line 46
  UIObjectTimePlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectTimePlugin();
  plugin->addRef();
  UIObjectAcc acc(handle);
  UIObjectTimePlugin *result = nullptr;
  if (type != TIME_TYPE_NONE) {
    result = plugin;
    bool attached = false;
    if (acc.isValid() && acc.isText() && UIObjectPluginUtil::attachPlugin(handle, plugin)) {
      const char *text = acc.getTextPtr();
      if (text != nullptr && checkTimeTextFormat(text, type)) {
        plugin->unknown88 = acc.getTextPtr();
        plugin->unknown90 = type;
        attached = true;
      }
    }
    if (!attached && plugin != nullptr) {
      plugin->release();
      result = nullptr;
    }
  }
  return result;
}

bool UIObjectTimePlugin::checkTimeTextFormat(const char *text, u8 type) {
  switch (type) {
  case TIME_TYPE_DATE:
  case TIME_TYPE_HOUR_MIN_SEC:
  case TIME_TYPE_SEC_MSEC:
  case TIME_TYPE_ELAPSE:
    return UIUtil::checkNumberTextFormat(text, 3);
  case TIME_TYPE_MONTH_DAY:
  case TIME_TYPE_MIN_SEC:
  case TIME_TYPE_HOUR_MIN:
    return UIUtil::checkNumberTextFormat(text, 2);
  }
  return false;
}

void UIObjectTimePlugin::setYear(u16 year) {
  if (year > 0x1fff) {
    year = 0x1fff;
  }
  if (unknown80.unknown00_0 != year) {
    unknown80.unknown00_0 = year;
    unknown18 |= true;
  }
}

void UIObjectTimePlugin::setMonth(u8 month) {
  if (month > 12) {
    month = 12;
  }
  if (unknown80.unknown01_5 != month) {
    unknown80.unknown01_5 = month;
    unknown18 |= true;
  }
}

void UIObjectTimePlugin::setDay(u8 day) {
  if (day > 31) {
    day = 31;
  }
  if (unknown80.unknown03_2 != day) {
    unknown80.unknown03_2 = day;
    unknown18 |= true;
  }
}

void UIObjectTimePlugin::setHour(u8 hour) {
  if (hour > 99) {
    hour = 99;
  }
  if (unknown80.unknown03_7 != hour) {
    unknown80.unknown03_7 = hour;
    unknown18 |= true;
  }
}

void UIObjectTimePlugin::setMin(u8 minute) {
  if (minute > 59) {
    minute = 59;
  }
  if (unknown80.unknown04_6 != minute) {
    unknown80.unknown04_6 = minute;
    unknown18 |= true;
  }
}

void UIObjectTimePlugin::setSec(u8 second) {
  if (second > 59) {
    second = 59;
  }
  if (unknown80.unknown05_5 != second) {
    unknown80.unknown05_5 = second;
    unknown18 |= true;
  }
}

void UIObjectTimePlugin::setMSec(u8 millisecond) {
  if (millisecond > 99) {
    millisecond = 99;
  }
  if (unknown80.unknown06_3 != millisecond) {
    unknown80.unknown06_3 = millisecond;
    unknown18 |= true;
  }
}

void UIObjectTimePlugin::setElapseHour(u16 hour) {
  if (hour > 999) {
    hour = 999;
  }
  if (unknown92 != hour) {
    unknown92 = hour;
    unknown18 |= true;
  }
}

void UIObjectTimePlugin::reload(UIObjectAcc &acc) {
  unknown88 = acc.getTextPtr();
  if (!checkTimeTextFormat(unknown88, unknown90)) {
    unknown88 = nullptr;
  }
  unknown18 |= true;
}

const mm::mtl::RTTI *UIObjectTimePlugin::getRTTI() const { return &m_rtti; }

} // namespace ui
