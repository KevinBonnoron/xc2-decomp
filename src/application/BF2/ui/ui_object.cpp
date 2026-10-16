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
    : UIObjectBase(name), layer(layer), layerAcc(layer), objectType(type), duplicateCount(0), parent(0), plugins(nullptr) {
  handle = UIUtil::registObject(this);
  nameHash = mm::mtl::hashStrCrc(this->name.c_str());
}

UIObject::~UIObject() {
  if (layer != nullptr) {
    layer->release();
    layer = nullptr;
  }

  for (mm::mtl::IntrusiveList<UIObjectParam>::iterator it = params.begin(); it != params.end(); ++it) {
    it->handle = 0;
  }

  if (plugins != nullptr) {
    UIObjectPlugin *plugin = plugins;
    do {
      UIObjectPlugin *next = plugin->next;
      plugin->release();
      plugin = next;
    } while (plugin != nullptr);
  }
  plugins = nullptr;
}

void UIObject::update() {
  if (flags.test(UI_OBJECT_FLAG_DUPLICATE) && !flags.test(UI_OBJECT_FLAG_TERM)) {
    if (UIUtil::getObject(parent)->isTerm()) {
      setTerm();
      return;
    }
  }

  if (!flags.test(UI_OBJECT_FLAG_SUSPEND) && displayInfo.disp) {
    UIObjectBase::update();
  }
}

UIObject *UIObject::getParentPtr() const {
  if (parent != 0) {
    return UIUtil::getObject(parent);
  }
  return nullptr;
}

void UIObject::updatePlugin() {
  UIObjectAcc acc(this);
  for (UIObjectPlugin *plugin = plugins; plugin != nullptr; plugin = plugin->next) {
    if (plugin->isNeedUpdate(acc)) {
      plugin->execute(acc);
    }
  }
}

void UIObject::applyDisplayInfo(const UIObjectParam::AdditionalParam &param) {
  layerAcc.setCenterType(CENTER_TYPES[displayInfo.displayMode]);
  layerAcc.setPriority(displayInfo.priority);
  layerAcc.setAddCol(displayInfo.getAddColor());
  mm::Col4 color = displayInfo.getMulColor();
  color.a = param.alpha * color.a;
  layerAcc.setMulCol(color);
}

void UIObject::setParent(u32 parent) {
  if (this->parent != parent) {
    this->parent = parent;
  }
}

void UIObject::getPos(mm::Pnt<s16> &pos) const {
  pos = transform.pos;
  mm::Pnt<s16> offset;
  getDisplayOffset(UI_DISPLAY_MODE_TOP_LEFT, offset);
  pos.x += offset.x;
  pos.y += offset.y;
}

void UIObject::getPosCenter(mm::Pnt<s16> &pos) const {
  pos = transform.pos;
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
  transform.setPos(x - offset.x, y - offset.y);
}

void UIObject::setPosCenter(const mm::Pnt<s16> &pos) {
  s16 x = pos.x;
  s16 y = pos.y;
  mm::Pnt<s16> offset;
  getDisplayOffset(UI_DISPLAY_MODE_CENTER, offset);
  transform.setPos(x - offset.x, y - offset.y);
}

void UIObject::resetDirty() {
  transform.dirty = false;
  displayInfo.dirty = false;
}

void UIObject::attachPlugin(UIObjectPlugin *plugin) {
  plugin->next = plugins;
  plugins = plugin;
  plugin->addRef();
}

bool UIObject::isPluginOwner(UIObjectPlugin *plugin) const {
  if (plugin == nullptr) {
    return false;
  }

  for (UIObjectPlugin *owned = plugins; owned != nullptr; owned = owned->next) {
    if (owned == plugin) {
      return true;
    }
  }
  return false;
}

void UIObject::registAdditionalParam(UIObjectParam *param) {
  if (param != nullptr) {
    params.push_back(param);
  }
}

void UIObject::unregistAdditionalParam(UIObjectParam *param) {
  if (param != nullptr) {
    params.erase(param);
  }
}

void UIObject::getDisplayOffset(u16 mode, mm::Pnt<s16> &offset) const {
  offset.x = 0;
  offset.y = 0;
  u32 width = static_cast<s32>(displayInfo.pixelWidth * transform.scale.x);
  u32 height = static_cast<s32>(displayInfo.pixelHeight * transform.scale.y);
  if (displayInfo.displayMode == UI_DISPLAY_MODE_TOP_LEFT) {
    if (mode == UI_DISPLAY_MODE_CENTER) {
      offset.x = width >> 1;
      offset.y = height >> 1;
    }
  } else if (displayInfo.displayMode == UI_DISPLAY_MODE_CENTER) {
    if (mode == UI_DISPLAY_MODE_TOP_LEFT) {
      offset.x = -(width >> 1);
      offset.y = -(height >> 1);
    }
  }
}

void UIObject::switchDisplayMode(u16 mode) {
  layer::LayerAccManager manager;
  if (displayInfo.displayMode == mode) {
    return;
  }

  f32 width = displayInfo.pixelWidth * transform.scale.x;
  f32 height = displayInfo.pixelHeight * transform.scale.y;
  if (mode == UI_DISPLAY_MODE_CENTER) {
    if (isImageType() || objectType == UI_OBJECT_TYPE_TEXT) {
      transform.setPos(transform.getPos().x + static_cast<s16>(width * 0.5f), transform.getPos().y + static_cast<s16>(height * 0.5f));
    }
  } else if (isImageType() || objectType == UI_OBJECT_TYPE_TEXT) {
    transform.setPos(transform.getPos().x - static_cast<s16>(width * 0.5f), transform.getPos().y - static_cast<s16>(height * 0.5f));
  }
  displayInfo.displayMode = mode;
}

void UIObject::setBlendType(u16 type) {
  displayInfo.blendType = type;
  layerAcc.setBlendType(BLEND_TYPES[type]);
}

void UIObject::setPriority(u16 priority) { displayInfo.priority = priority; }

void UIObject::setAddColor(const mm::Col3 &color) { displayInfo.addColor = color; }

void UIObject::setDebugDraw(bool) {}

bool UIObject::isDebugDraw() const { return false; }

void UIObject::importDisplaySize(UIDisplayInfo &displayInfo, layer::LayerBase *layer) {
  layer::LayerAccObjBase acc(layer);
  switch (layer->type) {
  case layer::LAYER_OBJ_TYPE_FONT: {
    layer::LayerAccFontObj font(layer);
    displayInfo.setPixelWidth(font.getFontPixelWidth());
    displayInfo.setPixelHeight(font.getFontPixelHeight());
    displayInfo.dirty = true;
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
    displayInfo.displayMode = UI_DISPLAY_MODE_TOP_LEFT;
  } else if (acc.getCenterType() == layer::LAYER_CENTER_TYPE_CENTER) {
    displayInfo.displayMode = UI_DISPLAY_MODE_CENTER;
  }
  mm::Col4 color = acc.getMulCol();
  displayInfo.mulColor = color;
}

const mm::mtl::RTTI *UIObject::getRTTI() const { return &m_rtti; }

} // namespace ui
