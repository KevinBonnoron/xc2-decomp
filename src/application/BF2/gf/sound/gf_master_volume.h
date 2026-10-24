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

  f32 getEventVoiceVolume() const { return unknown08; }
  f32 getEventCsVolume() const { return unknown0c; }
  f32 getEventBgmVolume() const { return unknown10; }
  f32 getEventSeVolume() const { return unknown14; }
  f32 getGameBgmVolume() const { return unknown18; }
  f32 getGameEnvVolume() const { return unknown1c; }
  f32 getGameWeatherVolume() const { return unknown20; }
  f32 getGameSeVolume() const { return unknown24; }
  f32 getPlayerVoiceVolume() const { return unknown28; }
  f32 getEnemyVoiceVolume() const { return unknown2c; }
  f32 getNareVoiceVolume() const { return unknown30; }
  f32 getSystemVolume() const { return unknown34; }
  f32 getMenuBgmVolume() const { return unknown38; }

private:
  GF_SE_CATEGORY_HANDLE *unknown00; // Inferred role: category handle; original member name unknown.
  f32 unknown08;                    // Inferred role: event voice volume; original member name unknown.
  f32 unknown0c;                    // Inferred role: event cs volume; original member name unknown.
  f32 unknown10;                    // Inferred role: event bgm volume; original member name unknown.
  f32 unknown14;                    // Inferred role: event se volume; original member name unknown.
  f32 unknown18;                    // Inferred role: game bgm volume; original member name unknown.
  f32 unknown1c;                    // Inferred role: game env volume; original member name unknown.
  f32 unknown20;                    // Inferred role: game weather volume; original member name unknown.
  f32 unknown24;                    // Inferred role: game se volume; original member name unknown.
  f32 unknown28;                    // Inferred role: player voice volume; original member name unknown.
  f32 unknown2c;                    // Inferred role: enemy voice volume; original member name unknown.
  f32 unknown30;                    // Inferred role: nare voice volume; original member name unknown.
  f32 unknown34;                    // Inferred role: system volume; original member name unknown.
  f32 unknown38;                    // Inferred role: menu bgm volume; original member name unknown.

  friend struct GfMasterVolumeLayout;
};

struct GfMasterVolumeLayout {
  static_assert(offsetof(GfMasterVolume, unknown08) == 0x08, "");
  static_assert(offsetof(GfMasterVolume, unknown18) == 0x18, "");
  static_assert(offsetof(GfMasterVolume, unknown38) == 0x38, "");
};

static_assert(sizeof(GfMasterVolume) == 0x40, "");

} // namespace gf
