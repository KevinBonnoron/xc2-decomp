#include "event/volume_player.h"

#include "gf/game/event/gf_game_event.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace event {

const f32 VolumePlayer::TO_SEC = 1.0f / 30.0f;

VolumePlayer::VolumePlayer() {}

void VolumePlayer::clear() {
  update();
  mKeys.clear();
}

void VolumePlayer::update() {
  for (u32 i = 0; i < mKeys.size(); i++) {
    if (mKeys[i].isChange) {
      gf::GfGameEvent::setCategoryVolume(static_cast<fw::SoundCategory>(mKeys[i].category), mKeys[i].volume, mKeys[i].frame * TO_SEC);
      if (mKeys[i].category == 1) {
        gf::GfGameEvent::setCategoryVolume(static_cast<fw::SoundCategory>(10), mKeys[i].volume, mKeys[i].frame * TO_SEC);
      }
    } else {
      gf::GfGameEvent::setCategoryVolume(static_cast<fw::SoundCategory>(mKeys[i].category), 1.0f, mKeys[i].frame * TO_SEC);
      if (mKeys[i].category == 1) {
        gf::GfGameEvent::setCategoryVolume(static_cast<fw::SoundCategory>(10), 1.0f, mKeys[i].frame * TO_SEC);
      }
    }
  }
  mKeys.clear();
}

void VolumePlayer::change(u32 category, f32 volume, f32 frame) {
  if (mKeys.size() >= mKeys.capacity()) {
    mKeys.erase(mKeys.begin());
  }
  Key key;
  key.isChange = true;
  key.category = category;
  key.volume = volume;
  key.frame = frame;
  mKeys.push_back(key);
}

void VolumePlayer::reset(u32 category, f32 volume, f32 frame) {
  if (mKeys.size() >= mKeys.capacity()) {
    mKeys.erase(mKeys.begin());
  }
  Key key;
  key.isChange = true;
  key.category = category;
  key.volume = volume;
  key.frame = frame;
  mKeys.push_back(key);
}

} // namespace event
