#include "gf/menu/adapter/gf_menu_adapter.h"

#include "gf/field/gf_field_time.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/rtti.h"
#include "string.h"
#include "ui/plugin/ui_object_color_plugin.h"
#include "ui/plugin/ui_object_disp_plugin.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/plugin/ui_object_offset_plugin.h"
#include "ui/plugin/ui_object_pattern_plugin.h"
#include "ui/plugin/ui_object_pos_plugin.h"
#include "ui/plugin/ui_object_text_plugin.h"
#include "ui/plugin/ui_object_time_plugin.h"
#include "ui/plugin/ui_object_world_pos_plugin.h"
#include "ui/ui_object.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

namespace gf {

GfMenuAdapter::GfMenuAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAfter, bool isUpdateAlways)
    : plugin(nullptr), flags(0), linkedObject(0), rewriteNumber(nullptr) {
  attachPlugin(plugin);
  flags |= FLAG_CHANGED;
  if (isUpdateAlways) {
    flags |= FLAG_UPDATE_ALWAYS;
  }
  GfMenuAdapterManager::get()->addAdapter(this, isUpdateAfter);
}

GfMenuAdapter::~GfMenuAdapter() {
  mm::mtl::safeRelease(plugin);
  mm::mtl::safeRelease(rewriteNumber);
}

void GfMenuAdapter::setChange() {
  flags |= FLAG_CHANGED;
  if (plugin != nullptr) {
    plugin->needUpdate |= 2;
  }
}

void GfMenuAdapter::setUpdateAfter() { GfMenuAdapterManager::get()->setAfterUpdate(this); }

ui::UIObjectPlugin *GfMenuAdapter::createPlugin(u32 handle, const PluginSetup &setup) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectPlugin *plugin = nullptr;
  if (acc.isValid()) {
    switch (setup.type) {
    case PLUGIN_TYPE_NUMBER: {
      ui::UIObjectNumberPlugin *numberPlugin = ui::UIObjectNumberPlugin::create(handle);
      if (numberPlugin != nullptr) {
        numberPlugin->setMin(setup.param);
        numberPlugin->setMax(setup.max);
      }
      plugin = numberPlugin;
      break;
    }
    case PLUGIN_TYPE_IMAGE:
      if (acc.isImage()) {
        ui::UIObjectNumberPlugin *numberPlugin = ui::UIObjectNumberPlugin::create(handle);
        if (numberPlugin != nullptr) {
          int min = acc.isStreamImage();
          int max = min + acc.getImageMax();
          numberPlugin->setMin(min);
          numberPlugin->setMax(max);
        }
        plugin = numberPlugin;
      }
      break;
    case PLUGIN_TYPE_TEXT:
      plugin = ui::UIObjectTextPlugin::create(handle);
      break;
    case PLUGIN_TYPE_DISP:
      plugin = ui::UIObjectDispPlugin::create(handle);
      break;
    case PLUGIN_TYPE_POS:
      plugin = ui::UIObjectPosPlugin::create(handle, 0, 0);
      break;
    case PLUGIN_TYPE_WORLD_POS:
      plugin = ui::UIObjectWorldPosPlugin::create(handle);
      break;
    case PLUGIN_TYPE_OFFSET:
      plugin = ui::UIObjectOffsetPlugin::create(handle);
      break;
    case PLUGIN_TYPE_TIME:
      plugin = ui::UIObjectTimePlugin::create(handle, setup.param);
      break;
    case PLUGIN_TYPE_COLOR:
      plugin = ui::UIObjectColorPlugin::create(handle);
      break;
    case PLUGIN_TYPE_PATTERN:
      plugin = ui::UIObjectPatternPlugin::create(handle);
      break;
    }
  }
  return plugin;
}

