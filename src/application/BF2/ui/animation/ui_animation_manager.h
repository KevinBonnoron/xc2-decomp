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
    u32 unknown10;  // Inferred role: object; original member name unknown.
    bool unknown14; // Inferred role: playing; original member name unknown.
    u32 unknown18;  // Inferred role: handler; original member name unknown.
  };

  UIAnimationManager();
  virtual ~UIAnimationManager();
  void update(const fw::UpdateInfo &info);
  bool registObject(u32 object);
  void changeEventHandleObject(u32 object, u32 handler);
  void resetEventHandleObject(u32 object);

  mm::mtl::IntrusiveList<AnimationInfo> unknown08; // Inferred role: animations; original member name unknown.
};

static_assert(offsetof(UIAnimationManager::AnimationInfo, unknown10) == 0x10, "");
static_assert(offsetof(UIAnimationManager::AnimationInfo, unknown14) == 0x14, "");
static_assert(offsetof(UIAnimationManager::AnimationInfo, unknown18) == 0x18, "");
static_assert(sizeof(UIAnimationManager::AnimationInfo) == 0x20, "");
static_assert(offsetof(UIAnimationManager, unknown08) == 0x08, "");
static_assert(sizeof(UIAnimationManager) == 0x20, "");

} // namespace ui
