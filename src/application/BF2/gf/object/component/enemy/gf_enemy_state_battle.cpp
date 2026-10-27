#include "gf/object/component/enemy/gf_enemy_state_battle.h"

#include "anm/anm_res_asm.h"
#include "battle/battle_global.h"
#include "battle/chain_attack_manager.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "battle/data_manager_battle.h"
#include "battle/misc_battle.h"
#include "battle/sp_attack_manager.h"
#include "battle/ui_manager_battle.h"
#include "framework/message/message_object.h"
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_com_property_enemy.h"
#include "gf/object/component/enemy/gf_enemy_asm_callback.h"
#include "gf/object/component/enemy/gf_enemy_battle_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"

namespace gf {
struct GF_OBJ_HANDLE;

bool GfStateBase::onEvent(void *owner, void *event) {
  unknown001 *stateEvent = static_cast<unknown001 *>(event);
  return recieveMessage(owner, stateEvent->unknown00, *stateEvent->unknown08);
}

bool GfStateBase::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) { return false; }

namespace enemy {

StateBattleBase::StateBattleBase() : mOwner(nullptr) {}

void StateBattleBase::enter(GfComBehaviorEnemy *behavior, ai::State *previous) {
  mOwner = behavior;
  mIsEntered = Enter(behavior, previous);
  mOwner = nullptr;
}

void StateBattleBase::leave(GfComBehaviorEnemy *behavior, ai::State *next) {
  mOwner = behavior;
  Leave(behavior, next);
  mOwner = nullptr;
}

void StateBattleBase::update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) {
  if (mIsEntered) {
    mOwner = behavior;
    btl::BattleCharacter *character = GetBattleCharacter();
    BeforeUpdate(character, behavior, info);
    Update(character, behavior, info);
    AfterUpdate(character, behavior, info);
    mOwner = nullptr;
  }
}

btl::BattleCharacter *StateBattleBase::GetBattleCharacter() {
  int id = mm::mtl::dynamicCast<GfComPropertyEnemy>(static_cast<GfComBehaviorEnemy *>(mOwner)->unknown08->unknown38[GfComPropertyEnemy::COMPONENT_INDEX])->unknown40._10;
  return btl::CharacterManager::get()->GetCharacterConst(id);
}

GfComPropertyEnemy *StateBattleBase::GetProperty() { return static_cast<GfComBehaviorEnemy *>(mOwner)->unknown08->getComponent<GfComPropertyEnemy>(); }

const GfComPropertyEnemy *StateBattleBase::GetPropertyConst() const { return static_cast<GfComBehaviorEnemy *>(mOwner)->unknown08->getComponent<GfComPropertyEnemy>(); }

GfEnemyBattleProperty *StateBattleBase::GetBattleProperty() { return &GetProperty()->unknown40; }

const GfEnemyBattleProperty *StateBattleBase::GetBattlePropertyConst() const { return &GetPropertyConst()->unknown40; }

const btl::EnemyParameter *StateBattleBase::GetEnemyParameter() { return GetProperty()->unknown40.GetEnemyParameterConst(); }

const btl::EnemyParameter *StateBattleBase::GetEnemyParameterConst() const { return GetPropertyConst()->unknown40.GetEnemyParameterConst(); }

bool StateBattleBase::IsDriver() const {
  const btl::EnemyParameter *parameter = GetEnemyParameterConst();
  if (!parameter->btl::CharacterParameter::m_invalidTarget) {
    return parameter->unknown10 != INVALID_HANDLE;
  }

  return false;
}

bool StateBattleBase::IsBlade() const { return GetEnemyParameterConst()->btl::CharacterParameter::m_invalidTarget; }

void StateBattleActionBase::BeforeUpdate(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) { character->BeforeUpdate(info); }

void StateBattleActionBase::Update(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) { character->Update(); }

