#include "ui/ctrl/ui_ctrl_manager.h"

#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/motion/ui_motion_library.h"
#include "ui/ui_object.h"
#include "ui/ui_object_base.h"
#include "ui/ui_util.h"

namespace ui {
class UIMotionData;

UICtrlManager::UICtrlManager() : slots() {
  for (u32 i = 0; i < CTRL_SLOT_MAX; i++) {
    slots[i].objectPtr = nullptr;
    slots[i].object = 0;
    slots[i].handler = 0;
    slots[i].ctrl.stop();
  }
}

void UICtrlManager::releaseCtrlSlot(int slot) {
  if (slots[slot].objectPtr == nullptr) {
    return;
  }

  slots[slot].objectPtr->flags.set(UI_OBJECT_FLAG_CONTROL, false);
  if (slots[slot].flags.test(CTRL_FLAG_TERM)) {
    slots[slot].objectPtr->setTerm();
  }
  slots[slot].ctrl.stop();
  mm::mtl::safeRelease(slots[slot].objectPtr);
  slots[slot].object = 0;
  slots[slot].handler = 0;
}

void UICtrlManager::setDefault(int slot) {
  if (isValidSlot(slot) && slots[slot].objectPtr != nullptr) {
    slots[slot].objectPtr->transform = slots[slot].defaultTransform;
    slots[slot].objectPtr->displayInfo = slots[slot].defaultDisplayInfo;
  }
}

void UICtrlManager::stopAll() {
  for (int i = 0; i < CTRL_SLOT_MAX; i++) {
    if (slots[i].ctrl.isBusy()) {
      stopCtrl(i, true, true);
    }
  }
}

void UICtrlManager::stopCtrl(int slot, bool release, bool callback) {
  slots[slot].ctrl.stop();
  if (callback && slots[slot].handler != 0) {
    UIObject *handler = UIUtil::getObject(slots[slot].handler);
    if (handler != nullptr && handler->flags.test(UI_OBJECT_FLAG_LISTENER)) {
      UIEventManager::EventInfo event;
      event.handle = slots[slot].handler;
      event.data.type = 3;
      UIEventManager::get()->pushObjectEvent(event);
    }
  }
  if (slots[slot].flags.test(CTRL_FLAG_RESTORE)) {
    setDefault(slot);
  }
  if (release) {
    releaseCtrlSlot(slot);
  }
}

int UICtrlManager::reserveCtrlSlot(u32 handle, bool loop) {
  if (!UIUtil::isValid(handle)) {
    return -1;
  }

  for (u32 i = 0; i < CTRL_SLOT_MAX; i++) {
    if (slots[i].object == handle) {
      slots[i].loop = loop;
      return i;
    }
  }

  for (u32 i = 0; i < CTRL_SLOT_MAX; i++) {
    if (slots[i].objectPtr == nullptr) {
      slots[i].object = handle;
      slots[i].handler = handle;
      slots[i].objectPtr = UIUtil::getObject(handle);
      slots[i].objectPtr->addRef();
      slots[i].methods.clear();
      slots[i].delay = 0.0f;
      slots[i].loop = loop;
      slots[i].flags.clear();
      slots[i].defaultTransform = slots[i].objectPtr->transform;
      slots[i].defaultDisplayInfo = slots[i].objectPtr->displayInfo;
      return i;
    }
  }
  return -1;
}

int UICtrlManager::getCtrlSlot(u32 handle) {
  for (u32 i = 0; i < CTRL_SLOT_MAX; i++) {
    if (slots[i].object == handle) {
      return i;
    }
  }
  return -1;
}

void UICtrlManager::changeEventHandleObject(int slot, u32 handler) {
  if (slot != -1 && slots[slot].objectPtr != nullptr) {
    slots[slot].handler = handler;
  }
}

void UICtrlManager::setDelayTime(int slot, f32 delay) {
  if (slots[slot].objectPtr != nullptr) {
    slots[slot].delay = delay;
  }
}

void UICtrlManager::addPositionMethod(int slot, s16 x, s16 y, CURVE_TYPE curve) {
  if (slots[slot].objectPtr != nullptr) {
    slots[slot].pos.setup(slots[slot].objectPtr, mm::Pnt<s16>(x, y));
    UICtrl::Method method;
    method.method = &slots[slot].pos;
    method.curve = UIUtil::getCurve(curve);
    slots[slot].methods.push_back(method);
  }
}

void UICtrlManager::addScaleMethod(int slot, f32 x, f32 y, CURVE_TYPE curve) {
  if (slots[slot].objectPtr != nullptr) {
    alignas(16) mm::Vec2 scale = {x, y};
    slots[slot].scale.setup(slots[slot].objectPtr, scale);
    UICtrl::Method method;
    method.method = &slots[slot].scale;
    method.curve = UIUtil::getCurve(curve);
    slots[slot].methods.push_back(method);
  }
}

void UICtrlManager::addAlphaMethod(int slot, f32 alpha, CURVE_TYPE curve) {
  if (slots[slot].objectPtr != nullptr) {
    slots[slot].alpha.setup(slots[slot].objectPtr, alpha);
    UICtrl::Method method;
    method.method = &slots[slot].alpha;
    method.curve = UIUtil::getCurve(curve);
    slots[slot].methods.push_back(method);
  }
}

void UICtrlManager::addBrightMethod(int slot, f32 bright, CURVE_TYPE curve) {
  if (slots[slot].objectPtr != nullptr) {
    slots[slot].bright.setup(slots[slot].objectPtr, bright);
    UICtrl::Method method;
    method.method = &slots[slot].bright;
    method.curve = UIUtil::getCurve(curve);
    slots[slot].methods.push_back(method);
  }
}

void UICtrlManager::addRotMethod(int slot, f32 rot, CURVE_TYPE curve) {
  if (slots[slot].objectPtr != nullptr) {
    slots[slot].rot.setup(slots[slot].objectPtr, rot);
    UICtrl::Method method;
    method.method = &slots[slot].rot;
    method.curve = UIUtil::getCurve(curve);
    slots[slot].methods.push_back(method);
  }
}

void UICtrlManager::addMulColorMethod(int slot, const mm::Col3 &color, CURVE_TYPE curve) {
  if (slots[slot].objectPtr != nullptr) {
    slots[slot].mulColor.setup(slots[slot].objectPtr, color);
    UICtrl::Method method;
    method.method = &slots[slot].mulColor;
    method.curve = UIUtil::getCurve(curve);
    slots[slot].methods.push_back(method);
  }
}

void UICtrlManager::addAddColorMethod(int slot, const mm::Col3 &color, CURVE_TYPE curve) {
  if (slots[slot].objectPtr != nullptr) {
    slots[slot].addColor.setup(slots[slot].objectPtr, color);
    UICtrl::Method method;
    method.method = &slots[slot].addColor;
    method.curve = UIUtil::getCurve(curve);
    slots[slot].methods.push_back(method);
  }
}

void UICtrlManager::addMotionMethod(int slot, const char *motion, const char *name) {
  if (slots[slot].objectPtr == nullptr) {
    return;
  }

  UIMotionData *motionData = UIMotionLibrary::get()->find(motion);
  if (motionData != nullptr) {
    slots[slot].motion.setup(slots[slot].objectPtr, motionData, name);
    UICtrl::Method method;
    method.method = &slots[slot].motion;
    method.curve = UIUtil::getCurve(CURVE_TYPE_LINEAR);
    slots[slot].methods.push_back(method);
  }
}

void UICtrlManager::getDefaultTransfom(int slot, UITransform &transform) {
  if (isValidSlot(slot) && slots[slot].objectPtr != nullptr) {
    transform = slots[slot].defaultTransform;
  }
}

void UICtrlManager::getDefaultDisplayInfo(int slot, UIDisplayInfo &displayInfo) {
  if (isValidSlot(slot) && slots[slot].objectPtr != nullptr) {
    displayInfo = slots[slot].defaultDisplayInfo;
  }
}

void UICtrlManager::setSpeedFactor(int slot, f32 speedFactor) {
  if (isValidSlot(slot) && slots[slot].objectPtr != nullptr) {
    slots[slot].ctrl.speedFactor = speedFactor;
  }
}

void UICtrlManager::addCtrlObject(UICtrlObject *object) {
  if (object != nullptr) {
    object->addRef();
    ctrlObjects.push_back(object);
  }
}

void UICtrlManager::addUpdater(IUICtrlUpdater &updater) {
  if (!updater.intoNode()) {
    updaters.push_back(&updater);
  }
}

void UICtrlManager::delUpdater(IUICtrlUpdater &updater) {
  if (updater.intoNode()) {
    updaters.erase(&updater);
  }
}

bool UICtrlManager::isBusyCtrl(int slot) {
  bool busy = false;
  if (isValidSlot(slot) && slots[slot].objectPtr != nullptr) {
    busy = slots[slot].ctrl.isBusy();
  }
  return busy;
}

} // namespace ui
