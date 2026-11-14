// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/game/gf_game_mover_switcher.cpp.
#include "gf/game/gf_game_mover_switcher.h"

#include "fw/fw_transform.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/game/gf_game_ride.h"
#include "gf/game/gf_game_target.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_pc_property_battle.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {
struct GF_OBJ_HANDLE;

void GfGameMoverSwitcher::build(const GfSetupParam &) {
// __LINE__ of the operator new call is 0x22 in the game.
#line 34
  GfGameMoverSwitcher *switcher = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameMoverSwitcher();
  switcher->setup();
}

void GfGameMoverSwitcher::setup() { GfEvent::addEventCallback(this); }

void GfGameMoverSwitcher::destroy() {
  GfGameMoverSwitcher *switcher = get();
  if (switcher != nullptr) {
    switcher->cleanup();
    delete switcher;
  }
}

void GfGameMoverSwitcher::cleanup() { GfEvent::removeEventCallback(this); }

GfGameMoverSwitcher::GfGameMoverSwitcher() : unknown28(false) {}

GfGameMoverSwitcher::~GfGameMoverSwitcher() {}

void GfGameMoverSwitcher::gevPartyMemberOK(bool isMemberOk) {
  if (isMemberOk) {
    GF_OBJ_HANDLE *leader = GfGameManager::getPartyLeader();
    if (GfObjUtil::getObjType(leader) == OBJECT_TYPE_BLADE && !GfGameRide::isRideOnPair()) {
      unknown28 = true;
    } else {
      unknown28 = false;
    }
  }
}

void GfGameMoverSwitcher::gevPartyReturnFieldState(u32 state) {
  if (state == 0 && unknown28 && GfGameParty::getLeaderDriver() == GfGameManager::getControlMover()) {
    switchMover();
  }
}

void GfGameMoverSwitcher::switchMover() {
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  if (formation != nullptr) {
    formation->swapFormation(0, 1);
    for (u32 i = 0; i < 2; i++) {
      GfObj *obj = GfObjUtil::getObj(formation->unknown1a0[i].unknown08);
      if (obj != nullptr) {
        MsgPcFieldChangeControlMode mode(i);
        sendMessage(obj, mode);
        MsgPcFieldWarp warp;
        warp.unknown10.unknown10 = formation->unknowne0[0].unknown10;
        warp.unknown10.unknown00 = formation->unknown20[i];
        warp.unknown30 = true;
        sendMessage(obj, warp);
      }
    }
  }
}

bool GfGameMoverSwitcher::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_UNKNOWN_16777265) {
    procMsgGameSwitchControlMover(sender, static_cast<MsgGameSwitchControlMover &>(message));
    return true;
  }

  return false;
}

void GfGameMoverSwitcher::procMsgGameSwitchControlMover(fw::MessageObject *, MsgGameSwitchControlMover &message) {
  if (unknown28) {
    switchMover();
    if (message.unknown08 == 1) {
      GfGameTarget::disableTargetWithoutEnemy();
      GfObj *obj = GfObjUtil::getObj(GfGameManager::getPartyLeaderDriver());
      if (obj != nullptr) {
        MsgPcBattleStart start(0);
        sendMessage(obj, start);
      }
    }
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameMoverSwitcher>::~PtrSingleton();
