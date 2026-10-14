#pragma once
#include "gf/data/gf_data_system.h"
#include "gf/sound/gf_master_volume.h"
#include "types.h"
#include <stddef.h>

namespace gf {

constexpr float VOLUME_SCALE = 255.0f;

struct SDataOption {
  SDataOption() : version(SAVE_DATA_VERSION), _04(0), _08(0), _09(0), _0a(0), _0b(true), _0c() {
    GfMasterVolume masterVolume;
    _66 = 0x80;
    _68 = true;
    eventVoiceVolume = masterVolume.getEventVoiceVolume() * VOLUME_SCALE;
    eventCsVolume = masterVolume.getEventCsVolume() * VOLUME_SCALE;
    eventBgmVolume = masterVolume.getEventBgmVolume() * VOLUME_SCALE;
    eventSeVolume = masterVolume.getEventSeVolume() * VOLUME_SCALE;
    gameBgmVolume = masterVolume.getGameBgmVolume() * VOLUME_SCALE;
    gameEnvVolume = masterVolume.getGameEnvVolume() * VOLUME_SCALE;
    gameWeatherVolume = masterVolume.getGameWeatherVolume() * VOLUME_SCALE;
    gameSeVolume = masterVolume.getGameSeVolume() * VOLUME_SCALE;
    playerVoiceVolume = masterVolume.getPlayerVoiceVolume() * VOLUME_SCALE;
    enemyVoiceVolume = masterVolume.getEnemyVoiceVolume() * VOLUME_SCALE;
    nareVoiceVolume = masterVolume.getNareVoiceVolume() * VOLUME_SCALE;
    systemVolume = masterVolume.getSystemVolume() * VOLUME_SCALE;
    menuBgmVolume = masterVolume.getMenuBgmVolume() * VOLUME_SCALE;
  }

  u32 version;
  u32 _04;
  u8 _08;
  u8 _09;
  u8 _0a;
  bool _0b;
  u8 _0c[0x4c - 0x0c];
  u16 eventVoiceVolume;
  u16 eventCsVolume;
  u16 eventBgmVolume;
  u16 eventSeVolume;
  u16 gameBgmVolume;
  u16 gameEnvVolume;
  u16 gameWeatherVolume;
  u16 gameSeVolume;
  u16 playerVoiceVolume;
  u16 enemyVoiceVolume;
  u16 nareVoiceVolume;
  u16 systemVolume;
  u16 menuBgmVolume;
  u16 _66;
  bool _68;
  u8 _69[0x88 - 0x69];
};

static_assert(offsetof(SDataOption, _08) == 0x08, "");
static_assert(offsetof(SDataOption, _0c) == 0x0c, "");
static_assert(offsetof(SDataOption, eventVoiceVolume) == 0x4c, "");
static_assert(offsetof(SDataOption, menuBgmVolume) == 0x64, "");
static_assert(offsetof(SDataOption, _66) == 0x66, "");
static_assert(offsetof(SDataOption, _68) == 0x68, "");
static_assert(sizeof(SDataOption) == 0x88, "");

} // namespace gf
