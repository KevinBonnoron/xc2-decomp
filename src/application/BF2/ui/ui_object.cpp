#include "ui/ui_object.h"

#include "layer/layer_acc_font_obj.h"
#include "layer/layer_acc_manager.h"
#include "layer/layer_acc_mem_obj.h"
#include "layer/layer_base.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/hash.h"
#include "ui/ui_displayinfo.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_transform.h"
#include "ui/ui_util.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

namespace {

const layer::LayerCenterType CENTER_TYPES[] = {layer::LAYER_CENTER_TYPE_TOP_LEFT, layer::LAYER_CENTER_TYPE_CENTER};
const layer::LayerBlendType BLEND_TYPES[] = {layer::LAYER_BLEND_TYPE_NORMAL, layer::LAYER_BLEND_TYPE_ADD};

} // namespace

UIObject::UIObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name, u32 type)
    : UIObjectBase(name), unknownc8(layer), unknownd0(layer), unknownd8(type), unknownda(0), unknowndc(0), unknowne0(nullptr) {
  unknowne8 = UIUtil::registObject(this);
  unknownec = mm::mtl::hashStrCrc(this->unknowna0.c_str());
}

UIObject::~UIObject() {
  if (unknownc8 != nullptr) {
    unknownc8->release();
    unknownc8 = nullptr;
  }

  for (mm::mtl::IntrusiveList<UIObjectParam>::iterator it = unknownf0.begin(); it != unknownf0.end(); ++it) {
    it->unknown18 = 0;
  }

  if (unknowne0 != nullptr) {
    UIObjectPlugin *plugin = unknowne0;
    do {
      UIObjectPlugin *next = plugin->unknown10;
      plugin->release();
      plugin = next;
    } while (plugin != nullptr);
  }
  unknowne0 = nullptr;
}

void UIObject::update() {
  if (unknown98.test(UI_OBJECT_FLAG_DUPLICATE) && !unknown98.test(UI_OBJECT_FLAG_TERM)) {
    if (UIUtil::getObject(unknowndc)->isTerm()) {
      setTerm();
      return;
    }
  }

  if (!unknown98.test(UI_OBJECT_FLAG_SUSPEND) && unknown50.unknown08) {
    UIObjectBase::update();
  }
}

UIObject *UIObject::getParentPtr() const {
  if (unknowndc != 0) {
    return UIUtil::getObject(unknowndc);
  }
  return nullptr;
}

void UIObject::updatePlugin() {
  UIObjectAcc acc(this);
  for (UIObjectPlugin *plugin = unknowne0; plugin != nullptr; plugin = plugin->unknown10) {
    if (plugin->isNeedUpdate(acc)) {
      plugin->execute(acc);
    }
  }
}

void UIObject::applyDisplayInfo(const UIObjectParam::AdditionalParam &param) {
  unknownd0.setCenterType(CENTER_TYPES[unknown50.unknown09]);
  unknownd0.setPriority(unknown50.unknown0c);
  unknownd0.setAddCol(unknown50.getAddColor());
  mm::Col4 color = unknown50.getMulColor();
  color.a = param.alpha * color.a;
  unknownd0.setMulCol(color);
}

void UIObject::setParent(u32 parent) {
  if (this->unknowndc != parent) {
    this->unknowndc = parent;
  }
}

void UIObject::getPos(mm::Pnt<s16> &pos) const {
  pos = unknown20.unknown08;
  mm::Pnt<s16> offset;
  getDisplayOffset(UI_DISPLAY_MODE_TOP_LEFT, offset);
  pos.x += offset.x;
  pos.y += offset.y;
}

void UIObject::getPosCenter(mm::Pnt<s16> &pos) const {
  pos = unknown20.unknown08;
  mm::Pnt<s16> offset;
  getDisplayOffset(UI_DISPLAY_MODE_CENTER, offset);
  pos.x += offset.x;
  pos.y += offset.y;
}

void UIObject::setPos(const mm::Pnt<s16> &pos) {
  s16 x = pos.x;
  s16 y = pos.y;
  mm::Pnt<s16> offset;
  getDisplayOffset(UI_DISPLAY_MODE_TOP_LEFT, offset);
  unknown20.setPos(x - offset.x, y - offset.y);
}

void UIObject::setPosCenter(const mm::Pnt<s16> &pos) {
  s16 x = pos.x;
  s16 y = pos.y;
  mm::Pnt<s16> offset;
  getDisplayOffset(UI_DISPLAY_MODE_CENTER, offset);
  unknown20.setPos(x - offset.x, y - offset.y);
}

void UIObject::resetDirty() {
  unknown20.unknown24 = false;
  unknown50.unknown30 = false;
}

