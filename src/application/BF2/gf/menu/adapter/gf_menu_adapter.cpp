#include "gf/menu/adapter/gf_menu_adapter.h"

#include <string.h>

#include "gf/field/gf_field_time.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/rtti.h"
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

GfMenuAdapter::GfMenuAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAfter, bool isUpdateAlways) : unknown18(nullptr), unknown20(0), unknown24(0), unknown28(nullptr) {
  attachPlugin(plugin);
  unknown20 |= FLAG_CHANGED;
  if (isUpdateAlways) {
    unknown20 |= FLAG_UPDATE_ALWAYS;
  }
  GfMenuAdapterManager::get()->addAdapter(this, isUpdateAfter);
}

GfMenuAdapter::~GfMenuAdapter() {
  mm::mtl::safeRelease(unknown18);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuAdapter::setChange() {
  unknown20 |= FLAG_CHANGED;
  if (unknown18 != nullptr) {
    unknown18->unknown18 |= 2;
  }
}

void GfMenuAdapter::setUpdateAfter() { GfMenuAdapterManager::get()->setAfterUpdate(this); }

ui::UIObjectPlugin *GfMenuAdapter::createPlugin(u32 handle, const PluginSetup &setup) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectPlugin *plugin = nullptr;
  if (acc.isValid()) {
    switch (setup.unknown00) {
    case unknown004_0: {
      ui::UIObjectNumberPlugin *numberPlugin = ui::UIObjectNumberPlugin::create(handle);
      if (numberPlugin != nullptr) {
        numberPlugin->setMin(setup.unknown04);
        numberPlugin->setMax(setup.unknown08);
      }
      plugin = numberPlugin;
      break;
    }
    case unknown004_1:
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
    case unknown004_2:
      plugin = ui::UIObjectTextPlugin::create(handle);
      break;
    case unknown004_3:
      plugin = ui::UIObjectDispPlugin::create(handle);
      break;
    case unknown004_4:
      plugin = ui::UIObjectPosPlugin::create(handle, 0, 0);
      break;
    case unknown004_5:
      plugin = ui::UIObjectWorldPosPlugin::create(handle);
      break;
    case unknown004_6:
      plugin = ui::UIObjectOffsetPlugin::create(handle);
      break;
    case unknown004_7:
      plugin = ui::UIObjectTimePlugin::create(handle, setup.unknown04);
      break;
    case unknown004_8:
      plugin = ui::UIObjectColorPlugin::create(handle);
      break;
    case unknown004_9:
      plugin = ui::UIObjectPatternPlugin::create(handle);
      break;
    }
  }
  return plugin;
}

GfMenuAdapter::unknown005 GfMenuAdapter::compare(GfMenuAdapter *adapter, GfMenuAdapter *other) {
  ui::UIObjectNumberPlugin *number = adapter->unknown18 != nullptr ? mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(adapter->unknown18) : nullptr;
  if (other->unknown18 != nullptr) {
    ui::UIObjectNumberPlugin *otherNumber = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(other->unknown18);
    if (number != nullptr && otherNumber != nullptr) {
      if (number->unknown7c == otherNumber->unknown7c) {
        return unknown005_0;
      }
      if (number->unknown7c < otherNumber->unknown7c) {
        return unknown005_1;
      }
      if (number->unknown7c > otherNumber->unknown7c) {
        return unknown005_2;
      }
    }
  }

  ui::UIObjectTextPlugin *text = adapter->unknown18 != nullptr ? mm::mtl::dynamicCast<ui::UIObjectTextPlugin>(adapter->unknown18) : nullptr;
  if (other->unknown18 == nullptr) {
    return unknown005_0;
  }
  ui::UIObjectTextPlugin *otherText = mm::mtl::dynamicCast<ui::UIObjectTextPlugin>(other->unknown18);
  if (text == nullptr || otherText == nullptr) {
    return unknown005_0;
  }

  int result = strcmp(text->unknown80.c_str(), otherText->unknown80.c_str());
  if (result == 0) {
    return unknown005_0;
  }
  if (result < 0) {
    return unknown005_1;
  }
  if (result > 0) {
    return unknown005_2;
  }
  return unknown005_0;
}

