#include "ui/object/ui_image_object.h"

#include "framework/memory/framework_memory.h"
#include "layer/layer_acc_action.h"
#include "layer/layer_acc_def_obj.h"
#include "layer/layer_acc_def_texture.h"
#include "layer/layer_acc_layout_obj.h"
#include "layer/layer_acc_manager.h"
#include "layer/layer_acc_obj_base.h"
#include "ml/scn.h"
#include "mm_mtl/bitflag.h"
#include "scn/scn_render_dr_sys.h"
#include "scn/scn_render_dr_sys_parm_acc.h"
#include "ui/object/ui_layout_object.h"
#include "ui/stream/ui_stream_manager.h"
#include "ui/ui_object_base.h"
#include "ui/ui_util.h"

namespace ui {

UIImageObject::UIImageObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name) : UIObject(layer, name, UI_OBJECT_TYPE_IMAGE), unknown108(0), unknown10c(0), unknown110(nullptr) {}

UIImageObject::UIImageObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name, u32 type) : UIObject(layer, name, type), unknown108(0), unknown10c(0), unknown110(nullptr) {}

UIImageObject::~UIImageObject() { ; }

UIImageObject *UIImageObject::create(UILayoutObject *parent, const void *data, u32 streamId, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator, bool mask) {
  layer::LayerBase *layer;
  if (parent != nullptr) {
    layer::LayerAccLayoutObj layoutAcc(parent->unknownc8);
    layer = mask ? layoutAcc.createMaskObj(data) : layoutAcc.createObj(data);
  } else {
    layer::LayerAccManager manager;
    layer = mask ? manager.createMaskObj(data) : manager.createObj(data);
  }

  UIImageObject *image = nullptr;
  if (layer != nullptr) {
    layer::LayerAccDefObj(layer).setIconNum(0);
// __LINE__ is the line argument of the operator new call.
#line 106
    image = new (allocator, 16, __FILE__, __LINE__) UIImageObject(layer, name.c_str());
    if (image != nullptr && mask) {
      image->unknown98.set(UI_OBJECT_FLAG_MASK);
    }
  }
  image->unknown108 = streamId;
  return image;
}

UIImageObject *UIImageObject::create(UILayoutObject *parent, ml::ScnRenderDrCapture *capture, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator) {
  layer::LayerBase *layer;
  if (parent != nullptr) {
    layer::LayerAccLayoutObj layoutAcc(parent->unknownc8);
    layer = layoutAcc.createTexObj(*capture->texture);
  } else {
    layer::LayerAccManager manager;
    layer = manager.createTexObj(*capture->texture);
  }

  UIImageObject *image = nullptr;
  if (layer != nullptr) {
// __LINE__ is the line argument of the operator new call.
#line 155
    image = new (allocator, 16, __FILE__, __LINE__) UIImageObject(layer, name.c_str());
  }
  image->unknown110 = capture;
  return image;
}

void UIImageObject::changeBin(const void *data) {
  if (data != nullptr && unknownc8 != nullptr) {
    layer::LayerAccDefTexture(unknownc8).setTexutre(data);
  }
}

void UIImageObject::setMaskObject(UIImageObject *mask) {
  if (mask != nullptr && unknownc8 != nullptr && mask->unknownc8 != nullptr && mask->unknown98.test(UI_OBJECT_FLAG_MASK)) {
    layer::LayerAccDefObj(unknownc8).setMaskObj(mask->unknownc8);
  }
}

void UIImageObject::setImageIndex(u16 index) {
  if (unknown110 != nullptr || unknownc8 == nullptr) {
    return;
  }
  if (index < getImageMax()) {
    if (unknown108 != 0) {
      UIStreamManager::get()->start(unknown108, unknowne8, index);
      unknown10c = index;
    } else {
      layer::LayerAccDefObj obj(unknownc8);
      obj.setIconNum(index);
    }
  }
}

u16 UIImageObject::getImageMax() {
  if (unknown110 != nullptr) {
    return 1;
  }
  if (unknownc8 == nullptr) {
    return 1;
  }
  u16 max;
  if (unknown108 != 0) {
    max = UIStreamManager::get()->getContentsNum(unknown108);
  } else {
    layer::LayerAccDefObj obj(unknownc8);
    max = obj.getIconMax() + 1;
  }
  return max;
}

u16 UIImageObject::getImageIndex() {
  if (unknown110 != nullptr) {
    return 0;
  }
  if (unknownc8 == nullptr) {
    return 0;
  }
  if (unknown108 != 0) {
    return unknown10c;
  }
  return layer::LayerAccDefObj(unknownc8).getIconNum();
}

void UIImageObject::setHFlip(bool flip) {
  if (unknownc8 != nullptr) {
    layer::LayerAccDefObj(unknownc8).setFlip(layer::LAYER_FLIP_TYPE_HORIZONTAL, flip);
  }
}

void UIImageObject::setVFlip(bool flip) {
  if (unknownc8 != nullptr) {
    layer::LayerAccDefObj(unknownc8).setFlip(layer::LAYER_FLIP_TYPE_VERTICAL, flip);
  }
}

