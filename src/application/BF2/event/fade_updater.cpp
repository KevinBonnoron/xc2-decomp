#include "event/fade_updater.h"

#include "gf/game/gf_game_manager.h"
#include "gf/scom/gf_scom_fade.h"

namespace event {

FadeUpdater::FadeUpdater() : mChannel(0), mIsReserved(false), mHasColor(false) {}

void FadeUpdater::clear() {
  update();
  mIsReserved = false;
  mHasColor = false;
}

void FadeUpdater::update() {
  if (mIsReserved) {
    gf::SCOM_FADE::create(mChannel, frame, mIsFadeOut ? (mHasColor ? mColor : mm::Col4::black) : mm::Col4::zero);
    mIsReserved = false;
    mHasColor = false;
  }
}

void FadeUpdater::setup(int channel) { mChannel = channel; }

void FadeUpdater::reserve(bool isFadeOut, int frame, const mm::Col4 *color) {
  mIsReserved = true;
  mIsFadeOut = isFadeOut;
  this->frame = frame;
  if (color != nullptr) {
    mHasColor = true;
    mColor = *color;
  } else {
    mHasColor = false;
  }
}

bool FadeUpdater::isFading() const { return mIsReserved || gf::GfGameManager::isFading(mChannel); }

} // namespace event
