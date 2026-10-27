#include "gf/game/gf_game_slow_attack.h"

#include "gf/game/gf_game_speed.h"
#include "gf/gf_allocator.h"
#include "gf/sound/gf_sound.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace gf {

GfSlowAttack::GfSlowAttack() : unknown30(false) {
  unknown10.bind(this, &GfSlowAttack::updateForIdle);
  m_state = 0;
}

GfSlowAttack::~GfSlowAttack() {}

void GfSlowAttack::update(const fw::UpdateInfo &info) {
  if (unknown10.isValid()) {
    unknown10(info);
  }
  if (unknown30) {
    unknown30 = false;
  }
}

void GfSlowAttack::updateForIdle(const fw::UpdateInfo &) {
  if (unknown30) {
    m_state = 1;
    unknown10.bind(this, &GfSlowAttack::updateForPlay);
  }
}

void GfSlowAttack::updateForPlay(const fw::UpdateInfo &) {
  setSpeedEnvronment(GfGameSpeed::getPlaySpeed());
  if (!unknown30) {
    m_state = 2;
    unknown10.bind(this, &GfSlowAttack::updateForTerm);
  }
}

void GfSlowAttack::updateForTerm(const fw::UpdateInfo &) {
  setSpeedEnvronment(1.0f);
  finish();
}

void GfSlowAttack::setSpeedEnvronment(f32 speed) {
  static const fw::SoundCategory categories[] = {CATEGORY_FIELD_SE, CATEGORY_GIMMICK_SE, CATEGORY_GAME_ENV, CATEGORY_GAME_WEATHER, CATEGORY_CHARACTER_SE};
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    for (u32 index = 0; index < 5; index++) {
      sound->setCategoryPitch(categories[index], speed, 0.0f);
    }
  }
}

f32 GfSlowAttack::getPlaySpeed() const { return GfGameSpeed::getPlaySpeed(); }

GfSlowAttack *GfSlowAttack::create() {
  GfSlowAttack *slowAttack = get();
  if (slowAttack == nullptr) {
#line 109
    slowAttack = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfSlowAttack();
  }
  return slowAttack;
}

void GfSlowAttack::destroy() {
  GfSlowAttack *slowAttack = get();
  if (slowAttack != nullptr) {
    slowAttack->finish();
    delete slowAttack;
  }
}

void GfSlowAttack::finish() {
  unknown10.bind(this, &GfSlowAttack::updateForIdle);
  m_state = 0;
}

s32 GfSlowAttack::getState() const { return m_state; }

void GfSlowAttack::executeSlow() { unknown30 = true; }

} // namespace gf
