#include "gf/game/gf_game_unit.h"

#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_scene.h"
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

void GfGameUnit::createParty(PartyLeaderInfo &info) {
  GfGameScene *scene = GfGameScene::get();
  if (scene == nullptr) {
    return;
  }

  for (u32 partyId = 0; partyId < PARTY_UNKNOWN_3; partyId++) {
    u32 driver = GfGameParty::getDriverBdatId(partyId);
    DataParamAcc acc(OBJECT_TYPE_PC, driver, GIMMICK_TYPE_UNKNOWN_0);
    if (!acc.isValid() || GfDataDriver::isActivateUnuse(driver)) {
      GfObjUtil::destroy(GfGameParty::getHandleDriver(partyId));
    } else {
      GfInitParamDriver param;
      param.unknown08 = unknown030_1;
      param.unknown20 = partyId;
      param.m_bladeID = driver;
      param.unknown1a0 = scene->isRide(partyId);
      if (partyId == 0) {
        param.unknown1a8 = info.unknown00;
        if (info.unknown04) {
          param.unknown80 = true;
          param.unknown60 = info.unknown10;
          param.unknown70 = mm::Vec3(0.0f, info.unknown20, 0.0f);
        }
      }
      GfObjFactory::createDriver(param);
    }
  }
}

void GfGameUnit::destroyParty(const RQ_SETUP_PARTY &info, mm::mtl::FixedVector<GF_OBJ_HANDLE *, 32> *handles) {
  GfObjAcc leaderAcc(GfGameParty::getLeader());
  bool isChange = false;
  if (info.unknowncc != leaderAcc.getBdatId() && leaderAcc.isValid()) {
    isChange = info.unknowncc != 0;
  }
  if (info.unknowncc == 0 || (leaderAcc.isValid() && leaderAcc.getBdatId() != info.unknowncc)) {
    isChange = true;
  }

  for (u32 partyId = 0; partyId < PARTY_UNKNOWN_3; partyId++) {
    GfObjAcc driverAcc(GfGameParty::getHandleDriver(partyId));
    if (driverAcc.getDriverId() != info.unknown00[partyId].unknown00) {
      isChange = true;
      break;
    }
  }

  for (u32 partyId = 0; partyId < PARTY_UNKNOWN_3; partyId++) {
    GfObjAcc driverAcc(GfGameParty::getHandleDriver(partyId));
    if (!driverAcc.isValid()) {
      continue;
    }

    const RQ_SETUP_PARTY::Member &member = info.unknown00[partyId];
    bool isForce = member.unknown12;
    bool isDiffer = driverAcc.getDriverId() != member.unknown00;
    bool isDestroy = false;
    if (isDiffer || isChange || isForce) {
      GfObjUtil::destroy(driverAcc.getHandle());
      if (handles != nullptr) {
        handles->push_back(driverAcc.getHandle());
      }
      int setId = GfSelectBlade::getStartBattleSetId(partyId);
      if (setId >= 0) {
        DataParamAcc paramAcc(driverAcc.getHandle());
        paramAcc.setBladeSet(setId);
      }
      isDestroy = true;
    }

    int bladeNum = GfDataDriver::getMaxSetBladeNum(driverAcc.getDriverId());
    for (int slot = 0; slot < bladeNum; slot++) {
      GfObjAcc bladeAcc(GfGameParty::getHandleBlade(partyId, slot));
      bool isRemove = true;
      if (!isChange && !isDestroy) {
        for (int index = 0; index < bladeNum; index++) {
          if (bladeAcc.getBladeId() == member.unknown08[index]) {
            isRemove = false;
            break;
          }
        }
      }
      if (isRemove) {
        GfObjUtil::destroy(bladeAcc.getHandle());
        if (handles != nullptr) {
          handles->push_back(bladeAcc.getHandle());
        }
        GfGameParty::destroyHandleWeapon(partyId, slot);
      }
    }
  }
}

} // namespace gf
