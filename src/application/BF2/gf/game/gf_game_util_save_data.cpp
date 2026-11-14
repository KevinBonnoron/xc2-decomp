#include "gf/game/gf_game_util_save_data.h"

#include "execute/title/title_main.h"
#include "framework/lang_util.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_option.h"
#include "gf/data/gf_data_system.h"
#include "gf/field/gf_real_time.h"
#include "gf/sound/gf_master_volume.h"
#include "gf/sound/gf_sound.h"

namespace gf {

void GfGameUtilSaveData::getSaveData(SDataSystem &dataSystem) {
  const SDataSystem *source = GfDataManager::getDataSystem();
  dataSystem.unknown00 = source->unknown00;
  dataSystem.unknown08 = source->unknown08;
}

void GfGameUtilSaveData::setTitleSaveData(const SDataSave &saveData) {
  if (tl::TitleMain::get() != nullptr) {
    SDataSave *titleSaveData = tl::TitleMain::get()->getSaveBuffer();
    titleSaveData->unknown00 = saveData.unknown00;
    titleSaveData->unknown08 = saveData.unknown08;
    titleSaveData->unknown10 = saveData.unknown10;
  }
}

void GfGameUtilSaveData::setupOptionSaveData(SDataOption &optionData) {
  optionData = *GfDataManager::getDataOption();
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    optionData.unknown4c.unknown00 = GfMasterVolume::getU16Volume(sound->unknown6690.getEventVoiceVolume());
    optionData.unknown4c.unknown02 = GfMasterVolume::getU16Volume(sound->unknown6690.getEventCsVolume());
    optionData.unknown4c.unknown04 = GfMasterVolume::getU16Volume(sound->unknown6690.getEventBgmVolume());
    optionData.unknown4c.unknown06 = GfMasterVolume::getU16Volume(sound->unknown6690.getEventSeVolume());
    optionData.unknown4c.unknown08 = GfMasterVolume::getU16Volume(sound->unknown6690.getGameBgmVolume());
    optionData.unknown4c.unknown0a = GfMasterVolume::getU16Volume(sound->unknown6690.getGameEnvVolume());
    optionData.unknown4c.unknown0c = GfMasterVolume::getU16Volume(sound->unknown6690.getGameWeatherVolume());
    optionData.unknown4c.unknown0e = GfMasterVolume::getU16Volume(sound->unknown6690.getGameSeVolume());
    optionData.unknown4c.unknown10 = GfMasterVolume::getU16Volume(sound->unknown6690.getPlayerVoiceVolume());
    optionData.unknown4c.unknown12 = GfMasterVolume::getU16Volume(sound->unknown6690.getEnemyVoiceVolume());
    optionData.unknown4c.unknown14 = GfMasterVolume::getU16Volume(sound->unknown6690.getNareVoiceVolume());
    optionData.unknown4c.unknown18 = GfMasterVolume::getU16Volume(sound->unknown6690.getMenuBgmVolume());
  }
  optionData.unknown4c._1d = fw::LangUtil::getLangType();
}

} // namespace gf
