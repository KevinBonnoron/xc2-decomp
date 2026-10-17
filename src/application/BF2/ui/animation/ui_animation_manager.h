#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace ui {

class UIAnimationManager : public mm::mtl::PtrSingleton<UIAnimationManager> {
public:
  struct AnimationInfo : public mm::mtl::IntrusiveListNode<AnimationInfo> {
    u32 object;
    bool playing;
    u32 handler;
  };

  UIAnimationManager();
  virtual ~UIAnimationManager();
  void update(const fw::UpdateInfo &info);
  bool registObject(u32 object);
  void changeEventHandleObject(u32 object, u32 handler);
  void resetEventHandleObject(u32 object);

  mm::mtl::IntrusiveList<AnimationInfo> animations;
};

static_assert(offsetof(UIAnimationManager::AnimationInfo, object) == 0x10, "");
static_assert(offsetof(UIAnimationManager::AnimationInfo, playing) == 0x14, "");
static_assert(offsetof(UIAnimationManager::AnimationInfo, handler) == 0x18, "");
static_assert(sizeof(UIAnimationManager::AnimationInfo) == 0x20, "");
static_assert(offsetof(UIAnimationManager, animations) == 0x08, "");
static_assert(sizeof(UIAnimationManager) == 0x20, "");

} // namespace ui
