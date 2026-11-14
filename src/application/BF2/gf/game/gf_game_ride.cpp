#include "gf/game/gf_game_ride.h"

#include "framework/object/component_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_target.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_pc_property_battle.h"
#include "gf/object/component/pc/plugin/gf_pc_attach_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_damage_plugin.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"

namespace gf {

void GfGameRide::build(const GfSetupParam &) {
// __LINE__ of the operator new call is 0x28 in the game.
#line 40
  GfGameRide *ride = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameRide();
  ride->setup();
}

void GfGameRide::setup() { GfEvent::addEventCallback(this); }

void GfGameRide::destroy() {
  GfGameRide *ride = get();
  ride->cleanup();
  delete ride;
}

void GfGameRide::cleanup() { GfEvent::removeEventCallback(this); }

bool GfGameRide::testRideOn() {
  GfGameRide *ride = get();
  if (ride->unknown28 != unknown020) {
    return ride->unknown30 != unknown020;
  }

  return false;
}

void GfGameRide::setRideOn(bool isRide) {
  GfGameRide *ride = get();
  if (isRide) {
    ride->rideOn();
  } else {
    ride->getDown(GfGameManager::getPartyLeader());
  }
}

void GfGameRide::rideOn() {
  if (unknown28 != unknown020 && unknown30 != unknown020) {
    getDown(GfGameManager::getPartyLeader());
  }
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  if (formation == nullptr) {
    return;
  }
  GF_OBJ_HANDLE *leader = formation->unknown1a0[0].unknown08;
  u32 partyId = GfGameParty::getPartyId(leader);
  if (partyId == PARTY_UNKNOWN_4294967295) {
    return;
  }
  unknown30 = GfGameParty::getHandleDriver(partyId);
  unknown28 = GfGameParty::getHandleBlade(partyId, -1);
  if (unknown28 == unknown020 || unknown30 == unknown020) {
    unknown28 = unknown020;
    unknown30 = unknown020;
    return;
  }
  if (leader == unknown30) {
    GfObj *vehicleObj = GfObjUtil::getObj(unknown28);
    if (vehicleObj != nullptr) {
      GfObjProperty *property = GfObjUtil::getProperty(unknown30);
      unknown070 *move = property != nullptr ? property->unknown18 : nullptr;
      if (move != nullptr) {
        MsgPcFieldWarp warp;
        warp.unknown10.unknown00 = move->unknown10;
        warp.unknown10.unknown10 = move->unknown20;
        warp.unknown30 = true;
        sendMessage(vehicleObj, warp);
      }
      MsgPcFieldChangeControlMode mode(0);
      sendMessage(vehicleObj, mode);
    }
    formation->swapFormation(unknown30, unknown28);
  }
  GfObj *driverObj = GfObjUtil::getObj(unknown30);
  if (driverObj == nullptr) {
    return;
  }
  MsgPcFieldGetFallMaxHeight getFallMaxHeight;
  sendMessage(driverObj, getFallMaxHeight);
  GfObjUtil::changeLayer(unknown30, 5);
  GfComBehaviorPc *behavior = driverObj->getComponent<GfComBehaviorPc>();
  if (behavior != nullptr) {
    pc::AttachPlugin *plugin = behavior->unknown001<pc::AttachPlugin>(12);
    if (plugin != nullptr) {
      plugin->setActivate(false);
    }
  }
  GfObjUtil::mountToBone(unknown30, unknown28, "EX_ride");
  GfComTransform *transform = mm::mtl::dynamicCast<GfComTransform>(driverObj->unknown38[GfComTransform::COMPONENT_INDEX]);
  fw::ReferenceFrame *frame = transform->unknown10.operator->();
  frame->invalidateWorld();
  frame->unknown20.unknown00 = mm::Vec3::zero;
  frame->unknown20.unknown10 = mm::Quat::identity;
  transform->unknown10->syncWorldTransform();
  MsgPcFieldChangeControlMode mode(2);
  sendMessage(driverObj, mode);
  if (getFallMaxHeight.unknown0c) {
    GfObj *vehicleObj = GfObjUtil::getObj(unknown28);
    if (vehicleObj != nullptr) {
      MsgPcFieldSetFallMaxHeight setFallMaxHeight(getFallMaxHeight.unknown08);
      sendMessage(vehicleObj, setFallMaxHeight);
    }
  }
}

void GfGameRide::getDown(GF_OBJ_HANDLE *handle) {
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  if (formation == nullptr || unknown28 == unknown020 || unknown30 == unknown020) {
    return;
  }
  GfObj *driverObj = GfObjUtil::getObj(unknown30);
  if (driverObj != nullptr) {
    MsgPcFieldChangeControlMode mode(unknown30 != handle);
    sendMessage(driverObj, mode);
  }
  GfObjUtil::changeLayer(unknown30, 4);
  GfObjUtil::unmountFromBone(unknown30);
  bool isOnCloud;
  f32 cloudHeight;
  f32 cloudLimit;
  if (unknown30 == handle) {
    unknown070 *move = GfObjUtil::getProperty(unknown28)->unknown18;
    isOnCloud = move->unknown00 == PROPERTY_MOVE_UNKNOWN_2;
    cloudHeight = move->unknown74;
    cloudLimit = move->unknown78;
    formation->swapFormation(unknown30, unknown28);
    GfObj *vehicleObj = GfObjUtil::getObj(unknown28);
    if (vehicleObj != nullptr) {
      {
        MsgPcFieldChangeControlMode mode(1);
        sendMessage(vehicleObj, mode);
      }
      u32 playerId = formation->findPlayer(unknown28);
      MsgPcFieldWarp warp;
      warp.unknown10.unknown10 = formation->unknowne0[0].unknown10;
      warp.unknown10.unknown00 = formation->unknown20[playerId];
      warp.unknown30 = true;
      sendMessage(vehicleObj, warp);
    }
  } else {
    cloudLimit = 0.0f;
    isOnCloud = false;
    cloudHeight = cloudLimit;
  }
  formation = GfGamePlayerFormation::get();
  if (formation != nullptr) {
    GfObj *obj = GfObjUtil::getObj(unknown30);
    if (obj != nullptr) {
      u32 playerId = formation->findPlayer(unknown30);
      MsgPcFieldWarp warp;
      warp.unknown10.unknown10 = formation->unknowne0[playerId].unknown10;
      warp.unknown10.unknown00 = formation->unknown20[playerId];
      if (isOnCloud) {
        f32 height = GfObjUtil::getProperty(unknown30)->unknown18->unknownb8;
        if (cloudLimit >= height) {
          warp.unknown10.unknown00.y = cloudHeight - height;
        } else {
          warp.unknown10.unknown00.y = cloudHeight - cloudLimit;
        }
      }
      warp.unknown30 = true;
      sendMessage(obj, warp);
    }
  }
  unknown28 = unknown020;
  unknown30 = unknown020;
}

bool GfGameRide::isVehicle(GF_OBJ_HANDLE *handle) {
  if (handle != unknown020) {
    return get()->unknown28 == handle;
  }

  return false;
}

bool GfGameRide::isRider(GF_OBJ_HANDLE *handle) {
  if (handle != unknown020) {
    return get()->unknown30 == handle;
  }

  return false;
}

GfGameRide::GfGameRide() : unknown28(unknown020), unknown30(unknown020) {}

GfGameRide::~GfGameRide() {}

void GfGameRide::resetHandles() {
  unknown28 = unknown020;
  unknown30 = unknown020;
}

void GfGameRide::gevPartyReturnFieldState(u32 state) {
  if (state == 0) {
    GfObjSetup *setup = GfObjUtil::getObjSetup(GfGameManager::getPartyLeaderDriver());
    if (setup != nullptr && GfGameScene::get() != nullptr && GfGameScene::get()->isRideParty(setup->unknown14) && (unknown28 == unknown020 || unknown30 == unknown020)) {
      rideOn();
    }
  }
}

bool GfGameRide::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == EVENT_UNKNOWN_16777264) {
    procMsgGameRideEvent(sender, static_cast<MsgGameRideEvent &>(message));
    return true;
  }

  return false;
}

void GfGameRide::procMsgGameRideEvent(fw::MessageObject *, MsgGameRideEvent &message) {
  GfObjSetup *setup = GfObjUtil::getObjSetup(GfGameManager::getPartyLeaderDriver());
  if (setup != nullptr && GfGameScene::get() != nullptr && GfGameScene::get()->isRideParty(setup->unknown14)) {
    switch (message.unknown08) {
    case RIDE_EVENT_UNKNOWN_0:
      rideOn();
      break;
    case RIDE_EVENT_UNKNOWN_1: {
      GF_OBJ_HANDLE *driver = GfGameManager::getPartyLeaderDriver();
      getDown(driver);
      if (get()->unknown28 == unknown020 || get()->unknown30 == unknown020) {
        GfGameTarget::disableTargetWithoutEnemy();
        GfObj *obj = GfObjUtil::getObj(driver);
        if (obj != nullptr) {
          MsgPcBattleStart start(0);
          sendMessage(obj, start);
        }
      }
      break;
    }
    case RIDE_EVENT_UNKNOWN_2:
      getDown(GfGameManager::getPartyLeaderDriver());
      break;
    }
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameRide>::~PtrSingleton();