void UIObject::attachPlugin(UIObjectPlugin *plugin) {
  plugin->unknown10 = unknowne0;
  unknowne0 = plugin;
  plugin->addRef();
}

bool UIObject::isPluginOwner(UIObjectPlugin *plugin) const {
  if (plugin == nullptr) {
    return false;
  }

  for (UIObjectPlugin *owned = unknowne0; owned != nullptr; owned = owned->unknown10) {
    if (owned == plugin) {
      return true;
    }
  }
  return false;
}

void UIObject::registAdditionalParam(UIObjectParam *param) {
  if (param != nullptr) {
    unknownf0.push_back(param);
  }
}

void UIObject::unregistAdditionalParam(UIObjectParam *param) {
  if (param != nullptr) {
    unknownf0.erase(param);
  }
}

void UIObject::getDisplayOffset(u16 mode, mm::Pnt<s16> &offset) const {
  offset.x = 0;
  offset.y = 0;
  u32 width = static_cast<s32>(unknown50.unknown2c * unknown20.unknown10.x);
  u32 height = static_cast<s32>(unknown50.unknown2e * unknown20.unknown10.y);
  if (unknown50.unknown09 == UI_DISPLAY_MODE_TOP_LEFT) {
    if (mode == UI_DISPLAY_MODE_CENTER) {
      offset.x = width >> 1;
      offset.y = height >> 1;
    }
  } else if (unknown50.unknown09 == UI_DISPLAY_MODE_CENTER) {
    if (mode == UI_DISPLAY_MODE_TOP_LEFT) {
      offset.x = -(width >> 1);
      offset.y = -(height >> 1);
    }
  }
}

void UIObject::switchDisplayMode(u16 mode) {
  layer::LayerAccManager manager;
  if (unknown50.unknown09 == mode) {
    return;
  }

  f32 width = unknown50.unknown2c * unknown20.unknown10.x;
  f32 height = unknown50.unknown2e * unknown20.unknown10.y;
  if (mode == UI_DISPLAY_MODE_CENTER) {
    if (isImageType() || unknownd8 == UI_OBJECT_TYPE_TEXT) {
      unknown20.setPos(unknown20.getPos().x + static_cast<s16>(width * 0.5f), unknown20.getPos().y + static_cast<s16>(height * 0.5f));
    }
  } else if (isImageType() || unknownd8 == UI_OBJECT_TYPE_TEXT) {
    unknown20.setPos(unknown20.getPos().x - static_cast<s16>(width * 0.5f), unknown20.getPos().y - static_cast<s16>(height * 0.5f));
  }
  unknown50.unknown09 = mode;
}

void UIObject::setBlendType(u16 type) {
  unknown50.unknown0a = type;
  unknownd0.setBlendType(BLEND_TYPES[type]);
}

void UIObject::setPriority(u16 priority) { unknown50.unknown0c = priority; }

void UIObject::setAddColor(const mm::Col3 &color) { unknown50.unknown20 = color; }

void UIObject::setDebugDraw(bool) {}

bool UIObject::isDebugDraw() const { return false; }

void UIObject::importDisplaySize(UIDisplayInfo &displayInfo, layer::LayerBase *layer) {
  layer::LayerAccObjBase acc(layer);
  switch (layer->type) {
  case layer::LAYER_OBJ_TYPE_FONT: {
    layer::LayerAccFontObj font(layer);
    displayInfo.setPixelWidth(font.getFontPixelWidth());
    displayInfo.setPixelHeight(font.getFontPixelHeight());
    displayInfo.unknown30 = true;
    break;
  }
  case layer::LAYER_OBJ_TYPE_MEM: {
    layer::LayerAccMemObj mem(layer);
    displayInfo.setPixelWidth(mem.getMemWidth());
    displayInfo.setPixelHeight(mem.getMemHeight());
    break;
  }
  default:
    displayInfo.setPixelWidth(acc.getPixelWidth());
    displayInfo.setPixelHeight(acc.getPixelHeight());
    break;
  }
}

void UIObject::importDisplayInfo(UIDisplayInfo &displayInfo, layer::LayerBase *layer) {
  layer::LayerAccObjBase acc(layer);
  importDisplaySize(displayInfo, layer);
  if (acc.getCenterType() == layer::LAYER_CENTER_TYPE_TOP_LEFT) {
    displayInfo.unknown09 = UI_DISPLAY_MODE_TOP_LEFT;
  } else if (acc.getCenterType() == layer::LAYER_CENTER_TYPE_CENTER) {
    displayInfo.unknown09 = UI_DISPLAY_MODE_CENTER;
  }
  mm::Col4 color = acc.getMulCol();
  displayInfo.unknown10 = color;
}

const mm::mtl::RTTI *UIObject::getRTTI() const { return &m_rtti; }

} // namespace ui
