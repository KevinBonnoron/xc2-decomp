#include "gf/game/gf_game_pad.h"

#include "gf/data/gf_bdat_quest.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

constexpr u32 EMERGENCY_ESCAPE_BUTTONS = 0x40f8;
constexpr u32 EMERGENCY_ESCAPE_FRAME = 150;
constexpr u32 COND_DISABLE_EMERGENCY_ESCAPE = 2654;
constexpr u32 SE_OPEN_MENU = 3;
constexpr u32 SE_DISABLE = 7;
constexpr u32 OPEN_MENU_TYPE = 1;

void GfGamePad::initialize(const GfSetupParam &) {
  GfEvent::addEventCallback(this);
  unknown10 = true;
  changePadInputMode();
}

GfGamePad::~GfGamePad() {}

void GfGamePad::clear() {}

void GfGamePad::destroy() {
  GfGamePad *pad = get();
  pad->finalize();
  delete pad;
}

void GfGamePad::finalize() {
  unknown18.unbind();
  GfEvent::removeEventCallback(this);
  unknown10 = false;
}

void GfGamePad::changePadInputMode() {
  unknown18.unbind();
  unknown18.bind(0, 4, getAllocator(ALLOCATOR_DEFAULT));
  if (GfManager::isExecModeDebug() || GfManager::isExecModeScenarioGame()) {
    if (GfGameManager::isEvent(false) || GfGameManager::isTalking()) {
      unknown18.bindAction("pause_event", this, &GfGamePad::eventInGameEventPause);
    } else if (GfGameManager::isEnableOpenMainMenuSequence()) {
      unknown18.bindAction("boot_mainmenu", this, &GfGamePad::eventInGameOpenMainMenu);
      unknown18.bindAction("call_system", this, &GfGamePad::eventInGameOpenSystemMenu);
      unknown18.bindAction("call_skiptravel", this, &GfGamePad::eventInGameOpenSkipTravelMenu);
    }
  } else if (GfManager::isExecModeThater()) {
    if (GfGameManager::isEvent(false) || GfGameManager::isTalking()) {
      unknown18.bindAction("pause_event", this, &GfGamePad::eventInGameEventPause);
    }
  }
}

bool GfGamePad::isInitialized() {
  GfGamePad *pad = get();
  if (pad == nullptr) {
    return false;
  }

  return pad->unknown10;
}

void GfGamePad::clearUniqParams() { unknown11 = false; }

u32 GfGamePad::getPlayerPadId() { return 0; }

void GfGamePad::checkEmergencyEscape() {
  if ((unknown50.hold & EMERGENCY_ESCAPE_BUTTONS) != EMERGENCY_ESCAPE_BUTTONS) {
    unknown1a0 = 0;
    return;
  }

  if (++unknown1a0 > EMERGENCY_ESCAPE_FRAME) {
    unknown1a0 = 0;
    if (!GfGameCond::isGameCond(COND_DISABLE_EMERGENCY_ESCAPE)) {
      GfObj *obj = GfObjUtil::getObj(GfGameManager::getPartyLeader());
      MsgObjectDead message(DEAD_TYPE_EMERGENCY_ESCAPE);
      obj->sendMessage(obj, message);
    }
  }
}

const fw::PadData *GfGamePad::getPadPlayer() {
  GfGamePad *pad = get();
  if (pad != nullptr) {
    return &pad->unknown50;
  }

  return fw::PadManager::getControlPadData(0);
}

bool GfGamePad::isEventPause() {
  GfGamePad *pad = get();
  if (pad == nullptr) {
    return false;
  }

  return pad->unknown11;
}

void GfGamePad::setInterruptPadOnForDebug(DWPAD dwpad) {
  GfGamePad *pad = get();
  if (pad == nullptr) {
    return;
  }

  if (pad->unknown98.size() != pad->unknown98.capacity()) {
    pad->unknown98.push_back(dwpad);
  }
}

void GfGamePad::eventInGameEventPause() { unknown11 = true; }

void GfGamePad::eventInGameOpenMainMenu() {
  if (GfGameManager::isEnableOpenMainMenu() && GfGameManager::isEnableOpenMainMenuSequence()) {
    GfMenuObjUtil::playSE(SE_OPEN_MENU);
    GfPlayFactory::createOpenMenu2(OPEN_MENU_TYPE, MAINMENU_TOP, nullptr);
  } else {
    GfMenuObjUtil::playSE(SE_DISABLE);
  }
}

void GfGamePad::eventInGameOpenSystemMenu() {
  if (GfGameManager::isEnableOpenMainMenu() && GfGameManager::isEnableOpenMainMenuSequence()) {
    GfMenuObjUtil::playSE(SE_OPEN_MENU);
    GfPlayFactory::createOpenMenu2(OPEN_MENU_TYPE, MAINMENU_SYSTEM, nullptr);
  } else {
    GfMenuObjUtil::playSE(SE_DISABLE);
  }
}

void GfGamePad::eventInGameOpenSkipTravelMenu() {
  if (GfGameManager::isEnableOpenMainMenu() && GfGameManager::isEnableOpenMainMenuSequence()) {
    GfMenuObjUtil::playSE(SE_OPEN_MENU);
    GfPlayFactory::createOpenMenu2(OPEN_MENU_TYPE, MAINMENU_SKIP_TRAVEL, nullptr);
  } else {
    GfMenuObjUtil::playSE(SE_DISABLE);
  }
}

void GfGamePad::gevExecState(EXEC_STATE) {}

void GfGamePad::gevGameState(GF_STATE, GF_STATE) {}

void GfGamePad::eventInGameOpenQuestListMenu() {
  if (GfGameManager::isControlFree() && !GfGameManager::isBattle() && !GfGameManager::isControlMoverBattle() && !GfGameManager::isStopMainMenuOpenForGimmick() &&
      GfQuestInfo::isDispUI(GfQuestManager::getCurrentQuest(QTYPE_NONE))) {
    GfPlayFactory::createMenuQuestList();
  }
}

} // namespace gf
