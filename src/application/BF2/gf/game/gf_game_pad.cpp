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
#include "mm_mtl/delegate.h" // IWYU pragma: keep

namespace gf {

constexpr u32 EMERGENCY_ESCAPE_UNKNOWN_16632 = 0x40f8; // Inferred role: emergency escape buttons; original name unknown.
constexpr u32 EMERGENCY_ESCAPE_UNKNOWN_150 = 150;      // Inferred role: emergency escape frame; original name unknown.
constexpr u32 COND_UNKNOWN_2654 = 2654;                // Inferred role: cond disable emergency escape; original name unknown.
constexpr u32 SE_UNKNOWN_3 = 3;                        // Inferred role: se open menu; original name unknown.
constexpr u32 SE_UNKNOWN_7 = 7;                        // Inferred role: se disable; original name unknown.
constexpr u32 TYPE_UNKNOWN_1 = 1;                      // Inferred role: open menu type; original name unknown.

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
  unknown18.bind(0, 4, getAllocator(ALLOCATOR_UNKNOWN_0));
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
  if ((unknown50.unknown00 & EMERGENCY_ESCAPE_UNKNOWN_16632) != EMERGENCY_ESCAPE_UNKNOWN_16632) {
    unknown1a0 = 0;
    return;
  }

  if (++unknown1a0 > EMERGENCY_ESCAPE_UNKNOWN_150) {
    unknown1a0 = 0;
    if (!GfGameCond::isGameCond(COND_UNKNOWN_2654)) {
      GfObj *obj = GfObjUtil::getObj(GfGameManager::getPartyLeader());
      MsgObjectDead message(DEAD_TYPE_UNKNOWN_4);
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
    GfMenuObjUtil::playSE(SE_UNKNOWN_3);
    GfPlayFactory::createOpenMenu2(TYPE_UNKNOWN_1, MAINMENU_UNKNOWN_0, nullptr);
  } else {
    GfMenuObjUtil::playSE(SE_UNKNOWN_7);
  }
}

void GfGamePad::eventInGameOpenSystemMenu() {
  if (GfGameManager::isEnableOpenMainMenu() && GfGameManager::isEnableOpenMainMenuSequence()) {
    GfMenuObjUtil::playSE(SE_UNKNOWN_3);
    GfPlayFactory::createOpenMenu2(TYPE_UNKNOWN_1, MAINMENU_UNKNOWN_1, nullptr);
  } else {
    GfMenuObjUtil::playSE(SE_UNKNOWN_7);
  }
}

void GfGamePad::eventInGameOpenSkipTravelMenu() {
  if (GfGameManager::isEnableOpenMainMenu() && GfGameManager::isEnableOpenMainMenuSequence()) {
    GfMenuObjUtil::playSE(SE_UNKNOWN_3);
    GfPlayFactory::createOpenMenu2(TYPE_UNKNOWN_1, MAINMENU_UNKNOWN_2, nullptr);
  } else {
    GfMenuObjUtil::playSE(SE_UNKNOWN_7);
  }
}

void GfGamePad::gevExecState(EXEC_STATE) {}

void GfGamePad::gevGameState(GF_STATE, GF_STATE) {}

void GfGamePad::eventInGameOpenQuestListMenu() {
  if (GfGameManager::isControlFree() && !GfGameManager::isBattle() && !GfGameManager::isControlMoverBattle() && !GfGameManager::isStopMainMenuOpenForGimmick() &&
      GfQuestInfo::isDispUI(GfQuestManager::getCurrentQuest(QTYPE_UNKNOWN_0))) {
    GfPlayFactory::createMenuQuestList();
  }
}

} // namespace gf

template void mm::mtl::Delegate<void()>::memberFuncInvoker<gf::GfGamePad>(const mm::mtl::Delegate<void()> *);
