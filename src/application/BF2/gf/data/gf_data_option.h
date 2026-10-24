#pragma once
#include "gf/data/gf_data_system.h"
#include "gf/sound/gf_master_volume.h"
#include "types.h"
#include <stddef.h>

namespace gf {

constexpr float VOLUME_SCALE = 255.0f;

struct SDataOption {
  SDataOption() : unknown00(SAVE_DATA_VERSION), _04(0), _08(0), _09(0), _0a(0), _0b(true), _0c() {
    GfMasterVolume masterVolume;
    _66 = 0x80;
    _68 = true;
    unknown4c = masterVolume.getEventVoiceVolume() * VOLUME_SCALE;
    unknown4e = masterVolume.getEventCsVolume() * VOLUME_SCALE;
    unknown50 = masterVolume.getEventBgmVolume() * VOLUME_SCALE;
    unknown52 = masterVolume.getEventSeVolume() * VOLUME_SCALE;
    unknown54 = masterVolume.getGameBgmVolume() * VOLUME_SCALE;
    unknown56 = masterVolume.getGameEnvVolume() * VOLUME_SCALE;
    unknown58 = masterVolume.getGameWeatherVolume() * VOLUME_SCALE;
    unknown5a = masterVolume.getGameSeVolume() * VOLUME_SCALE;
    unknown5c = masterVolume.getPlayerVoiceVolume() * VOLUME_SCALE;
    unknown5e = masterVolume.getEnemyVoiceVolume() * VOLUME_SCALE;
    unknown60 = masterVolume.getNareVoiceVolume() * VOLUME_SCALE;
    unknown62 = masterVolume.getSystemVolume() * VOLUME_SCALE;
    unknown64 = masterVolume.getMenuBgmVolume() * VOLUME_SCALE;
  }

  u32 unknown00; // Inferred role: version; original member name unknown.
  u32 _04;
  u8 _08;
  u8 _09;
  u8 _0a;
  bool _0b;
  u8 _0c[0x4c - 0x0c];
  u16 unknown4c; // Inferred role: event voice volume; original member name unknown.
  u16 unknown4e; // Inferred role: event cs volume; original member name unknown.
  u16 unknown50; // Inferred role: event bgm volume; original member name unknown.
  u16 unknown52; // Inferred role: event se volume; original member name unknown.
  u16 unknown54; // Inferred role: game bgm volume; original member name unknown.
  u16 unknown56; // Inferred role: game env volume; original member name unknown.
  u16 unknown58; // Inferred role: game weather volume; original member name unknown.
  u16 unknown5a; // Inferred role: game se volume; original member name unknown.
  u16 unknown5c; // Inferred role: player voice volume; original member name unknown.
  u16 unknown5e; // Inferred role: enemy voice volume; original member name unknown.
  u16 unknown60; // Inferred role: nare voice volume; original member name unknown.
  u16 unknown62; // Inferred role: system volume; original member name unknown.
  u16 unknown64; // Inferred role: menu bgm volume; original member name unknown.
  u16 _66;
  bool _68;
  u8 _69[0x88 - 0x69];
};

static_assert(offsetof(SDataOption, _08) == 0x08, "");
static_assert(offsetof(SDataOption, _0c) == 0x0c, "");
static_assert(offsetof(SDataOption, unknown4c) == 0x4c, "");
static_assert(offsetof(SDataOption, unknown64) == 0x64, "");
static_assert(offsetof(SDataOption, _66) == 0x66, "");
static_assert(offsetof(SDataOption, _68) == 0x68, "");
static_assert(sizeof(SDataOption) == 0x88, "");

} // namespace gf
