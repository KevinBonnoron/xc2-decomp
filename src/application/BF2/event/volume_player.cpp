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
  unknown08.clear();
}

void VolumePlayer::update() {
  for (u32 i = 0; i < unknown08.size(); i++) {
    if (unknown08[i].unknown00) {
      gf::GfGameEvent::setCategoryVolume(static_cast<fw::SoundCategory>(unknown08[i].unknown04), unknown08[i].unknown08, unknown08[i].unknown0c * TO_SEC);
      if (unknown08[i].unknown04 == 1) {
        gf::GfGameEvent::setCategoryVolume(static_cast<fw::SoundCategory>(10), unknown08[i].unknown08, unknown08[i].unknown0c * TO_SEC);
      }
    } else {
      gf::GfGameEvent::setCategoryVolume(static_cast<fw::SoundCategory>(unknown08[i].unknown04), 1.0f, unknown08[i].unknown0c * TO_SEC);
      if (unknown08[i].unknown04 == 1) {
        gf::GfGameEvent::setCategoryVolume(static_cast<fw::SoundCategory>(10), 1.0f, unknown08[i].unknown0c * TO_SEC);
      }
    }
  }
  unknown08.clear();
}

void VolumePlayer::change(u32 category, f32 volume, f32 frame) {
  if (unknown08.size() >= unknown08.capacity()) {
    unknown08.erase(unknown08.begin());
  }
  Key key;
  key.unknown00 = true;
  key.unknown04 = category;
  key.unknown08 = volume;
  key.unknown0c = frame;
  unknown08.push_back(key);
}

void VolumePlayer::reset(u32 category, f32 volume, f32 frame) {
  if (unknown08.size() >= unknown08.capacity()) {
    unknown08.erase(unknown08.begin());
  }
  Key key;
  key.unknown00 = true;
  key.unknown04 = category;
  key.unknown08 = volume;
  key.unknown0c = frame;
  unknown08.push_back(key);
}

} // namespace event