bool StateBattleActionBase::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_OBJECT_NOTIFY_ASM_CALLBACK) {
    ProcMessageAsmCallback(static_cast<GfComBehaviorEnemy *>(owner), sender, static_cast<MsgObjectNotifyAsmCallback &>(message));
    return true;
  }

  return false;
}

void StateBattleActionBase::ProcMessageAsmCallback(GfComBehaviorEnemy *behavior, fw::MessageObject *sender, MsgObjectNotifyAsmCallback &message) {
  mOwner = behavior;
  GetBattleCharacter()->AsmCallback(message);
  mOwner = nullptr;
}

bool StateBattle::Enter(GfComBehaviorEnemy *behavior, ai::State *previous) {
  btl::BattleCharacter *character = GetBattleCharacter();
  character->NotifyBattleStart(false);
  character->SetAction(btl::BattleCharacter::ACTION_ID_UNKNOWN_2, false, true, 0, 0.0f);
  GfEnemyBattleProperty *property = GetBattleProperty();
  {
    mm::Vec3 position;
    btl::Misc::GetObjectTransform(character->GetObject(), position, btl::Misc::TRANS_TYPE_POSITION);
    property->unknown00 = position;
  }

  {
    DataParamAcc dataParam(static_cast<GfObj *>(behavior->unknown08)->unknownf8);
    const SDataEnemy *data = dataParam.getSDataEnemy();
    u32 arrangeId = data->unknown00;
    GfBdatChrEnArrange *arrange = GfBdatChrEnArrange::get();
    property->unknown1c = arrange->getChrEnArrangeBatAreaType(arrangeId);
    u32 area = arrange->getChrEnArrangeBatArea(arrangeId);
    property->unknown14 = area == 0 ? 60.0f : static_cast<f32>(area);
    u32 interval = arrange->getChrEnArrangeBatInterval(arrangeId);
    property->unknown18 = interval == 0 ? 40.0f : static_cast<f32>(interval);
    property->unknown1d = GfBdatRsc::get()->getRscEnActType(data->unknown44);
  }

  CheckInvalidTarget(character, behavior);
  unknown24 = 0.0f;
  return true;
}

void StateBattle::CheckInvalidTarget(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior) {
  GfObjAcc acc(static_cast<GfObj *>(behavior->unknown08)->unknownf8);
  if (acc.getBdatId() == 0xc0) {
    static_cast<GfObj *>(behavior->unknown08)->unknown110 &= ~4;
  }
}

void StateBattle::Leave(GfComBehaviorEnemy *behavior, ai::State *next) {
  GetBattleCharacter()->NotifyBattleEnd();
  GfObjAcc acc(static_cast<GfObj *>(behavior->unknown08));
  acc.setFlag(OBJ_FLAG_UNKNOWN_17, true);
}

void StateBattle::Update(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) {
  character->Update();
  if (!CheckReturnHome(character, behavior)) {
    if (character->unknowncc8 == 0x51c) {
      if (!btl::DataManager::get()->IsSpecialEffects(2)) {
        unknown24 = 0.0f;
      } else if (btl::BattleGlobal::get()->unknown5b00.get() == nullptr && btl::SpAttackManager::get()->unknown08.get() == nullptr && !btl::ChainAttackManager::get()->IsProc(true)) {
        unknown24 -= info.unknown04;
        if (unknown24 <= 0.0f) {
          unknown24 += 4.0f;
          btl::UIManager::get()->DispSystemMessageUI(character, 7, true);
        }
      }
    }
  } else if (character->IsDriver()) {
    const btl::CharacterParameter *parameter = character->GetCharacterParameterConst(true);
    if (parameter != nullptr) {
      btl::BattleCharacter *buddy = btl::CharacterManager::get()->GetCharacterConst(parameter->unknown10);
      if (buddy != nullptr) {
        buddy->StartBackHome();
      }
    }
  }
}

void registerAsmCallbackField(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm) { resAsm->sortAnnotation(1); }

} // namespace enemy
} // namespace gf