GfMenuAdapter::CompareResult GfMenuAdapter::compare(GfMenuAdapter *adapter, GfMenuAdapter *other) {
  ui::UIObjectNumberPlugin *number = adapter->plugin != nullptr ? mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(adapter->plugin) : nullptr;
  if (other->plugin != nullptr) {
    ui::UIObjectNumberPlugin *otherNumber = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(other->plugin);
    if (number != nullptr && otherNumber != nullptr) {
      if (number->number == otherNumber->number) {
        return COMPARE_RESULT_SAME;
      }
      if (number->number < otherNumber->number) {
        return COMPARE_RESULT_LESS;
      }
      if (number->number > otherNumber->number) {
        return COMPARE_RESULT_GREATER;
      }
    }
  }

  ui::UIObjectTextPlugin *text = adapter->plugin != nullptr ? mm::mtl::dynamicCast<ui::UIObjectTextPlugin>(adapter->plugin) : nullptr;
  if (other->plugin == nullptr) {
    return COMPARE_RESULT_SAME;
  }
  ui::UIObjectTextPlugin *otherText = mm::mtl::dynamicCast<ui::UIObjectTextPlugin>(other->plugin);
  if (text == nullptr || otherText == nullptr) {
    return COMPARE_RESULT_SAME;
  }

  int result = strcmp(text->text.c_str(), otherText->text.c_str());
  if (result == 0) {
    return COMPARE_RESULT_SAME;
  }
  if (result < 0) {
    return COMPARE_RESULT_LESS;
  }
  if (result > 0) {
    return COMPARE_RESULT_GREATER;
  }
  return COMPARE_RESULT_SAME;
}

void GfMenuAdapter::attachPlugin(ui::UIObjectPlugin *plugin) {
  plugin->addRef();
  this->plugin = plugin;
}

void GfMenuAdapter::setDispAlphaMode(bool isAlphaMode) {
  if (plugin != nullptr) {
    ui::UIObjectDispPlugin *dispPlugin = mm::mtl::dynamicCast<ui::UIObjectDispPlugin>(plugin);
    if (dispPlugin != nullptr) {
      dispPlugin->setAlphaMode(isAlphaMode);
    }
  }
}

void GfMenuAdapter::setDispReverseMode(bool isReverseMode) {
  if (plugin != nullptr) {
    ui::UIObjectDispPlugin *dispPlugin = mm::mtl::dynamicCast<ui::UIObjectDispPlugin>(plugin);
    if (dispPlugin != nullptr) {
      dispPlugin->setReverseMode(isReverseMode);
    }
  }
}

void GfMenuAdapter::setDispFadeMode(f32 fadeTime) {
  if (plugin != nullptr) {
    ui::UIObjectDispPlugin *dispPlugin = mm::mtl::dynamicCast<ui::UIObjectDispPlugin>(plugin);
    if (dispPlugin != nullptr) {
      dispPlugin->setFadeMode(fadeTime);
    }
  }
}

void GfMenuAdapter::setDispSuspendMode(bool isSuspendMode) {
  if (plugin != nullptr) {
    ui::UIObjectDispPlugin *dispPlugin = mm::mtl::dynamicCast<ui::UIObjectDispPlugin>(plugin);
    if (dispPlugin != nullptr) {
      dispPlugin->setSuspendMode(true);
    }
  }
}

void GfMenuAdapter::setNumberReverseMode(bool isReverseMode) {
  if (plugin != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(plugin);
    if (numberPlugin != nullptr) {
      numberPlugin->isReverse = isReverseMode;
    }
  }
}

void GfMenuAdapter::setNumberInterpolateMode(f32 time) {
  if (plugin != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(plugin);
    if (numberPlugin != nullptr) {
      numberPlugin->setInterpolate(time);
    }
  }
}

void GfMenuAdapter::setPosAdjustScreen(bool isAdjustScreen) {
  if (plugin != nullptr) {
    ui::UIObjectPosPlugin *posPlugin = mm::mtl::dynamicCast<ui::UIObjectPosPlugin>(plugin);
    if (posPlugin != nullptr) {
      posPlugin->isAdjustScreen = isAdjustScreen;
    }
  }
}

void GfMenuAdapter::setPosAdjustSize(u32 width, u32 height) {
  if (plugin != nullptr) {
    ui::UIObjectPosPlugin *posPlugin = mm::mtl::dynamicCast<ui::UIObjectPosPlugin>(plugin);
    if (posPlugin != nullptr) {
      posPlugin->adjustWidth = width;
      posPlugin->adjustHeight = height;
    }
  }
}