void GfMenuAdapter::attachPlugin(ui::UIObjectPlugin *plugin) {
  plugin->addRef();
  this->unknown18 = plugin;
}

void GfMenuAdapter::setDispAlphaMode(bool isAlphaMode) {
  if (unknown18 != nullptr) {
    ui::UIObjectDispPlugin *dispPlugin = mm::mtl::dynamicCast<ui::UIObjectDispPlugin>(unknown18);
    if (dispPlugin != nullptr) {
      dispPlugin->setAlphaMode(isAlphaMode);
    }
  }
}

void GfMenuAdapter::setDispReverseMode(bool isReverseMode) {
  if (unknown18 != nullptr) {
    ui::UIObjectDispPlugin *dispPlugin = mm::mtl::dynamicCast<ui::UIObjectDispPlugin>(unknown18);
    if (dispPlugin != nullptr) {
      dispPlugin->setReverseMode(isReverseMode);
    }
  }
}

void GfMenuAdapter::setDispFadeMode(f32 fadeTime) {
  if (unknown18 != nullptr) {
    ui::UIObjectDispPlugin *dispPlugin = mm::mtl::dynamicCast<ui::UIObjectDispPlugin>(unknown18);
    if (dispPlugin != nullptr) {
      dispPlugin->setFadeMode(fadeTime);
    }
  }
}

void GfMenuAdapter::setDispSuspendMode(bool isSuspendMode) {
  if (unknown18 != nullptr) {
    ui::UIObjectDispPlugin *dispPlugin = mm::mtl::dynamicCast<ui::UIObjectDispPlugin>(unknown18);
    if (dispPlugin != nullptr) {
      dispPlugin->setSuspendMode(true);
    }
  }
}

void GfMenuAdapter::setNumberReverseMode(bool isReverseMode) {
  if (unknown18 != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(unknown18);
    if (numberPlugin != nullptr) {
      numberPlugin->unknown89 = isReverseMode;
    }
  }
}

void GfMenuAdapter::setNumberInterpolateMode(f32 time) {
  if (unknown18 != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(unknown18);
    if (numberPlugin != nullptr) {
      numberPlugin->setInterpolate(time);
    }
  }
}

void GfMenuAdapter::setPosAdjustScreen(bool isAdjustScreen) {
  if (unknown18 != nullptr) {
    ui::UIObjectPosPlugin *posPlugin = mm::mtl::dynamicCast<ui::UIObjectPosPlugin>(unknown18);
    if (posPlugin != nullptr) {
      posPlugin->unknown80 = isAdjustScreen;
    }
  }
}

void GfMenuAdapter::setPosAdjustSize(u32 width, u32 height) {
  if (unknown18 != nullptr) {
    ui::UIObjectPosPlugin *posPlugin = mm::mtl::dynamicCast<ui::UIObjectPosPlugin>(unknown18);
    if (posPlugin != nullptr) {
      posPlugin->unknown82 = width;
      posPlugin->unknown84 = height;
    }
  }
}

void GfMenuAdapter::setPosAdjustSizeOffs(s16 x, s16 y) {
  if (unknown18 != nullptr) {
    ui::UIObjectPosPlugin *posPlugin = mm::mtl::dynamicCast<ui::UIObjectPosPlugin>(unknown18);
    if (posPlugin != nullptr) {
      posPlugin->unknown86 = x;
      posPlugin->unknown88 = y;
    }
  }
}

void GfMenuAdapter::setPosOffsMode(u32 mode) {
  if (unknown18 != nullptr) {
    ui::UIObjectPosPlugin *posPlugin = mm::mtl::dynamicCast<ui::UIObjectPosPlugin>(unknown18);
    if (posPlugin != nullptr) {
      posPlugin->unknown8c = mode;
    }
  }
}

