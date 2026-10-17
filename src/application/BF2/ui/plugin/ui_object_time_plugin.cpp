#include "ui/plugin/ui_object_time_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectTimePlugin::UIObjectTimePlugin() : time(), type(TIME_TYPE_NONE), elapseHour(0) {}

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
        plugin->format = acc.getTextPtr();
        plugin->type = type;
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
  if (time.year != year) {
    time.year = year;
    needUpdate |= true;
  }
}

void UIObjectTimePlugin::setMonth(u8 month) {
  if (month > 12) {
    month = 12;
  }
  if (time.month != month) {
    time.month = month;
    needUpdate |= true;
  }
}

void UIObjectTimePlugin::setDay(u8 day) {
  if (day > 31) {
    day = 31;
  }
  if (time.day != day) {
    time.day = day;
    needUpdate |= true;
  }
}

void UIObjectTimePlugin::setHour(u8 hour) {
  if (hour > 99) {
    hour = 99;
  }
  if (time.hour != hour) {
    time.hour = hour;
    needUpdate |= true;
  }
}

void UIObjectTimePlugin::setMin(u8 minute) {
  if (minute > 59) {
    minute = 59;
  }
  if (time.minute != minute) {
    time.minute = minute;
    needUpdate |= true;
  }
}

void UIObjectTimePlugin::setSec(u8 second) {
  if (second > 59) {
    second = 59;
  }
  if (time.second != second) {
    time.second = second;
    needUpdate |= true;
  }
}

void UIObjectTimePlugin::setMSec(u8 millisecond) {
  if (millisecond > 99) {
    millisecond = 99;
  }
  if (time.millisecond != millisecond) {
    time.millisecond = millisecond;
    needUpdate |= true;
  }
}

void UIObjectTimePlugin::setElapseHour(u16 hour) {
  if (hour > 999) {
    hour = 999;
  }
  if (elapseHour != hour) {
    elapseHour = hour;
    needUpdate |= true;
  }
}

void UIObjectTimePlugin::reload(UIObjectAcc &acc) {
  format = acc.getTextPtr();
  if (!checkTimeTextFormat(format, type)) {
    format = nullptr;
  }
  needUpdate |= true;
}

const mm::mtl::RTTI *UIObjectTimePlugin::getRTTI() const { return &m_rtti; }

} // namespace ui
