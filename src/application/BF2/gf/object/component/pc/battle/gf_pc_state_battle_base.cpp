#include "gf/object/component/pc/battle/gf_pc_state_battle_base.h"

#include "battle/battle_global.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_battle.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_battle.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

StateBattleBase::StateBattleBase() : unknown18(nullptr), unknown21(false) {}

void StateBattleBase::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  unknown18 = behavior;
  unknown20 = Enter(behavior, previous);
  unknown18 = nullptr;
}

void StateBattleBase::leave(GfComBehaviorPc *behavior, ai::State *next) {
  unknown18 = behavior;
  Leave(behavior, next);
  unknown18 = nullptr;
}

void StateBattleBase::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  unknown21 = false;
  if (unknown20) {
    unknown18 = behavior;
    btl::BattleCharacter *character = GetBattleCharacter();
    BeforeUpdate(character, behavior, info);
    Update(character, behavior, info);
    AfterUpdate(character, behavior, info);
    unknown18 = nullptr;
  }
}

btl::BattleCharacter *StateBattleBase::GetBattleCharacter() {
  int id = unknown18->getProperty()->unknown470.unknown08;
  return btl::CharacterManager::get()->GetCharacterConst(id);
}

void StateBattleBase::ChangeState(STATE_ID state, int param) {
  if (unknown08 != state) {
    unknown18->getProperty()->unknown470.unknown0c = param;
    reqState(state);
    unknown21 = true;
  }
}

GfPropertyBattle *StateBattleBase::GetBattleProperty() { return &GetProperty()->unknown470; }

GfComPropertyPc *StateBattleBase::GetProperty() { return unknown18->unknown08->getComponent<GfComPropertyPc>(); }

const GfComPropertyPc *StateBattleBase::GetPropertyConst() const { return unknown18->unknown08->getComponent<GfComPropertyPc>(); }

const GfPropertyBattle *StateBattleBase::GetBattlePropertyConst() const { return &GetPropertyConst()->unknown470; }

const btl::PlayerParameter *StateBattleBase::GetPlayerParameter() { return GetProperty()->unknown470.GetPlayerParameterConst(); }

const btl::PlayerParameter *StateBattleBase::GetPlayerParameterConst() const { return GetPropertyConst()->unknown470.GetPlayerParameterConst(); }

bool StateBattleBase::IsDriver() const {
  const btl::PlayerParameter *parameter = GetPlayerParameterConst();
  if (!parameter->m_invalidTarget) {
    return parameter->unknown10 != unknown020;
  }

  return false;
}

bool StateBattleBase::IsBlade() const { return GetPlayerParameterConst()->m_invalidTarget; }

bool StateBattleBase::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_OBJECT_UNKNOWN_16777271) {
    procMsgObjectNotifyDamage(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgObjectNotifyDamage &>(message));
  } else if (message.unknown00 == MSG_OBJECT_UNKNOWN_16777272) {
    procMsgObjectNotifyDead(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgObjectNotifyDead &>(message));
  } else if (message.unknown00 == MSG_OBJECT_UNKNOWN_16777273) {
    procMsgObjectNotifyHealHp(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgObjectNotifyHealHp &>(message));
  } else {
    return false;
  }

  return true;
}

void StateBattleBase::procMsgObjectNotifyDamage(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyDamage &message) {
  bool isOwnerSet = false;
  if (unknown18 == nullptr) {
    unknown18 = behavior;
    isOwnerSet = true;
  }
  btl::BattleCharacter *character = GetBattleCharacter();
  if (character != nullptr) {
    character->NotifySufferDamage(message);
    if (isOwnerSet) {
      unknown18 = nullptr;
    }
  }
}

void StateBattleBase::procMsgObjectNotifyDead(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyDead &message) {
  bool isOwnerSet = false;
  if (unknown18 == nullptr) {
    unknown18 = behavior;
    isOwnerSet = true;
  }
  btl::BattleCharacter *character = GetBattleCharacter();
  if (character != nullptr) {
    int type = message.unknown08;
    if (type == DEAD_TYPE_UNKNOWN_4 && character->IsControlCharacter()) {
      btl::BattleGlobal::get()->unknown65df_7 = true;
    }
    if (!character->IsBlade()) {
      StateUtil::notifyDead(*behavior, message, type == DEAD_TYPE_UNKNOWN_4);
    }
    character->NotifyDead(message);
  }
  if (isOwnerSet) {
    unknown18 = nullptr;
  }
}

void StateBattleBase::procMsgObjectNotifyHealHp(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyHealHp &message) {
  if (message.unknown10 == 0) {
    StateUtil::notifyRevival(*behavior, message);
    MsgPcFieldRelaySurvive relay(&message);
    StateUtil::sendMessageToBuddy(*behavior, relay);
  }
}

bool StateBattleActionBase::Enter(GfComBehaviorPc *behavior, ai::State *previous) {
  STATE_ID state = static_cast<STATE_ID>(unknown08);
  if (StateUtilBattle::IsBattleState(state)) {
    btl::BattleCharacter::ACTION_ID action = StateUtilBattle::ConversionStateToAction(state);
    GfPropertyBattle *property = GetBattleProperty();
    int param;
    if (action == btl::BattleCharacter::ACTION_ID_IDLE || action == btl::BattleCharacter::ACTION_ID_UNKNOWN_17) {
      param = property->unknown0c;
    } else {
      param = 0;
    }
    property->unknown0c = 0;
    GetBattleCharacter()->SetAction(action, false, true, param, 0.0f);
  }

  return true;
}

void StateBattleActionBase::BeforeUpdate(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  character->BeforeUpdate(info);
  GfComPropertyPc *property = GetProperty();
  property->unknown80 = mm::Vec3::zero;
  property->unknown94 = 0.0f;
}

bool StateBattleActionBase::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_OBJECT_UNKNOWN_16777279) {
    ProcMessageAsmCallback(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgObjectNotifyAsmCallback &>(message));
  } else if (message.unknown00 == MSG_PC_BATTLE_UNKNOWN_16777227) {
    ProcMessageBattleEnd(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcBattleEnd &>(message));
  } else {
    return false;
  }

  return true;
}

void StateBattleActionBase::ProcMessageAsmCallback(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyAsmCallback &message) {
  unknown18 = behavior;
  GetBattleCharacter()->AsmCallback(message);
  unknown18 = nullptr;
}

void StateBattleActionBase::ProcMessageBattleEnd(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcBattleEnd &message) {
  unknown18 = behavior;
  GetBattleCharacter()->SetExitBattle(true, false);
  unknown18 = nullptr;
}

} // namespace pc
} // namespace gf