void GfMenuAdapter::setOffsetLimit(u16 x, u16 y) {
  if (unknown18 != nullptr) {
    ui::UIObjectOffsetPlugin *offsetPlugin = mm::mtl::dynamicCast<ui::UIObjectOffsetPlugin>(unknown18);
    if (offsetPlugin != nullptr) {
      offsetPlugin->unknown80.x = x;
      offsetPlugin->unknown80.y = y;
    }
  }
}

bool GfMenuAdapter::checkOwner(u32 handle) {
  if (unknown18 != nullptr) {
    return ui::UIUtil::getObject(handle)->isPluginOwner(unknown18);
  }
  return false;
}

int GfMenuAdapter::getNumber() const {
  if (unknown18 != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(unknown18);
    if (numberPlugin != nullptr) {
      return numberPlugin->unknown7c;
    }
  }
  return 0;
}

int GfMenuAdapter::getNumberMin() const {
  if (unknown18 != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(unknown18);
    if (numberPlugin != nullptr) {
      return numberPlugin->unknown80;
    }
  }
  return 0;
}

int GfMenuAdapter::getNumberMax() const {
  if (unknown18 != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(unknown18);
    if (numberPlugin != nullptr) {
      return numberPlugin->unknown84;
    }
  }
  return 0;
}

void GfMenuAdapter::setRewriteNumber(GfMenuRewriteNumber *rewriteNumber) {
  this->unknown28 = rewriteNumber;
  rewriteNumber->addRef();
}

void GfMenuAdapter::setNumber(int number) {
  if (unknown18 != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(unknown18);
    if (numberPlugin != nullptr) {
      if (unknown28 != nullptr && unknown28->unknown10) {
        number = unknown28->unknown0c;
      }
      numberPlugin->setNumber(number);
    }
  }
}

void GfMenuAdapter::setNumberMin(int min) {
  if (unknown18 != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(unknown18);
    if (numberPlugin != nullptr) {
      numberPlugin->setMin(min);
    }
  }
}

void GfMenuAdapter::setNumberMax(int max) {
  if (unknown18 != nullptr) {
    ui::UIObjectNumberPlugin *numberPlugin = mm::mtl::dynamicCast<ui::UIObjectNumberPlugin>(unknown18);
    if (numberPlugin != nullptr) {
      numberPlugin->setMax(max);
    }
  }
}

void GfMenuAdapter::setText(const ui::UIStr &text) {
  if (unknown18 != nullptr) {
    ui::UIObjectTextPlugin *textPlugin = mm::mtl::dynamicCast<ui::UIObjectTextPlugin>(unknown18);
    if (textPlugin != nullptr) {
      textPlugin->setText(text);
    }
  }
}

void GfMenuAdapter::setDisp(bool isDisp) {
  if (unknown18 != nullptr) {
    ui::UIObjectDispPlugin *dispPlugin = mm::mtl::dynamicCast<ui::UIObjectDispPlugin>(unknown18);
    if (dispPlugin != nullptr) {
      dispPlugin->setDisp(isDisp);
      if (unknown24 != 0) {
        ui::UIObjectAcc(unknown24).setDisp(isDisp);
      }
    }
  }
}

void GfMenuAdapter::setPos(const mm::Pnt<s16> &pos) {
  if (unknown18 != nullptr) {
    ui::UIObjectPosPlugin *posPlugin = mm::mtl::dynamicCast<ui::UIObjectPosPlugin>(unknown18);
    if (posPlugin != nullptr) {
      posPlugin->unknown7c = pos;
    }
  }
}

void GfMenuAdapter::setPosWorld(const mm::Vec3 &pos) {
  if (unknown18 != nullptr) {
    ui::UIObjectWorldPosPlugin *worldPosPlugin = mm::mtl::dynamicCast<ui::UIObjectWorldPosPlugin>(unknown18);
    if (worldPosPlugin != nullptr) {
      worldPosPlugin->unknowna0 = pos;
    }
  }
}

