#include "ui/animation/ui_animation_manager.h"

#include "framework/memory/framework_memory.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UIAnimationManager::UIAnimationManager() {}

bool UIAnimationManager::registObject(u32 object) {
  UIObjectAcc acc(object);
  if (!acc.isImage() || !acc.hasAnimation()) {
    return false;
  }

// __LINE__ is the line argument of the operator new call.
#line 104
  AnimationInfo *info = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) AnimationInfo;
  info->unknown10 = object;
  info->unknown18 = object;
  info->unknown14 = false;
  unknown08.push_back(info);
  return true;
}

void UIAnimationManager::changeEventHandleObject(u32 object, u32 handler) {
  for (mm::mtl::IntrusiveList<AnimationInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    if (it->unknown10 == object) {
      it->unknown18 = handler;
    }
  }
}

void UIAnimationManager::resetEventHandleObject(u32 object) {
  for (mm::mtl::IntrusiveList<AnimationInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    if (it->unknown10 == object) {
      it->unknown18 = object;
    }
  }
}

} // namespace ui
