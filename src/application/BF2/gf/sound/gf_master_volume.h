#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_SE_CATEGORY_HANDLE;

class GfMasterVolume {
public:
  void initialize();
  void finalize();
  void setupGame();
  GfMasterVolume();
  ~GfMasterVolume();
  void setEventVoiceVolume(f32 volume);
  static f32 getFloatVolume(u16 volume);
  void setEventCsVolume(f32 volume);
  void setEventBgmVolume(f32 volume);
  void setEventSeVolume(f32 volume);
  void setGameBgmVolume(f32 volume);
  void setGameEnvVolume(f32 volume);
  void setGameWeatherVolume(f32 volume);
  void setGameSeVolume(f32 volume);
  void setPlayerVoiceVolume(f32 volume);
  void setEnemyVoiceVolume(f32 volume);
  void setNareVoiceVolume(f32 volume);
  void setSystemVolume(f32 volume);
  void setMenuBgmVolume(f32 volume);
  static u16 getU16Volume(f32 volume);

  f32 getEventVoiceVolume() const { return eventVoiceVolume; }
  f32 getEventCsVolume() const { return eventCsVolume; }
  f32 getEventBgmVolume() const { return eventBgmVolume; }
  f32 getEventSeVolume() const { return eventSeVolume; }
  f32 getGameBgmVolume() const { return gameBgmVolume; }
  f32 getGameEnvVolume() const { return gameEnvVolume; }
  f32 getGameWeatherVolume() const { return gameWeatherVolume; }
  f32 getGameSeVolume() const { return gameSeVolume; }
  f32 getPlayerVoiceVolume() const { return playerVoiceVolume; }
  f32 getEnemyVoiceVolume() const { return enemyVoiceVolume; }
  f32 getNareVoiceVolume() const { return nareVoiceVolume; }
  f32 getSystemVolume() const { return systemVolume; }
  f32 getMenuBgmVolume() const { return menuBgmVolume; }

private:
  GF_SE_CATEGORY_HANDLE *categoryHandle;
  f32 eventVoiceVolume;
  f32 eventCsVolume;
  f32 eventBgmVolume;
  f32 eventSeVolume;
  f32 gameBgmVolume;
  f32 gameEnvVolume;
  f32 gameWeatherVolume;
  f32 gameSeVolume;
  f32 playerVoiceVolume;
  f32 enemyVoiceVolume;
  f32 nareVoiceVolume;
  f32 systemVolume;
  f32 menuBgmVolume;

  friend struct GfMasterVolumeLayout;
};

struct GfMasterVolumeLayout {
  static_assert(offsetof(GfMasterVolume, eventVoiceVolume) == 0x08, "");
  static_assert(offsetof(GfMasterVolume, gameBgmVolume) == 0x18, "");
  static_assert(offsetof(GfMasterVolume, menuBgmVolume) == 0x38, "");
};

static_assert(sizeof(GfMasterVolume) == 0x40, "");

} // namespace gf
