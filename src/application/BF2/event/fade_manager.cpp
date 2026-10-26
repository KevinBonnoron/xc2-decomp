#include "event/fade_manager.h"

#include "event/frame_manager.h"
#include "event/skip_manager.h"
#include "event/ui_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

FadeManager::FadeManager() : unknown10(0) {}

void FadeManager::update() {
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  unknown18.update(info.unknown04);
  mm::mtl::Singleton<FadeCtrl>::getPtr()->update();
}

void FadeManager::playEventSkip(bool isFadeOut, int frame) {
  if (unknown10 & FLAG_DISABLE_FADE) {
    return;
  }
  int fadeFrame = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() ? 0 : frame;
  if (isFadeOut) {
    mm::mtl::Singleton<FadeCtrl>::getPtr()->fadeoutEventSkip(fadeFrame);
  } else {
    mm::mtl::Singleton<FadeCtrl>::getPtr()->fadeinEventSkip(fadeFrame);
  }
  mm::mtl::Singleton<UIManager>::getPtr()->setPadDisable(isFadeOut);
}

void FadeManager::clear() {
  unknown18.clear();
  mm::mtl::Singleton<FadeCtrl>::getPtr()->clear();
}

bool FadeManager::isFading() const { return mm::mtl::Singleton<FadeCtrl>::getPtr()->isFading(); }

void FadeManager::plan(FadePlanner::TYPE type, bool isEnable, u32 frame, u32 wait, FadeCtrl::PRIO prio, const mm::Col4 &color) {
  if (!(unknown10 & FLAG_DISABLE_FADE)) {
    unknown18.plan(type, isEnable, frame, wait, prio, color);
  }
}

void FadeManager::request(FadePlanner::TYPE type) {
  if (!(unknown10 & FLAG_DISABLE_FADE)) {
    unknown18.request(type);
  }
}

bool FadeManager::isSkipFading() const { return mm::mtl::Singleton<FadeCtrl>::getPtr()->isFading(FadeCtrl::PRIO_HIGH); }

void FadeManager::setDisableFade(bool isDisable) {
  if (isDisable) {
    unknown10 |= FLAG_DISABLE_FADE;
  } else {
    unknown10 &= ~FLAG_DISABLE_FADE;
  }
}

bool FadeManager::isDisableFade() const { return (unknown10 & FLAG_DISABLE_FADE) != 0; }

void FadeManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT_BEGIN:
    clear();
    break;
  case MSG_TYPE_UPDATE_POST:
    update();
    break;
  default:
    break;
  }
}

} // namespace event
