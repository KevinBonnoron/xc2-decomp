#include "event/fade_updater.h"

#include "gf/game/gf_game_manager.h"
#include "gf/scom/gf_scom_fade.h"

namespace event {

FadeUpdater::FadeUpdater() : unknown00(0), unknown04(false), unknown0c(false) {}

void FadeUpdater::clear() {
  update();
  unknown04 = false;
  unknown0c = false;
}

void FadeUpdater::update() {
  if (unknown04) {
    gf::SCOM_FADE::create(unknown00, unknown08, unknown05 ? (unknown0c ? unknown10 : mm::Col4::black) : mm::Col4::zero);
    unknown04 = false;
    unknown0c = false;
  }
}

void FadeUpdater::setup(int channel) { unknown00 = channel; }

void FadeUpdater::reserve(bool isFadeOut, int frame, const mm::Col4 *color) {
  unknown04 = true;
  unknown05 = isFadeOut;
  this->unknown08 = frame;
  if (color != nullptr) {
    unknown0c = true;
    unknown10 = *color;
  } else {
    unknown0c = false;
  }
}

bool FadeUpdater::isFading() const { return unknown04 || gf::GfGameManager::isFading(unknown00); }

} // namespace event