void UIImageObject::setExtType(u32 type) {
  if (unknown110 != nullptr || unknownc8 == nullptr) {
    return;
  }
  layer::LayerAccDefObj obj(unknownc8);
  switch (type) {
  case 1:
    obj.setGauge(static_cast<layer::LAYER_GAUGE>(3));
    break;
  case 2:
    obj.setGauge(static_cast<layer::LAYER_GAUGE>(1));
    break;
  case 3:
    obj.setGauge(static_cast<layer::LAYER_GAUGE>(4));
    break;
  case 4:
    obj.setGauge(static_cast<layer::LAYER_GAUGE>(2));
    break;
  }
}

u32 UIImageObject::getExtType() {
  if (unknown110 != nullptr) {
    return 0;
  }
  if (unknownc8 == nullptr) {
    return 0;
  }
  layer::LayerAccDefObj obj(unknownc8);
  if (obj.getGauge() != layer::LAYER_GAUGE_NONE) {
    if (obj.getGauge() == 3) {
      return 1;
    }
    if (obj.getGauge() == 1) {
      return 2;
    }
    if (obj.getGauge() == 4) {
      return 3;
    }
    if (obj.getGauge() == 2) {
      return 4;
    }
  }
  return 0;
}

void UIImageObject::setExtParam(f32 param) {
  if (unknown110 != nullptr || unknownc8 == nullptr) {
    return;
  }
  layer::LayerAccDefObj obj(unknownc8);
  if (obj.getGauge() != layer::LAYER_GAUGE_NONE) {
    obj.setParm(param);
  }
}

f32 UIImageObject::getExtParam() {
  if (unknown110 != nullptr || unknownc8 == nullptr) {
    return 0.0f;
  }
  layer::LayerAccDefObj obj(unknownc8);
  if (obj.getGauge() == layer::LAYER_GAUGE_NONE) {
    return 0.0f;
  }
  return obj.getParm();
}

bool UIImageObject::hasAnimation() {
  if (unknown110 != nullptr) {
    return false;
  }
  if (unknownc8 == nullptr) {
    return false;
  }
  if (unknown98.test(UI_OBJECT_FLAG_MASK)) {
    return false;
  }
  return layer::LayerAccAction(unknownc8).isActionData();
}

void UIImageObject::startAnimation(const char *name, bool loop) {
  if (hasAnimation()) {
    layer::LayerAccAction action(unknownc8);
    action.actionName(name);
    unknown118 = loop;
  }
}

void UIImageObject::startAnimationFromID(u32 id, bool loop) {
  if (hasAnimation()) {
    layer::LayerAccAction action(unknownc8);
    action.actionID(id);
    unknown118 = loop;
  }
}

void UIImageObject::startAnimationFromIndex(u32 index, bool loop) {
  if (hasAnimation()) {
    layer::LayerAccAction action(unknownc8);
    if (index < action.getActionMax()) {
      action.actionIdx(index);
      unknown118 = loop;
    }
  }
}

void UIImageObject::stopAnimation() {
  if (hasAnimation()) {
    layer::LayerAccAction action(unknownc8);
    if (action.isRunning()) {
      action.actionEnd();
    }
  }
}

bool UIImageObject::isPlayingAnimation() {
  if (hasAnimation()) {
    layer::LayerAccAction action(unknownc8);
    return action.isRunning();
  }
  return false;
}

u32 UIImageObject::getAnimationMax() {
  if (hasAnimation()) {
    layer::LayerAccAction action(unknownc8);
    return action.getActionMax();
  }
  return 0;
}

const char *UIImageObject::getAnimationName(u32 index) {
  if (index < getAnimationMax()) {
    layer::LayerAccAction action(unknownc8);
    return action.getActionName(index);
  }
  return nullptr;
}

f32 UIImageObject::getAnimationPlaybackLength() {
  if (unknown110 != nullptr || unknownc8 == nullptr) {
    return 0.0f;
  }
  layer::LayerAccAction action(unknownc8);
  return action.getActionSec(action.getRunningActIdx());
}

f32 UIImageObject::getAnimationPlaybackTime() {
  if (unknown110 != nullptr || unknownc8 == nullptr) {
    return 0.0f;
  }
  return layer::LayerAccAction(unknownc8).getRunningActSec();
}

void UIImageObject::setAnimationPlaybackTime(f32 time) {
  if (unknown110 == nullptr && unknownc8 != nullptr) {
    layer::LayerAccAction(unknownc8).setRunningActSec(time);
  }
}

void UIImageObject::applyCapture() {
  if (unknown110 != nullptr) {
    ml::ScnRenderDrSysParmAcc(ml::Scn::get()->renderDrSys, 0).startCapture(unknown110);
  }
}

u32 UIImageObject::duplicateImpl(u32 parent) {
  UILayoutObject *layout = UIUtil::getLayoutObject(parent);
  if (layout == nullptr) {
    return 0;
  }

  layer::LayerAccObjBase acc(unknownc8);
  UIImageObject *image;
  if (unknown110 == nullptr) {
    image = create(layout, acc.getResData(), unknown108, unknowna0.c_str(), UIUtil::getProgAllocator(), unknown98.test(UI_OBJECT_FLAG_MASK));
  } else {
    image = create(layout, unknown110, unknowna0.c_str(), UIUtil::getProgAllocator());
  }
  if (image == nullptr) {
    return 0;
  }

  image->addRef();
  image->setImageIndex(getImageIndex());
  u32 handle = layout->addChild(parent, image);
  image->release();
  return handle;
}

const mm::mtl::RTTI *UIImageObject::getRTTI() const { return &m_rtti; }

} // namespace ui
