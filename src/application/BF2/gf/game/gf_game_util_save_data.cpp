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
  dataSystem.unknown08 = source->unknown08;
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
  map.unknownc0 = GfGameManager::getMapJumpID();
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// Copies the order parent quests of a save game (the 256 quests and their count) in setupGameSaveData (0x7100355178). Forms tried without the helper, all 14 differing lines: the loop in the
// function body (int, u32 or size_t counter, a pointer walk, a QuestID or two halfword assignments, a reference to the target game): the game computes the target address of the loop before the
// source address, the body gives the reverse.
static void copyOrderParentQuests(SDataGame &dst, const SDataGame &src) {
  for (int i = 0; i < 256; i++) {
    dst.unknown10a138[i] = src.unknown10a138[i];
  }
  dst.unknown10a538 = src.unknown10a538;
}

// The branch tests the negation: written as `if (isClear)` clang tests the flag with cbz, the game with tbz (0x71003551f0).
void GfGameUtilSaveData::setupGameSaveData(SDataSave &saveData) {
  bool isClear = GfDataUtil::getScenarioFlag() > 10042 || GfDataManager::getDataGame()->unknown10ae81 != 0;
  getSaveData(saveData);
  saveData.unknown10 = *GfDataManager::getDataGame();
  if (!isClear) {
    unknown001(saveData.unknown10.unknown1097f0);
    saveData.unknown10.unknown10ae81 = 0;
    saveData.unknown10.unknown10ae74 = GfGamePlayerCamera::getSaveYaw();
    saveData.unknown10.unknown10ae78 = GfGamePlayerCamera::getSavePitch();
    saveData.unknown10.unknown109b28 = GfGamePlayerCamera::getSaveDistance();
    saveData.unknown10.unknown10ad70 = GfGamePlayerCamera::getSaveHeight();
    saveData.unknown10.unknown10ae82 = GfGamePlayerCamera::getSaveSide();
    saveData.unknown10.unknown10ae7c = GfGamePlayerCamera::isSaveFreeMode();
  } else {
    saveData.unknown10.unknown10ae81 = 1;
    GfGameFlag::setLocal(saveData.unknown10.unknownfbbc4, 16, 1, 10032);
    tl::TitleMain *title = tl::TitleMain::get();
    if (title != nullptr) {
      // The game flag ranges copied from the title save (same helpers and index numbers as GfGameUtil::setupNewGameParam). Each range is a loop of its own in the game (0x7100355248 to 0x7100355708),
      // with the title save buffer fetched before each one: the calls stay written out (ruling 8; the quality gate reports the repeated statements).
      saveData.unknown10.unknown002(title->getSaveBuffer()->unknown10, 2, 0x27a, 0x662);
      saveData.unknown10.unknown002(title->getSaveBuffer()->unknown10, 2, 0x25b, 0x279);
      saveData.unknown10.unknown002(title->getSaveBuffer()->unknown10, 1, 0xfa2, 0x11fa);
      saveData.unknown10.unknown003(title->getSaveBuffer()->unknown10, 1, 0x11fb, 0x4b0);
      saveData.unknown10.unknown002(title->getSaveBuffer()->unknown10, 1, 0x1, 0xfa1);
      saveData.unknown10.unknown003(title->getSaveBuffer()->unknown10, 1, 0x9230, 0x400);
      saveData.unknown10.unknown003(title->getSaveBuffer()->unknown10, 1, 0x3690, 15000);
      saveData.unknown10.unknown003(title->getSaveBuffer()->unknown10, 1, 0x9631, 0x400);
      saveData.unknown10.unknown003(title->getSaveBuffer()->unknown10, 1, 0xab67, 0x640);
      saveData.unknown10.unknown003(title->getSaveBuffer()->unknown10, 1, 0xb1a8, 0xa0);
      saveData.unknown10.unknown003(title->getSaveBuffer()->unknown10, 1, 0xb249, 0xa0);
      saveData.unknown10.unknown003(title->getSaveBuffer()->unknown10, 1, 0xb2ea, 0xa0);
      saveData.unknown10.unknown003(title->getSaveBuffer()->unknown10, 1, 0xb38b, 0xa0);
      saveData.unknown10.unknown003(title->getSaveBuffer()->unknown10, 1, 0xb42c, 0xa0);
      saveData.unknown10.unknown003(title->getSaveBuffer()->unknown10, 2, 0x94b7, 0x640);
      saveData.unknown10.unknown002(title->getSaveBuffer()->unknown10, 8, 0x12, 0x5ee);
      saveData.unknown10.unknown1097e4 = title->getSaveBuffer()->unknown10.unknown1097e4;
      saveData.unknown10.unknown1097e8 = title->getSaveBuffer()->unknown10.unknown1097e8;
      copyOrderParentQuests(saveData.unknown10, title->getSaveBuffer()->unknown10);
      saveData.unknown10.unknown26 = title->getSaveBuffer()->unknown10.unknown26;
      saveData.unknown10.unknown28 = title->getSaveBuffer()->unknown10.unknown28;
    }
  }
  GfFieldTime *fieldTime = GfFieldTime::get();
  if (fieldTime != nullptr) {
    saveData.unknown10.unknown1098c0 = fieldTime->getGameTime();
    saveData.unknown10.unknown1098c4 = fieldTime->getElapseTime();
    saveData.unknown10.unknown24 = fieldTime->isTimeStop();
    fieldTime->getRealTime(saveData.unknown08);
    fieldTime->getRealTime(saveData.unknown10.unknown10ad68);
  }
}

void GfGameUtilSaveData::getSaveData(SDataGame &dataGame) {
  dataGame = *GfDataManager::getDataGame();
  unknown001(dataGame.unknown1097f0);
}

void GfGameUtilSaveData::setTitleSaveData(const SDataSave &saveData) {
  if (tl::TitleMain::get() != nullptr) {
    SDataSave *titleSaveData = tl::TitleMain::get()->getSaveBuffer();
    titleSaveData->unknown00 = saveData.unknown00;
    titleSaveData->unknown08 = saveData.unknown08;
    titleSaveData->unknown10 = saveData.unknown10;
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