void GfMenuAdapter::setOffsetTargetPos(const mm::Pnt<s16> &pos) {
  if (unknown18 != nullptr) {
    ui::UIObjectOffsetPlugin *offsetPlugin = mm::mtl::dynamicCast<ui::UIObjectOffsetPlugin>(unknown18);
    if (offsetPlugin != nullptr) {
      offsetPlugin->unknown7c = pos;
    }
  }
}

bool GfMenuAdapter::isPosScreenAdjust() const {
  if (unknown18 != nullptr) {
    ui::UIObjectPosPlugin *posPlugin = mm::mtl::dynamicCast<ui::UIObjectPosPlugin>(unknown18);
    if (posPlugin != nullptr) {
      return posPlugin->unknown80;
    }
  }
  return false;
}

void GfMenuAdapter::setTime(const ui::uiDateTime &time) {
  if (unknown18 != nullptr) {
    ui::UIObjectTimePlugin *timePlugin = mm::mtl::dynamicCast<ui::UIObjectTimePlugin>(unknown18);
    if (timePlugin != nullptr) {
      timePlugin->setYear(time.unknown00_0);
      timePlugin->setMonth(time.unknown01_5);
      timePlugin->setDay(time.unknown03_2);
      timePlugin->setHour(time.unknown03_7);
      timePlugin->setMin(time.unknown04_6);
      timePlugin->setSec(time.unknown05_5);
      timePlugin->setMSec(time.unknown06_3);
    }
  }
}

void GfMenuAdapter::setElapseTime(const ElapseTime &time) {
  if (unknown18 != nullptr) {
    ui::UIObjectTimePlugin *timePlugin = mm::mtl::dynamicCast<ui::UIObjectTimePlugin>(unknown18);
    if (timePlugin != nullptr) {
      timePlugin->setElapseHour(time.unknown01_4);
      timePlugin->setMin(time.unknown00_6);
      timePlugin->setSec(time.unknown00_0);
    }
  }
}

void GfMenuAdapter::setMulColor(const char *name) {
  if (unknown18 != nullptr) {
    ui::UIObjectColorPlugin *colorPlugin = mm::mtl::dynamicCast<ui::UIObjectColorPlugin>(unknown18);
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
  if (unknown18 != nullptr) {
    ui::UIObjectColorPlugin *colorPlugin = mm::mtl::dynamicCast<ui::UIObjectColorPlugin>(unknown18);
    if (colorPlugin != nullptr) {
      colorPlugin->setAddColor(name == nullptr ? "" : name);
    }
  }
}

void GfMenuAdapter::setColorMode(u32 mode) {
  if (unknown18 != nullptr) {
    ui::UIObjectColorPlugin *colorPlugin = mm::mtl::dynamicCast<ui::UIObjectColorPlugin>(unknown18);
    if (colorPlugin != nullptr) {
      colorPlugin->setColorMode(mode);
    }
  }
}

bool GfMenuAdapter::isUpdateAlways() const { return (unknown20 & FLAG_UPDATE_ALWAYS) != 0; }

void GfMenuAdapter::setColor(const char *name) {
  ui::UIObjectColorPlugin *colorPlugin = unknown18 != nullptr ? mm::mtl::dynamicCast<ui::UIObjectColorPlugin>(unknown18) : nullptr;
  if (name != nullptr && colorPlugin != nullptr) {
    colorPlugin->setColor(name);
  }
}

void GfMenuAdapter::setTextFacePattern(const char *name) {
  ui::UIObjectPatternPlugin *patternPlugin = unknown18 != nullptr ? mm::mtl::dynamicCast<ui::UIObjectPatternPlugin>(unknown18) : nullptr;
  if (name != nullptr && patternPlugin != nullptr) {
    patternPlugin->setFacePattern(name);
  }
}

void GfMenuAdapter::update(const fw::UpdateInfo &info) { unknown20 &= ~FLAG_CHANGED; }

} // namespace gf
