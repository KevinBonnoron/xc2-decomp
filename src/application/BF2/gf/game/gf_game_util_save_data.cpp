#include "gf/game/gf_game_util_save_data.h"

#include "execute/title/title_main.h"
#include "framework/lang_util.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_option.h"
#include "gf/data/gf_data_system.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_real_time.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_player_camera.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/quest/gf_quest_data.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/gf_manager.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/sound/gf_master_volume.h"
#include "gf/sound/gf_sound.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {

void GfGameUtilSaveData::getSaveData(SDataSystem &dataSystem) {
  const SDataSystem *source = GfDataManager::getDataSystem();
  dataSystem.unknown00 = source->unknown00;
  dataSystem.m_realTime = source->m_realTime;
}

// Inferred role: saves the map positions and rotations of the party; original name unknown (0x71003558e8, right after setupGameSaveData, 114 instructions; called by setupGameSaveData and
// getSaveData(SDataGame &), so it stays out of line). The yaw in degrees is held in a float before the Vec3 is built, and that is visible in the game's code only through the debug info: under
// -g a variable bound to the product puts a DBG_VALUE of s0 between the fmul and its store, AArch64A57FPLoadBalancing then sees that multiply as a chain without a kill and keeps its s0 instead
// of recolouring it. The game's six multiplies are s0, s0, s1, s1, s0, s1 (blade 0 keeps s0, 0x7100355978); the alternation s0, s1, s0, s1, s0, s1 of every spelling without a variable (the
// product inside the Vec3 constructor, member stores, in place, an inlined helper taking degrees or radians, a Vec3 local) differs in the 4 words at +0x90 and +0xc8. Searched exhaustively: 83 hand
// spellings and 2 permuter runs (1311 candidates, 158 matching sources, every one with a variable bound to the product). Decision 57, same kind of evidence as decision 44 (the effect exists only
// under -g and shows the original had the variable); both halves are written alike, the game cannot tell this from blade 0 alone.
static void unknown001(unknown118 &map) {
  for (u32 i = 0; i < 3; i++) {
    f32 driverRot;
    GfObjAcc driver(GfGameParty::getHandleDriver(i));
    driver.getObjPosRot(map.unknown00[i], driverRot);
    f32 driverDeg = driverRot * mm::RAD_TO_DEG;
    map.unknown60[i] = mm::Vec3(0.0f, driverDeg, 0.0f);
    f32 bladeRot;
    GfObjAcc blade(GfGameParty::getHandleBlade(i, -1));
    blade.getObjPosRot(map.unknown30[i], bladeRot);
    f32 bladeDeg = bladeRot * mm::RAD_TO_DEG;
    map.unknown90[i] = mm::Vec3(0.0f, bladeDeg, 0.0f);
  }
  GfGameScene *scene = GfGameScene::get();
  if (scene != nullptr) {
    map.unknown00[0] = scene->getEnableSavePos();
  }
  map.m_skipTravelID = GfGameManager::getMapJumpID();
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// Copies the order parent quests of a save game (the 256 quests and their count) in setupGameSaveData (0x7100355178). Forms tried without the helper, all 14 differing lines: the loop in the
// function body (int, u32 or size_t counter, a pointer walk, a QuestID or two halfword assignments, a reference to the target game): the game computes the target address of the loop before the
// source address, the body gives the reverse.
static void copyOrderParentQuests(SDataGame &dst, const SDataGame &src) {
  for (int i = 0; i < 256; i++) {
    dst.m_questData[i] = src.m_questData[i];
  }
  dst.unknown10a538 = src.unknown10a538;
}

// The branch tests the negation: written as `if (isClear)` clang tests the flag with cbz, the game with tbz (0x71003551f0).
void GfGameUtilSaveData::setupGameSaveData(SDataSave &saveData) {
  bool isClear = GfDataUtil::getScenarioFlag() > 10042 || GfDataManager::getDataGame()->unknown10ae81 != 0;
  getSaveData(saveData);
  saveData.m_game = *GfDataManager::getDataGame();
  if (!isClear) {
    unknown001(saveData.m_game.m_sDataMap);
    saveData.m_game.unknown10ae81 = 0;
    saveData.m_game.m_cameraYaw = GfGamePlayerCamera::getSaveYaw();
    saveData.m_game.m_cameraPitch = GfGamePlayerCamera::getSavePitch();
    saveData.m_game.m_playerCameraDistance = GfGamePlayerCamera::getSaveDistance();
    saveData.m_game.m_cameraHeight = GfGamePlayerCamera::getSaveHeight();
    saveData.m_game.m_cameraSide = GfGamePlayerCamera::getSaveSide();
    saveData.m_game.m_cameraFreeMode = GfGamePlayerCamera::isSaveFreeMode();
  } else {
    saveData.m_game.unknown10ae81 = 1;
    GfGameFlag::setLocal(saveData.m_game.m_gameFlag, 16, 1, 10032);
    tl::TitleMain *title = tl::TitleMain::get();
    if (title != nullptr) {
      // The game flag ranges copied from the title save (same helpers and index numbers as GfGameUtil::setupNewGameParam). Each range is a loop of its own in the game (0x7100355248 to 0x7100355708),
      // with the title save buffer fetched before each one: the calls stay written out (ruling 8; the quality gate reports the repeated statements).
      saveData.m_game.unknown002(title->getSaveBuffer()->m_game, 2, 0x27a, 0x662);
      saveData.m_game.unknown002(title->getSaveBuffer()->m_game, 2, 0x25b, 0x279);
      saveData.m_game.unknown002(title->getSaveBuffer()->m_game, 1, 0xfa2, 0x11fa);
      saveData.m_game.unknown003(title->getSaveBuffer()->m_game, 1, 0x11fb, 0x4b0);
      saveData.m_game.unknown002(title->getSaveBuffer()->m_game, 1, 0x1, 0xfa1);
      saveData.m_game.unknown003(title->getSaveBuffer()->m_game, 1, 0x9230, 0x400);
      saveData.m_game.unknown003(title->getSaveBuffer()->m_game, 1, 0x3690, 15000);
      saveData.m_game.unknown003(title->getSaveBuffer()->m_game, 1, 0x9631, 0x400);
      saveData.m_game.unknown003(title->getSaveBuffer()->m_game, 1, 0xab67, 0x640);
      saveData.m_game.unknown003(title->getSaveBuffer()->m_game, 1, 0xb1a8, 0xa0);
      saveData.m_game.unknown003(title->getSaveBuffer()->m_game, 1, 0xb249, 0xa0);
      saveData.m_game.unknown003(title->getSaveBuffer()->m_game, 1, 0xb2ea, 0xa0);
      saveData.m_game.unknown003(title->getSaveBuffer()->m_game, 1, 0xb38b, 0xa0);
      saveData.m_game.unknown003(title->getSaveBuffer()->m_game, 1, 0xb42c, 0xa0);
      saveData.m_game.unknown003(title->getSaveBuffer()->m_game, 2, 0x94b7, 0x640);
      saveData.m_game.unknown002(title->getSaveBuffer()->m_game, 8, 0x12, 0x5ee);
      saveData.m_game.m_scenario = title->getSaveBuffer()->m_game.m_scenario;
      saveData.m_game.m_select = title->getSaveBuffer()->m_game.m_select;
      copyOrderParentQuests(saveData.m_game, title->getSaveBuffer()->m_game);
      saveData.m_game.unknown26 = title->getSaveBuffer()->m_game.unknown26;
      saveData.m_game.m_eventChapterSave = title->getSaveBuffer()->m_game.m_eventChapterSave;
    }
  }
  GfFieldTime *fieldTime = GfFieldTime::get();
  if (fieldTime != nullptr) {
    saveData.m_game.m_gameTime = fieldTime->getGameTime();
    saveData.m_game.m_elapseTime = fieldTime->getElapseTime();
    saveData.m_game.unknown24 = fieldTime->isTimeStop();
    fieldTime->getRealTime(saveData.m_realTime);
    fieldTime->getRealTime(saveData.m_game.m_saveRealTime);
  }
}

void GfGameUtilSaveData::getSaveData(SDataGame &dataGame) {
  dataGame = *GfDataManager::getDataGame();
  unknown001(dataGame.m_sDataMap);
}

void GfGameUtilSaveData::setTitleSaveData(const SDataSave &saveData) {
  if (tl::TitleMain::get() != nullptr) {
    SDataSave *titleSaveData = tl::TitleMain::get()->getSaveBuffer();
    titleSaveData->unknown00 = saveData.unknown00;
    titleSaveData->m_realTime = saveData.m_realTime;
    titleSaveData->m_game = saveData.m_game;
  }
}

// Returns a reference (P1: its callers read it without a null test): the game calls tl::TitleMain::getOptionBuffer with `bl` and shares the epilogue (0x7100355c20),
// while a pointer return makes clang tail-call it (`b`, epilogue duplicated).
SDataOption &GfGameUtilSaveData::getValidOptionData() {
  SDataOption *optionData = GfDataManager::getDataOption();
  if ((GfManager::isExecModeThater() || GfManager::isExecModeAdvertize()) && tl::TitleMain::get() != nullptr) {
    optionData = tl::TitleMain::get()->getOptionBuffer();
  }
  return *optionData;
}

void GfGameUtilSaveData::flushOptionSaveData() {
  GfMenuManager::applyOptionData(getValidOptionData());
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    sound->setupGame();
  }
}

