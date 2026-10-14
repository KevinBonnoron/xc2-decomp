#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {

class GfMasterVolume {
public:
  GfMasterVolume();
  ~GfMasterVolume();

  float getEventVoiceVolume() const { return mEventVoiceVolume; }
  float getEventCsVolume() const { return mEventCsVolume; }
  float getEventBgmVolume() const { return mEventBgmVolume; }
  float getEventSeVolume() const { return mEventSeVolume; }
  float getGameBgmVolume() const { return mGameBgmVolume; }
  float getGameEnvVolume() const { return mGameEnvVolume; }
  float getGameWeatherVolume() const { return mGameWeatherVolume; }
  float getGameSeVolume() const { return mGameSeVolume; }
  float getPlayerVoiceVolume() const { return mPlayerVoiceVolume; }
  float getEnemyVoiceVolume() const { return mEnemyVoiceVolume; }
  float getNareVoiceVolume() const { return mNareVoiceVolume; }
  float getSystemVolume() const { return mSystemVolume; }
  float getMenuBgmVolume() const { return mMenuBgmVolume; }

private:
  u8 _00[0x08 - 0x00];
  float mEventVoiceVolume;
  float mEventCsVolume;
  float mEventBgmVolume;
  float mEventSeVolume;
  float mGameBgmVolume;
  float mGameEnvVolume;
  float mGameWeatherVolume;
  float mGameSeVolume;
  float mPlayerVoiceVolume;
  float mEnemyVoiceVolume;
  float mNareVoiceVolume;
  float mSystemVolume;
  float mMenuBgmVolume;

  friend struct GfMasterVolumeLayout;
};

struct GfMasterVolumeLayout {
  static_assert(offsetof(GfMasterVolume, mEventVoiceVolume) == 0x08, "");
  static_assert(offsetof(GfMasterVolume, mGameBgmVolume) == 0x18, "");
  static_assert(offsetof(GfMasterVolume, mMenuBgmVolume) == 0x38, "");
};

} // namespace gf
