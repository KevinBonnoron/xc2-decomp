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

UIImageObject::UIImageObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name) : UIObject(layer, name, UI_OBJECT_TYPE_IMAGE), streamId(0), imageIndex(0), capture(nullptr) {}

UIImageObject::UIImageObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name, u32 type) : UIObject(layer, name, type), streamId(0), imageIndex(0), capture(nullptr) {}

UIImageObject::~UIImageObject() { ; }

UIImageObject *UIImageObject::create(UILayoutObject *parent, const void *data, u32 streamId, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator, bool mask) {
  layer::LayerBase *layer;
  if (parent != nullptr) {
    layer::LayerAccLayoutObj layoutAcc(parent->layer);
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
      image->flags.set(UI_OBJECT_FLAG_MASK);
    }
  }
  image->streamId = streamId;
  return image;
}

UIImageObject *UIImageObject::create(UILayoutObject *parent, ml::ScnRenderDrCapture *capture, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator) {
  layer::LayerBase *layer;
  if (parent != nullptr) {
    layer::LayerAccLayoutObj layoutAcc(parent->layer);
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
  image->capture = capture;
  return image;
}

void UIImageObject::changeBin(const void *data) {
  if (data != nullptr && layer != nullptr) {
    layer::LayerAccDefTexture(layer).setTexutre(data);
  }
}

void UIImageObject::setMaskObject(UIImageObject *mask) {
  if (mask != nullptr && layer != nullptr && mask->layer != nullptr && mask->flags.test(UI_OBJECT_FLAG_MASK)) {
    layer::LayerAccDefObj(layer).setMaskObj(mask->layer);
  }
}

void UIImageObject::setImageIndex(u16 index) {
  if (capture != nullptr || layer == nullptr) {
    return;
  }
  if (index < getImageMax()) {
    if (streamId != 0) {
      UIStreamManager::get()->start(streamId, handle, index);
      imageIndex = index;
    } else {
      layer::LayerAccDefObj obj(layer);
      obj.setIconNum(index);
    }
  }
}

u16 UIImageObject::getImageMax() {
  if (capture != nullptr) {
    return 1;
  }
  if (layer == nullptr) {
    return 1;
  }
  u16 max;
  if (streamId != 0) {
    max = UIStreamManager::get()->getContentsNum(streamId);
  } else {
    layer::LayerAccDefObj obj(layer);
    max = obj.getIconMax() + 1;
  }
  return max;
}

u16 UIImageObject::getImageIndex() {
  if (capture != nullptr) {
    return 0;
  }
  if (layer == nullptr) {
    return 0;
  }
  if (streamId != 0) {
    return imageIndex;
  }
  return layer::LayerAccDefObj(layer).getIconNum();
}

void UIImageObject::setHFlip(bool flip) {
  if (layer != nullptr) {
    layer::LayerAccDefObj(layer).setFlip(layer::LAYER_FLIP_TYPE_HORIZONTAL, flip);
  }
}

void UIImageObject::setVFlip(bool flip) {
  if (layer != nullptr) {
    layer::LayerAccDefObj(layer).setFlip(layer::LAYER_FLIP_TYPE_VERTICAL, flip);
  }
}

void UIImageObject::setExtType(u32 type) {
  if (capture != nullptr || layer == nullptr) {
    return;
  }
  layer::LayerAccDefObj obj(layer);
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
  if (capture != nullptr) {
    return 0;
  }
  if (layer == nullptr) {
    return 0;
  }
  layer::LayerAccDefObj obj(layer);
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
  if (capture != nullptr || layer == nullptr) {
    return;
  }
  layer::LayerAccDefObj obj(layer);
  if (obj.getGauge() != layer::LAYER_GAUGE_NONE) {
    obj.setParm(param);
  }
}

f32 UIImageObject::getExtParam() {
  if (capture != nullptr || layer == nullptr) {
    return 0.0f;
  }
  layer::LayerAccDefObj obj(layer);
  if (obj.getGauge() == layer::LAYER_GAUGE_NONE) {
    return 0.0f;
  }
  return obj.getParm();
}

bool UIImageObject::hasAnimation() {
  if (capture != nullptr) {
    return false;
  }
  if (layer == nullptr) {
    return false;
  }
  if (flags.test(UI_OBJECT_FLAG_MASK)) {
    return false;
  }
  return layer::LayerAccAction(layer).isActionData();
}

void UIImageObject::startAnimation(const char *name, bool loop) {
  if (hasAnimation()) {
    layer::LayerAccAction action(layer);
    action.actionName(name);
    playbackControl = loop;
  }
}

void UIImageObject::startAnimationFromID(u32 id, bool loop) {
  if (hasAnimation()) {
    layer::LayerAccAction action(layer);
    action.actionID(id);
    playbackControl = loop;
  }
}

void UIImageObject::startAnimationFromIndex(u32 index, bool loop) {
  if (hasAnimation()) {
    layer::LayerAccAction action(layer);
    if (index < action.getActionMax()) {
      action.actionIdx(index);
      playbackControl = loop;
    }
  }
}

void UIImageObject::stopAnimation() {
  if (hasAnimation()) {
    layer::LayerAccAction action(layer);
    if (action.isRunning()) {
      action.actionEnd();
    }
  }
}

bool UIImageObject::isPlayingAnimation() {
  if (hasAnimation()) {
    layer::LayerAccAction action(layer);
    return action.isRunning();
  }
  return false;
}

u32 UIImageObject::getAnimationMax() {
  if (hasAnimation()) {
    layer::LayerAccAction action(layer);
    return action.getActionMax();
  }
  return 0;
}

const char *UIImageObject::getAnimationName(u32 index) {
  if (index < getAnimationMax()) {
    layer::LayerAccAction action(layer);
    return action.getActionName(index);
  }
  return nullptr;
}

f32 UIImageObject::getAnimationPlaybackLength() {
  if (capture != nullptr || layer == nullptr) {
    return 0.0f;
  }
  layer::LayerAccAction action(layer);
  return action.getActionSec(action.getRunningActIdx());
}

f32 UIImageObject::getAnimationPlaybackTime() {
  if (capture != nullptr || layer == nullptr) {
    return 0.0f;
  }
  return layer::LayerAccAction(layer).getRunningActSec();
}

void UIImageObject::setAnimationPlaybackTime(f32 time) {
  if (capture == nullptr && layer != nullptr) {
    layer::LayerAccAction(layer).setRunningActSec(time);
  }
}

void UIImageObject::applyCapture() {
  if (capture != nullptr) {
    ml::ScnRenderDrSysParmAcc(ml::Scn::get()->renderDrSys, 0).startCapture(capture);
  }
}

u32 UIImageObject::duplicateImpl(u32 parent) {
  UILayoutObject *layout = UIUtil::getLayoutObject(parent);
  if (layout == nullptr) {
    return 0;
  }

  layer::LayerAccObjBase acc(layer);
  UIImageObject *image;
  if (capture == nullptr) {
    image = create(layout, acc.getResData(), streamId, name.c_str(), UIUtil::getProgAllocator(), flags.test(UI_OBJECT_FLAG_MASK));
  } else {
    image = create(layout, capture, name.c_str(), UIUtil::getProgAllocator());
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