void GfMenuAdapter::setPosAdjustSizeOffs(s16 x, s16 y) {
  if (plugin != nullptr) {
    ui::UIObjectPosPlugin *posPlugin = mm::mtl::dynamicCast<ui::UIObjectPosPlugin>(plugin);
    if (posPlugin != nullptr) {
      posPlugin->adjustOffsetX = x;
      posPlugin->adjustOffsetY = y;
    }
  }
}

void GfMenuAdapter::setPosOffsMode(u32 mode) {
  if (plugin != nullptr) {
    ui::UIObjectPosPlugin *posPlugin = mm::mtl::dynamicCast<ui::UIObjectPosPlugin>(plugin);
    if (posPlugin != nullptr) {
      posPlugin->offsetMode = mode;
    }
  }
}

void GfMenuAdapter::setOffsetLimit(u16 x, u16 y) {
  if (plugin != nullptr) {
    ui::UIObjectOffsetPlugin *offsetPlugin = mm::mtl::dynamicCast<ui::UIObjectOffsetPlugin>(plugin);
    if (offsetPlugin != nullptr) {
      offsetPlugin->maxOffset.x = x;
      offsetPlugin->maxOffset.y = y;
    }
  }
}

bool GfMenuAdapter::checkOwner(u32 handle) {
  if (plugin != nullptr) {
    return ui::UIUtil::getObject(handle)->isPluginOwner(plugin);
  }
  return false;
}

int GfMenuAdapter::getNumber() const {
  if (plugin != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(plugin);
    if (numberPlugin != nullptr) {
      return numberPlugin->number;
    }
  }
  return 0;
}

int GfMenuAdapter::getNumberMin() const {
  if (plugin != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(plugin);
    if (numberPlugin != nullptr) {
      return numberPlugin->min;
    }
  }
  return 0;
}

int GfMenuAdapter::getNumberMax() const {
  if (plugin != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(plugin);
    if (numberPlugin != nullptr) {
      return numberPlugin->max;
    }
  }
  return 0;
}

void GfMenuAdapter::setRewriteNumber(GfMenuRewriteNumber *rewriteNumber) {
  this->rewriteNumber = rewriteNumber;
  rewriteNumber->addRef();
}

void GfMenuAdapter::setNumber(int number) {
  if (plugin != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(plugin);
    if (numberPlugin != nullptr) {
      if (rewriteNumber != nullptr && rewriteNumber->isRewrite) {
        number = rewriteNumber->number;
      }
      numberPlugin->setNumber(number);
    }
  }
}

void GfMenuAdapter::setNumberMin(int min) {
  if (plugin != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(plugin);
    if (numberPlugin != nullptr) {
      numberPlugin->setMin(min);
    }
  }
}

void GfMenuAdapter::setNumberMax(int max) {
  if (plugin != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(plugin);
    if (numberPlugin != nullptr) {
      numberPlugin->setMax(max);
    }
  }
}

void GfMenuAdapter::setText(const ui::UIStr &text) {
  if (plugin != nullptr) {
    ui::UIObjectTextPlugin *textPlugin = mm::mtl::dynamicCast<ui::UIObjectTextPlugin>(plugin);
    if (textPlugin != nullptr) {
      textPlugin->setText(text);
    }
  }
}

void GfMenuAdapter::setDisp(bool isDisp) {
  if (plugin != nullptr) {
    ui::UIObjectDispPlugin *dispPlugin = mm::mtl::dynamicCast<ui::UIObjectDispPlugin>(plugin);
    if (dispPlugin != nullptr) {
      dispPlugin->setDisp(isDisp);
      if (linkedObject != 0) {
        ui::UIObjectAcc(linkedObject).setDisp(isDisp);
      }
    }
  }
}

void GfMenuAdapter::setPos(const mm::Pnt<s16> &pos) {
  if (plugin != nullptr) {
    ui::UIObjectPosPlugin *posPlugin = mm::mtl::dynamicCast<ui::UIObjectPosPlugin>(plugin);
    if (posPlugin != nullptr) {
      posPlugin->pos = pos;
    }
  }
}

void GfMenuAdapter::setPosWorld(const mm::Vec3 &pos) {
  if (plugin != nullptr) {
    ui::UIObjectWorldPosPlugin *worldPosPlugin = mm::mtl::dynamicCast<ui::UIObjectWorldPosPlugin>(plugin);
    if (worldPosPlugin != nullptr) {
      worldPosPlugin->worldPos = pos;
    }
  }
}

