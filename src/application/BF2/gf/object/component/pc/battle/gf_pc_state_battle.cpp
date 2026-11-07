#include "gf/object/component/pc/battle/gf_pc_state_battle.h"

#include "battle/battle_global.h"
#include "battle/character/battle_character.h"
#include "battle/utility_battle.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_battle.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {
struct GF_OBJ_HANDLE;

namespace pc {

bool StateBattle::Enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = GetProperty();
  property->unknown110_1 = true;
  const GfPropertyBattle *battle = GetBattlePropertyConst();
  bool isStart = battle->unknown14 == 3 && battle->unknown15 != 0 && battle->unknown16 != 0;
  GetBattleCharacter()->NotifyBattleStart(isStart);
  StateUtil::setEnableAgentBattle(*behavior, true);
  GF_OBJ_HANDLE *leader = btl::Utility::GetLeader();
  if (static_cast<GfObj *>(behavior->unknown08)->unknownf8 == leader) {
    GF_OBJ_HANDLE *target = StateUtil::getTarget(*behavior);
    btl::BattleGlobal *global = btl::BattleGlobal::get();
    global->unknown65de_4 = target != INVALID_HANDLE;
  }
  property->unknown470.unknown18 = false;
  GfObjAcc acc(static_cast<GfObj *>(behavior->unknown08));
  acc.setFlag(OBJ_FLAG_UNKNOWN_17, false);
  return true;
}

void StateBattle::Leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfComPropertyPc *property = GetProperty();
  property->unknown110_6 = false;
  GetBattleCharacter()->NotifyBattleEnd();
  StateUtil::setEnableAgentBattle(*behavior, false);
  StateUtil::setEnableGravity(*behavior, true);
  GF_OBJ_HANDLE *leader = btl::Utility::GetLeader();
  if (static_cast<GfObj *>(behavior->unknown08)->unknownf8 == leader) {
    btl::BattleGlobal::get()->unknown65de_4 = false;
  }
  StateUtil::setEnableFallDistChecker(*behavior, false);
  StateUtil::setEnableSpineRotate(*behavior, false, 0.2f);
  StateUtil::setSpineRotateAngles(*behavior, 0.0f, 0.0f);
  property->unknown470.unknown10 = 1.0f;
  StateUtil::setLipSpeed(*behavior, 1.0f);
  property->unknown110_1 = false;
  property->unknown111_7 = false;
  property->unknown470.unknown17 = false;
  property->unknown10.get()->unknown1b = false;
  GfObjAcc acc(static_cast<GfObj *>(behavior->unknown08));
  acc.setFlag(OBJ_FLAG_UNKNOWN_17, true);
}

void StateBattle::Update(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GF_OBJ_HANDLE *leader = btl::Utility::GetLeader();
  if (static_cast<GfObj *>(behavior->unknown08)->unknownf8 == leader) {
    if (behavior->getProperty()->unknown60.unknown08.test(INPUT_ID_CHANGE_CAMERA_MODE)) {
      if (StateUtil::isManualCamera()) {
        GF_OBJ_HANDLE *target = StateUtil::getTarget(*behavior);
        btl::BattleGlobal *global = btl::BattleGlobal::get();
        global->unknown65de_4 = target != INVALID_HANDLE;
      }
    } else if (btl::BattleGlobal::get()->unknown65de_4) {
      btl::BattleGlobal::get()->unknown65de_4 = !StateUtil::isManualCamera();
    }
  }
}

} // namespace pc
} // namespace gf