void GfGameUtilSaveData::setupOptionSaveData(SDataOption &optionData) {
  optionData = *GfDataManager::getDataOption();
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    optionData.m_sSoundUiOption.unknown00 = GfMasterVolume::getU16Volume(sound->m_masterVolume.getEventVoiceVolume());
    optionData.m_sSoundUiOption.unknown02 = GfMasterVolume::getU16Volume(sound->m_masterVolume.getEventCsVolume());
    optionData.m_sSoundUiOption.unknown04 = GfMasterVolume::getU16Volume(sound->m_masterVolume.getEventBgmVolume());
    optionData.m_sSoundUiOption.unknown06 = GfMasterVolume::getU16Volume(sound->m_masterVolume.getEventSeVolume());
    optionData.m_sSoundUiOption.unknown08 = GfMasterVolume::getU16Volume(sound->m_masterVolume.getGameBgmVolume());
    optionData.m_sSoundUiOption.unknown0a = GfMasterVolume::getU16Volume(sound->m_masterVolume.getGameEnvVolume());
    optionData.m_sSoundUiOption.unknown0c = GfMasterVolume::getU16Volume(sound->m_masterVolume.getGameWeatherVolume());
    optionData.m_sSoundUiOption.unknown0e = GfMasterVolume::getU16Volume(sound->m_masterVolume.getGameSeVolume());
    optionData.m_sSoundUiOption.unknown10 = GfMasterVolume::getU16Volume(sound->m_masterVolume.getPlayerVoiceVolume());
    optionData.m_sSoundUiOption.unknown12 = GfMasterVolume::getU16Volume(sound->m_masterVolume.getEnemyVoiceVolume());
    optionData.m_sSoundUiOption.unknown14 = GfMasterVolume::getU16Volume(sound->m_masterVolume.getNareVoiceVolume());
    optionData.m_sSoundUiOption.unknown18 = GfMasterVolume::getU16Volume(sound->m_masterVolume.getMenuBgmVolume());
  }
  optionData.m_sSoundUiOption._1d = fw::LangUtil::getLangType();
}

} // namespace gf