void GfMenuAdapter::setOffsetTargetPos(const mm::Pnt<s16> &pos) {
  if (plugin != nullptr) {
    ui::UIObjectOffsetPlugin *offsetPlugin = mm::mtl::dynamicCast<ui::UIObjectOffsetPlugin>(plugin);
    if (offsetPlugin != nullptr) {
      offsetPlugin->targetPos = pos;
    }
  }
}

bool GfMenuAdapter::isPosScreenAdjust() const {
  if (plugin != nullptr) {
    ui::UIObjectPosPlugin *posPlugin = mm::mtl::dynamicCast<ui::UIObjectPosPlugin>(plugin);
    if (posPlugin != nullptr) {
      return posPlugin->isAdjustScreen;
    }
  }
  return false;
}

void GfMenuAdapter::setTime(const ui::uiDateTime &time) {
  if (plugin != nullptr) {
    ui::UIObjectTimePlugin *timePlugin = mm::mtl::dynamicCast<ui::UIObjectTimePlugin>(plugin);
    if (timePlugin != nullptr) {
      timePlugin->setYear(time.year);
      timePlugin->setMonth(time.month);
      timePlugin->setDay(time.day);
      timePlugin->setHour(time.hour);
      timePlugin->setMin(time.minute);
      timePlugin->setSec(time.second);
      timePlugin->setMSec(time.millisecond);
    }
  }
}

void GfMenuAdapter::setElapseTime(const ElapseTime &time) {
  if (plugin != nullptr) {
    ui::UIObjectTimePlugin *timePlugin = mm::mtl::dynamicCast<ui::UIObjectTimePlugin>(plugin);
    if (timePlugin != nullptr) {
      timePlugin->setElapseHour(time.hour);
      timePlugin->setMin(time.minute);
      timePlugin->setSec(time.second);
    }
  }
}

void GfMenuAdapter::setMulColor(const char *name) {
  if (plugin != nullptr) {
    ui::UIObjectColorPlugin *colorPlugin = mm::mtl::dynamicCast<ui::UIObjectColorPlugin>(plugin);
    if (colorPlugin != nullptr) {
      if (name != nullptr) {
        colorPlugin->setMulColor(name);
      } else {
        colorPlugin->setMulColor(mm::Col3(1.0f, 1.0f, 1.0f));
      }
    }
  }
}

void GfMenuAdapter::setAddColor(const char *name) {
  if (plugin != nullptr) {
    ui::UIObjectColorPlugin *colorPlugin = mm::mtl::dynamicCast<ui::UIObjectColorPlugin>(plugin);
    if (colorPlugin != nullptr) {
      colorPlugin->setAddColor(name == nullptr ? "" : name);
    }
  }
}

void GfMenuAdapter::setColorMode(u32 mode) {
  if (plugin != nullptr) {
    ui::UIObjectColorPlugin *colorPlugin = mm::mtl::dynamicCast<ui::UIObjectColorPlugin>(plugin);
    if (colorPlugin != nullptr) {
      colorPlugin->setColorMode(mode);
    }
  }
}

bool GfMenuAdapter::isUpdateAlways() const { return (flags & FLAG_UPDATE_ALWAYS) != 0; }

void GfMenuAdapter::setColor(const char *name) {
  ui::UIObjectColorPlugin *colorPlugin = plugin != nullptr ? mm::mtl::dynamicCast<ui::UIObjectColorPlugin>(plugin) : nullptr;
  if (name != nullptr && colorPlugin != nullptr) {
    colorPlugin->setColor(name);
  }
}

void GfMenuAdapter::setTextFacePattern(const char *name) {
  ui::UIObjectPatternPlugin *patternPlugin = plugin != nullptr ? mm::mtl::dynamicCast<ui::UIObjectPatternPlugin>(plugin) : nullptr;
  if (name != nullptr && patternPlugin != nullptr) {
    patternPlugin->setFacePattern(name);
  }
}

void GfMenuAdapter::update(const fw::UpdateInfo &info) { flags &= ~FLAG_CHANGED; }

} // namespace gf
