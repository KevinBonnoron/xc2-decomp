#include "battle/character/battle_character.h"

#include <float.h>

#include "battle/battle_global.h"
#include "battle/blade_arts_manager.h"
#include "battle/btl_system_balance_access.h"
#include "battle/button_challenge.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "battle/data_manager_battle.h"
#include "battle/group_data.h"
#include "battle/hate_ring_manager.h"
#include "battle/misc_battle.h"
#include "battle/talk_manager_battle.h"
#include "battle/ui_manager_battle.h"
#include "battle/utility_battle.h"
#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_party.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/effect/gf_com_effect_caster.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "ml/rand.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/fixed_array.h"

namespace btl {

constexpr int ALPHA_RATE_NUM = 7;
constexpr f32 PAUSE_DT = 0.000001f;
constexpr u16 ANIMATION_INVALID = 39;
constexpr int ALPHA_WEAPON_FIRST = 12;
constexpr int ALPHA_WEAPON_LAST = 16;
constexpr int ALPHA_PROC_WEAPON = 6;
constexpr int ALPHA_PROC_LAST = 11;
constexpr int SE_HIT_ATTRIBUTE = 9;
constexpr int SE_HIT_BULLET = 17;
constexpr int SLOT_ALL = -17;
constexpr f32 DELAY_VOICE_TIME_SCALE = 4096.0f;
constexpr int BUFF_EFFECT_TARGET_LOCK = 8;
constexpr int COMMAND_NUM = 10;
constexpr u16 ACTION_PHASE_BLADE_ARTS_MOVE = 8;
constexpr u16 ACTION_PHASE_BLADE_CHANGE_RETURN = 6;
constexpr int AI_STATE_ACTIVE = 1;
constexpr f32 AI_SCOUT_TIME = 10.0f;
constexpr u32 BLADE_CHANGE_ACTIONS = 0xd2;
constexpr int BLADE_SUPPORT_CONDITION_HATE_ELSE = 8;

void BattleCharacter::ResetHateRingData() {
  if (!m_player && unknown118 != gf::INVALID_HANDLE && unknownf7d >= 0) {
    HateRingManager::get()->SetData(unknownf7d, unknown118, -1);
  }
}

void BattleCharacter::ResetDelayVoice() { unknowndd0 = -1; }

void BattleCharacter::ResetCustomVoiceData() {
  unknownf5c = 0;
  unknownf60 = 0;
  for (int i = 0; i < 3; i++) {
    unknownf64[i].unknown00 = 0;
    unknownf64[i].unknown01 = 0;
  }
}

const CharacterParameter *BattleCharacter::GetCharacterParameterConst(bool) const {
  if (unknown168 == nullptr) {
    if (unknownf6a < 0) {
      return nullptr;
    }
    unknown168 = DataManager::get()->GetCharacterParameterConst(unknownf6a);
  }
  return unknown168;
}

bool BattleCharacter::IsPlayer() const { return m_player; }

bool BattleCharacter::IsBlade() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && parameter->m_invalidTarget;
}

gf::GfObj *BattleCharacter::GetObject() const { return gf::GfObjUtil::getObj(unknown118); }

bool BattleCharacter::IsEnemy() const { return !m_player; }

bool BattleCharacter::IsDriver() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && !parameter->m_invalidTarget && parameter->unknown10 != gf::INVALID_HANDLE;
}

CharacterParameter *BattleCharacter::GetCharacterParameter(bool isBattle) { return const_cast<CharacterParameter *>(GetCharacterParameterConst(isBattle)); }

gf::GF_OBJ_HANDLE *BattleCharacter::GetControlCharacterHandle() const { return Utility::GetControlCharacterHandle(); }

gf::GfObj *BattleCharacter::GetObject(gf::GF_OBJ_HANDLE *handle) const { return gf::GfObjUtil::getObj(handle); }

bool BattleCharacter::IsBattle() const { return m_battle; }

void BattleCharacter::ResetAnimationMoveDistance() {
  for (int i = 0; i < 20; i++) {
    unknownce0[i].unknown04 = ANIMATION_INVALID;
  }
}

void BattleCharacter::ResetAlphaAnimation() {
  for (int i = 0; i < 17; i++) {
    unknowndd8[i].unknown10 = 0.0f;
    unknowndd8[i].unknown0c = 0.0f;
    unknowndd8[i].unknown04 = -1.0f;
    unknowndd8[i].unknown08 = -1.0f;
    unknowndd8[i].unknown00 = -1.0f;
  }
}

void BattleCharacter::InitializeEnhanceProcData(bool isFinalizeArtsEffect) {
  for (f32 &timer : unknown1108) {
    timer = 0.0f;
  }
  if (isFinalizeArtsEffect) {
    FinalizeArtsEffect(true);
  }
}

void BattleCharacter::DeleteKizunaAuraEffect() {
  if (unknown130[EFFECT_ID_KIZUNA_AURA] != 0) {
    if (gf::GfGameManager::isPlayEvent()) {
      fw::EffectManager::get()->remove(unknown130[EFFECT_ID_KIZUNA_AURA]);
    } else {
      fw::EffectManager::get()->dead(unknown130[EFFECT_ID_KIZUNA_AURA]);
    }
    unknown130[EFFECT_ID_KIZUNA_AURA] = 0;
  }
}

void BattleCharacter::CancelButtonChallenge() {
  if (unknown10c0 != 0) {
    BattleGlobal::get()->unknown5e8.Cancel(unknown10c0);
    unknown10c0 = 0;
  }
}

bool BattleCharacter::IsBound() const {
  if ((unknownf90 & 8) == 0 && !Misc::IsInWater(unknown10, 5.0f)) {
    return ((1ull << unknownf7c) & 0xe00000000ull) != 0;
  }
  return false;
}

void BattleCharacter::SetRimBloom(RIMBLOOM_ID id, bool isEnable) {
  if (id == 0) {
    if (isEnable) {
      unknownf7a |= 1;
    } else {
      unknownf7a &= 0xfffe;
    }
  } else if (static_cast<u32>(id - 1) < 8) {
    unknownf7a &= 0xfe01;
    if (isEnable) {
      unknownf7a |= 1u << id;
    }
  }
}

bool BattleCharacter::IsDispWeaponAlpha(int alpha) const {
  if (alpha >= ALPHA_WEAPON_FIRST && alpha <= ALPHA_WEAPON_LAST) {
    f32 rate = unknowndd8[alpha].unknown08;
    return rate < 0.0f || rate > 0.0f;
  }
  return false;
}

bool BattleCharacter::IsBoss() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && parameter->IsBoss();
}

bool BattleCharacter::IsNamed() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && parameter->IsNamed();
}

bool BattleCharacter::IsBossOrNamed() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && parameter->IsBossOrNamed();
}

bool BattleCharacter::IsMove() const { return unknown107c == ACTION_ID_MOVE || unknown1178 == AI_STATE_ACTIVE; }

bool BattleCharacter::IsMoveHealPot() const {
  if (unknown107c == ACTION_ID_MOVE && unknown1178 == AI_STATE_ACTIVE && unknown1160.unknown00 == 20) {
    return true;
  }
  return false;
}

int BattleCharacter::GetSeType(int type, int attr) const {
  int seType = 1;
  switch (type) {
  case 60000:
    break;
  case 60001:
    seType = 2;
    break;
  case 60002:
    seType = Utility::GetWeaponSeType(unknownf7f);
    break;
  case 60003:
    seType = Utility::GetAttrSeType(attr);
    break;
  case 60004:
    seType = unknownf78_0;
    break;
  case 0:
    return 0;
  default:
    seType = type;
    break;
  }
  return seType;
}

int BattleCharacter::GetKizunaStage(f32 *rate) const {
  if (Utility::IsThirdCharacter(unknown118)) {
    return 6;
  }
  if (rate != nullptr) {
    *rate = 0.0f;
  }

  const CharacterParameter *parameter = GetCharacterParameterConst(false);
  if (parameter == nullptr) {
    return 0;
  }
  int partyId = parameter->unknown1c;
  if (!DataManager::get()->unknown001(partyId)) {
    return 3;
  }
  return DataManager::get()->unknown10758[partyId].GetBladeDataConst(-1)->GetKizunaStage(rate);
}

int BattleCharacter::GetHateEnemyNum() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(false);
  if (parameter == nullptr) {
    return 0;
  }
  return HateRingManager::get()->GetHateEnemyNum(parameter->unknown1c);
}

void BattleCharacter::NotifyAngryEnd() {
  if (unknown130[6] == 0) {
    return;
  }
  if (!gf::GfGameManager::isPlayEvent()) {
    fw::EffectManager::get()->fadeOutDead(unknown130[6], 5);
  } else {
    fw::EffectManager::get()->remove(unknown130[6]);
  }
  unknown130[6] = 0;
}

void BattleCharacter::ResetHate() {
  if (m_player) {
    return;
  }
  CharacterParameter *characterParameter = GetCharacterParameter(false);
  if (characterParameter == nullptr) {
    return;
  }
  static_cast<EnemyParameter *>(characterParameter)->ResetHate(-1, false);
}

void BattleCharacter::AddUseWeapon() {
  CharacterParameter *parameter = GetCharacterParameter(true);
  if (parameter != nullptr) {
    int weapon = unknownf7f;
    parameter->AddUseWeapon(weapon);
  }
}

void BattleCharacter::StartBladeTimer(BLADE_TIMER_MODE mode) {
  if (unknownf77_1 > mode) {
    return;
  }

  f32 time;
  if (mode == 1) {
    time = 5.0f;
  } else if (mode == 2) {
    time = static_cast<f32>(BtlSystemBalanceAccess::get()->unknownaf);
  } else if (mode == 3) {
    time = static_cast<f32>(BtlSystemBalanceAccess::get()->unknownb0);
  } else {
    time = 0.0f;
  }
  unknowncd0 = time;
  unknownf77_1 = mode;
}

void BattleCharacter::EndBladeTimer(BLADE_TIMER_MODE mode) {
  if (unknownf77_1 == mode) {
    unknowncd0 = 0.0f;
    unknownf77_1 = 0;
  }
}

void BattleCharacter::PlayHitAttrSE(int attribute, const mm::Vec3 *position) {
  if (attribute >= 1 && attribute <= ATTRIBUTE_COUNT) {
    PlaySE(BTL_SE_HIT, attribute + SE_HIT_ATTRIBUTE, position, true);
  }
}

void BattleCharacter::PlayHitBulletSE(int attribute, const mm::Vec3 *position) {
  if (attribute >= 1 && attribute <= ATTRIBUTE_COUNT) {
    PlaySE(BTL_SE_HIT, attribute + SE_HIT_BULLET, position, true);
  }
}

int BattleCharacter::GetIKData(f32 &weight, f32 &height) const {
  int id = unknowndc0_0;
  if (id == 0) {
    weight = 0.0f;
    height = 0.0f;
    return id;
  }
  weight = unknowndb8;
  height = unknowndbc;
  return id;
}

void BattleCharacter::SetupPosDir() {
  unknownf4 = FLT_MAX;
  Misc::GetObjectTransform(unknown118, unknown10, Misc::TRANS_TYPE_POSITION);
  Misc::GetObjectDirection(unknown118, unknown50, true);
}

gf::GF_OBJ_HANDLE *BattleCharacter::GetBuddyTargetObjectHandle() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(false);
  if (parameter == nullptr) {
    return gf::INVALID_HANDLE;
  }

  gf::GF_OBJ_HANDLE *handle = parameter->unknown10;
  BattleCharacter *buddy = CharacterManager::get()->GetCharacterConst(handle);
  return buddy != nullptr ? buddy->unknown120 : gf::INVALID_HANDLE;
}

int BattleCharacter::GetTrustRank(int index) const {
  if (!m_player) {
    return 5;
  }

  const CharacterParameter *parameter = GetCharacterParameterConst(false);
  if (parameter == nullptr) {
    return 0;
  }
  int partyId = parameter->unknown1c;
  if (partyId < 0) {
    return 0;
  }

  const GROUP_DATA *group = &DataManager::get()->unknown10758[partyId];
  if (!group->unknown105_5) {
    return 0;
  }
  return group->GetBladeDataConst(index)->GetTrustRank();
}

bool BattleCharacter::IsPriorityReaction(int left, int right) const {
  if (right < 0) {
    right = unknown10c6_0;
  }
  if (right == left) {
    return static_cast<u32>(left - 1) < 2;
  }

  u8 *table = gf::GfDataBdat::getFP(0x34);
  u8 leftPriority = 0;
  if (left != 0) {
    leftPriority = Bdat::getValCheck(table, "Priority", left, 1);
  }
  u8 rightPriority = 0;
  if (right != 0) {
    rightPriority = Bdat::getValCheck(table, "Priority", right, 1);
  }
  return leftPriority >= rightPriority;
}

int BattleCharacter::GetArtsSlotIndex(int arts) const {
  const CharacterParameter *parameter = GetCharacterParameterConst(false);
  if (parameter == nullptr) {
    return -1;
  }

  const ARTS_PALETTE_DATA *palette = parameter->GetArtsPaletteDataConst(-1);
  int index = -1;
  for (int i = 0; i < 3; i++) {
    bool isNoMatch = palette->GetSlotDataConst(i, false)->unknown00_0 != arts;
    if (isNoMatch) {
      continue;
    }
    index = i;
    break;
  }
  return index;
}

bool BattleCharacter::IsBladeArtsEnd() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(false);
  if (parameter == nullptr) {
    return false;
  }
  if (!parameter->m_invalidTarget && parameter->unknown10 != gf::INVALID_HANDLE) {
    return unknown10c6_5 != 1;
  }
  return false;
}

gf::GF_OBJ_HANDLE *BattleCharacter::GetWeaponObjectHandle(bool isAlternate) const {
  gf::GfWeapon *weapon = GetWeaponInfo();
  if (weapon == nullptr) {
    return gf::INVALID_HANDLE;
  }

  const mm::mtl::FixedArray<gf::GF_OBJ_HANDLE *, 10> &handles = weapon->getCurrentHandles();
  if (isAlternate) {
    gf::GF_OBJ_HANDLE *handle = handles[1];
    if (handle == gf::INVALID_HANDLE) {
      handle = handles[0];
    }
    return handle;
  }
  gf::GF_OBJ_HANDLE *handle = handles[0];
  if (handle == gf::INVALID_HANDLE) {
    handle = handles[1];
  }
  return handle;
}

bool BattleCharacter::IsPerfectAvoid() const {
  if (unknown10e8 > 0.0f) {
    return true;
  }

  const CharacterParameter *parameter = GetCharacterParameterConst(false);
  if (parameter->m_perfectAvoid == 0) {
    return false;
  }
  return (1U << parameter->m_perfectAvoid & 0xc4U) != 0;
}

void BattleCharacter::ResetRequestPermit() {
  CharacterParameter *parameter = GetCharacterParameter(false);
  if (parameter == nullptr) {
    return;
  }
  int partyId = parameter->unknown1c;
  if (partyId < 0) {
    return;
  }

  DataManager *manager = DataManager::get();
  manager->unknown10758[partyId].unknown104_2 = 0;
  if (manager->unknown132a0 == partyId) {
    manager->unknown132a8 = true;
  }
}

gf::GfComProperty *BattleCharacter::GetComPropertyConst() const {
  gf::GfObj *obj = GetObject();
  if (obj == nullptr) {
    return nullptr;
  }
  return obj->getComponent<gf::GfComProperty>();
}

gf::GfComEffectCaster *BattleCharacter::GetEffectCaster() {
  gf::GfObj *obj = GetObject();
  if (obj == nullptr) {
    return nullptr;
  }
  return obj->getComponent<gf::GfComEffectCaster>();
}

gf::GfWeapon *BattleCharacter::GetWeaponInfo() const {
  if (!m_player) {
    return gf::GfMountManager::getGfWeapon(unknown118, gf::GFATTACH_WEAPON);
  }

  const CharacterParameter *parameter = GetCharacterParameterConst(false);
  if (parameter == nullptr) {
    return nullptr;
  }
  return gf::GfGameParty::getHandleWeapon(parameter->unknown1c, -1);
}

gf::GfComEffectCaster *BattleCharacter::GetWeaponEffectCaster() {
  gf::GfWeapon *weapon = GetWeaponInfo();
  if (weapon == nullptr) {
    return nullptr;
  }

  gf::GF_OBJ_HANDLE *handle = weapon->getCurrentHandles()[0];
  if (handle == gf::INVALID_HANDLE) {
    handle = weapon->getCurrentHandles()[1];
  }
  if (handle == gf::INVALID_HANDLE) {
    return nullptr;
  }

  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return nullptr;
  }
  return obj->getComponent<gf::GfComEffectCaster>();
}

int BattleCharacter::GetDriverType() const {
  if (m_player) {
    return 4;
  }

  const CharacterParameter *parameter = GetCharacterParameterConst(false);
  if (parameter != nullptr && parameter->m_invalidTarget && !parameter->unknown5df_6) {
    BattleCharacter *driver = CharacterManager::get()->GetCharacterConst(parameter->unknown10);
    if (driver != nullptr) {
      return driver->m_driverType;
    }
  }
  return m_driverType;
}

const GROUP_DATA *BattleCharacter::GetGroupDataConst() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(false);
  if (parameter == nullptr) {
    return nullptr;
  }
  int partyId = parameter->unknown1c;
  if (partyId < 0) {
    return nullptr;
  }

  const GROUP_DATA *group = &DataManager::get()->unknown10758[partyId];
  return group->unknown105_5 ? group : nullptr;
}

bool BattleCharacter::IsAnimationEnd() const {
  gf::GfComAsm *comAsm = GetObject()->getComponent<gf::GfComAsm>();
  if (comAsm == nullptr) {
    return true;
  }
  return comAsm->isEnd(gf::ANIM_LAYER_BASE);
}

const void *BattleCharacter::GetAnimationAppendix(const char *name) const {
  gf::GfComAsm *comAsm = GetObject()->getComponent<gf::GfComAsm>();
  if (comAsm == nullptr) {
    return nullptr;
  }
  return comAsm->getAppendix(name);
}

const char *BattleCharacter::GetNowAnimationStateName() const {
  gf::GfObj *obj = GetObject();
  if (obj == nullptr) {
    return "";
  }
  gf::GfComAsm *comAsm = obj->getComponent<gf::GfComAsm>();
  if (comAsm == nullptr) {
    return "";
  }
  return comAsm->getStateName(gf::ANIM_LAYER_BASE);
}

bool BattleCharacter::IsAnimationState(const char *name) const {
  gf::GfObj *obj = GetObject();
  const char *state = "";
  if (obj != nullptr) {
    gf::GfComAsm *comAsm = obj->getComponent<gf::GfComAsm>();
    if (comAsm != nullptr) {
      state = comAsm->getStateName(gf::ANIM_LAYER_BASE);
    }
  }
  return __builtin_strcmp(state + 2, name + 2) == 0;
}

f32 BattleCharacter::GetAnimationTime() const {
  gf::GfComAsm *comAsm = GetObject()->getComponent<gf::GfComAsm>();
  if (comAsm == nullptr) {
    return 0.0f;
  }
  return comAsm->getLocalTime(gf::ANIM_LAYER_BASE);
}

f32 BattleCharacter::GetAnimationFrame() const {
  gf::GfComAsm *comAsm = GetObject()->getComponent<gf::GfComAsm>();
  if (comAsm == nullptr) {
    return 0.0f;
  }
  return comAsm->getLocalTime(gf::ANIM_LAYER_BASE) * FRAME_RATE;
}

f32 BattleCharacter::GetAnimationLengthFrame() const {
  gf::GfComAsm *comAsm = GetObject()->getComponent<gf::GfComAsm>();
  if (comAsm == nullptr) {
    return 0.0f;
  }
  const char *state = comAsm->getStateName(gf::ANIM_LAYER_BASE);
  if (state == nullptr) {
    return 0.0f;
  }
  f32 time;
  if (!comAsm->getPlaybackTime(state, &time)) {
    return 0.0f;
  }
  f32 frame = time * FRAME_RATE;
  int base = static_cast<int>(frame);
  return static_cast<f32>(base + (frame - static_cast<f32>(base) >= 0.9f));
}

f32 BattleCharacter::GetAnimationLengthSec() const { return GetAnimationLengthFrame() * (1.0f / FRAME_RATE); }

int BattleCharacter::GetGroupIndex() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr ? parameter->unknown1c : -1;
}

bool BattleCharacter::IsEnableBackHome() const { return unknown107c == ACTION_ID_IDLE; }

bool BattleCharacter::IsDisp() const { return unknownf2c[0] > 0.0f; }

int BattleCharacter::GetWeaponType(bool isAsm) const {
  if (isAsm) {
    return gf::GfDataWeapon::getAsmWeaponType(unknownf7f);
  }

  return unknownf7f;
}

const BattleCharacter::CUSTOM_VOICE_DATA *BattleCharacter::GetCustomVoiceData(int voice, int *index) const {
  for (int i = 0; i < 3; i++) {
    if (unknownf64[i].unknown00 == voice) {
      if (index != nullptr) {
        *index = i;
      }
      return &unknownf64[i];
    }
  }
  return nullptr;
}

bool BattleCharacter::IsCustomVoice(int voice) const {
  u32 flag = 1 << voice;
  if ((unknownf5c & flag) == 0) {
    return false;
  }

  return (unknownf60 & flag) == 0;
}

void BattleCharacter::SetCustomVoiceEndFlag(int voice, bool isEnd) {
  if (isEnd) {
    unknownf60 |= 1 << voice;
  } else {
    unknownf60 &= ~(1 << voice);
  }
}

bool BattleCharacter::PlayCustomVoice(int voice) {
  if (!IsCustomVoice(voice)) {
    return false;
  }

  int index;
  if (GetCustomVoiceData(voice, &index) == nullptr) {
    return false;
  }
  if (!TalkManager::get()->NotifyTrigger(unknownf7d, static_cast<TalkManager::TRIGGER>(0x2b + index), 0, 0)) {
    return false;
  }
  SetCustomVoiceEndFlag(voice, true);
  return true;
}

void BattleCharacter::ClearCustomVoiceEndFlag(u32 flags) { unknownf60 &= ~flags; }

int BattleCharacter::GetWeaponSeType() const { return Utility::GetWeaponSeType(unknownf7f); }

bool BattleCharacter::IsEnableTurnAI() const { return ((1 << unknown107c) & ((1 << ACTION_ID_IDLE) | (1 << ACTION_ID_MOVE))) != 0; }

void BattleCharacter::GetMoveDataPerSec(mm::Vec3 &moveData) const {
  moveData.x = this->unknownb0.x * FRAME_RATE;
  moveData.y = this->unknownb0.y * FRAME_RATE;
  moveData.z = this->unknownb0.z * FRAME_RATE;
}

void BattleCharacter::SetAnimationSpeed(f32 speed) { m_animationSpeed = speed; }

void BattleCharacter::SetIKData(const ARTS_DATA &data) {
  unknowndc0_7 = data.unknown15_0;
  unknowndc1_3 = data.unknown15_4;
  unknowndc2_3 = data.unknown16_4;
  unknowndc2_7 = data.unknown17_0;
  unknowndc3_7 = data.unknown2f_0;
}

void BattleCharacter::NotifyStrikeDamage(int) { TalkManager::get()->NotifyTrigger(unknownf7d, TalkManager::TRIGGER_STRIKE_DAMAGE, 0, 0); }

void BattleCharacter::HealDirect(u32 value, int type, BattleCharacter *healer) {
  DIRECT_DAMAGE_DATA data;
  data.unknown08 = type;
  data.unknown0c = value;
  data.unknown11 = 0;
  data.unknown12 = 0;
  data.unknown00 = healer;
  data.unknown10 = 1;
  NotifyDirectDamage(data);
}

void BattleCharacter::LandingCallback() {}

void BattleCharacter::BoundCallback() {}

void BattleCharacter::ResetAlphaRate(int alpha) {
  int first = 0;
  int last = ALPHA_RATE_NUM - 1;
  if (alpha >= 0) {
    first = alpha;
    last = alpha;
  }

  for (int i = first; i <= last; i++) {
    unknownf2c[i] = -1.0f;
  }
}

f32 BattleCharacter::GetSyncCount(bool isSlow) const { return GetDt(isSlow, true) * FRAME_RATE; }

f32 BattleCharacter::GetDt(bool isSlow, bool isStopCheck) const {
  if (isStopCheck && unknownf93_6) {
    return 0.0f;
  }
  return isSlow ? unknowncc0 * unknownf58 : unknowncc0;
}

void BattleCharacter::RegisterSlow(SLOW_PROC_ID slow, f32 rate, f32 time) {
  unknownf4c[slow].unknown00 = rate;
  unknownf4c[slow].unknown04 = time;
  unknownf4c[slow].unknown08 = 0.0f;
}

void BattleCharacter::DeleteSlow(SLOW_PROC_ID slow) {
  unknownf4c[slow].unknown00 = 1.0f;
  unknownf4c[slow].unknown04 = 0.0f;
  unknownf4c[slow].unknown08 = 0.0f;
}

int BattleCharacter::GetAlphaSetID(ALPHA_PROC_ID alpha) {
  int id = alpha;
  if (id > ALPHA_PROC_LAST) {
    return ALPHA_PROC_WEAPON;
  }
  if (id >= 0 && id < ALPHA_PROC_WEAPON) {
    return id;
  }
  if (id >= ALPHA_PROC_WEAPON && id <= ALPHA_PROC_LAST) {
    return id - ALPHA_PROC_WEAPON;
  }
  return -1;
}

void BattleCharacter::AddRecast(f32 recast, bool isRate, int slot) { AddSlotRecast(slot < 0 ? SLOT_ALL : -1 - slot, recast, isRate); }

void BattleCharacter::RegisterDelayVoice(DELAY_VOICE_TYPE type, f32 time, int voice, int group, int priority) {
  if (type == DELAY_VOICE_TYPE_NORMAL) {
    unknowndd0 = time * (1.0f / FRAME_RATE) * DELAY_VOICE_TIME_SCALE;
    unknowndd2 = priority;
    unknowndd4 = group;
    unknowndd6 = voice;
  }
}

bool BattleCharacter::IsAngry() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && parameter->IsAngry();
}

void BattleCharacter::UpdateBuffEffect(int buff) {
  if (buff == BUFF_EFFECT_TARGET_LOCK) {
    UpdateTargetLockArrow();
  } else {
    UpdateEffectPositionScale(buff, nullptr, -1.0f);
  }
}

void BattleCharacter::ResetChangeActionStopSeData() { unknown10c4_0 = 0; }

void BattleCharacter::ReturnBladeChange() {
  SetAction(ACTION_ID_BLADE_CHANGE, false, false, 0, 0.0f);
  unknown107e = ACTION_PHASE_BLADE_CHANGE_RETURN;
}

void BattleCharacter::ReturnBladeArts() {
  SetAction(ACTION_ID_BLADE_ARTS, false, false, 0, 0.0f);
  BladeArtsManager *manager = BladeArtsManager::get();
  if (manager->IsRegister(unknown118)) {
    if (manager->IsBladeStart(unknown118)) {
      unknown107e = 6;
    } else {
      unknown107e = 11;
    }
  } else {
    unknown107e = 7;
  }
}

void BattleCharacter::NotifyChangeAttr(gf::GF_OBJ_HANDLE *handle, u32 attribute, u32 oldAttribute) {
  if (unknown120 == handle || unknown128 == handle) {
    BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
    if (character != nullptr && !character->IsDead(0)) {
      TalkManager::get()->NotifyTrigger(unknownf7d, static_cast<TalkManager::TRIGGER>(0x18), attribute, 0);
    }
  }
}

bool BattleCharacter::SetAngry(bool isAngry, f32 time) {
  CharacterParameter *parameter = GetCharacterParameter(false);
  if (parameter == nullptr) {
    return false;
  }

  return parameter->SetAngry(isAngry, time);
}

ActionCommand *BattleCharacter::GetActionCommand(ACTION_ID action, bool isSet) {
  int num = unknown1078;
  if (num <= 0) {
    return nullptr;
  }

  if (isSet) {
    for (long i = 0; i < num; i++) {
      ActionCommand *command = &unknownfb0[i];
      if (static_cast<s32>(command->unknown10) >= 0 && command->IsProcAction(static_cast<u8>(action))) {
        command->unknown10 |= 0x80000000;
        return command;
      }
    }
  } else {
    for (long i = 0; i < num; i++) {
      ActionCommand *command = &unknownfb0[i];
      if (static_cast<s32>(command->unknown10) >= 0 && command->IsProcAction(static_cast<u8>(action))) {
        return command;
      }
    }
  }

  return nullptr;
}

ActionCommand *BattleCharacter::GetFreeCommand() {
  if (unknown1078 >= COMMAND_NUM) {
    return nullptr;
  }
  ActionCommand *command = &unknownfb0[unknown1078];
  unknown1078++;
  command->Reset();
  return command;
}

bool BattleCharacter::IsRegisterCommand(ActionCommand::COMMAND_TYPE type) const {
  for (int i = 0; i < unknown1078; i++) {
    if (unknownfb0[i].unknown10_0 == type) {
      return true;
    }
  }
  return false;
}

void BattleCharacter::ActionCommandBladeArts(const ActionCommand *command, ActionCommand::COMMAND_TYPE type) {
  if ((type == ActionCommand::COMMAND_TYPE_MOVE_DIR_RATE || type == ActionCommand::COMMAND_TYPE_MOVE_LOCK) && unknown107e == ACTION_PHASE_BLADE_ARTS_MOVE) {
    ActionCommandRun(command, type);
  }
}

bool BattleCharacter::IsRescue() const {
  if (unknown107c == ACTION_ID_RESCUE) {
    return true;
  }
  if (unknown107c == ACTION_ID_MOVE && unknown1178 == AI_STATE_ACTIVE && unknown1160.unknown00 == ACTION_ID_RESCUE) {
    return true;
  }
  return false;
}

bool BattleCharacter::MoveStop(bool isForce) {
  if (unknown1178 != AI_STATE_ACTIVE || unknown1160.unknown00 != ACTION_ID_IDLE || (unknown1180 & AI_FLAG_SCOUT) != 0) {
    return false;
  }
  unknown1180 |= isForce ? AI_FLAG_STOP_FORCE : AI_FLAG_STOP;
  return true;
}

void BattleCharacter::SetScout(bool isScout) {
  if (unknown1178 == AI_STATE_ACTIVE) {
    if (isScout) {
      unknown1180 |= AI_FLAG_SCOUT;
      unknown1174 += AI_SCOUT_TIME;
    } else {
      unknown1180 &= ~AI_FLAG_SCOUT;
    }
  }
}

bool BattleCharacter::IsScout() const { return unknown1178 == AI_STATE_ACTIVE && (unknown1180 & AI_FLAG_SCOUT) != 0; }

gf::GF_OBJ_HANDLE *BattleCharacter::GetRescueTarget() const {
  int target;
  if (unknown107c == ACTION_ID_RESCUE) {
    target = unknown108c;
  } else if (unknown107c == ACTION_ID_MOVE && unknown1178 == AI_STATE_ACTIVE) {
    AI_ACTION_DATA action = GetAIActionData();
    if (action.unknown00 != ACTION_ID_RESCUE) {
      return gf::INVALID_HANDLE;
    }
    target = action.unknown04;
  } else {
    return gf::INVALID_HANDLE;
  }

  if (target < 0) {
    return gf::INVALID_HANDLE;
  }
  return gf::GfGameParty::getHandleDriver(target);
}

bool BattleCharacter::IsPause() const { return GetDt(true, true) <= PAUSE_DT; }

f32 BattleCharacter::GetSystemDt() const { return m_systemDt; }

f32 BattleCharacter::GetSystemSyncCount() const { return m_systemDt * FRAME_RATE; }

bool BattleCharacter::IsEnableBladeChangeAction(ACTION_ID actionId) const { return ((1 << static_cast<u8>(actionId)) & BLADE_CHANGE_ACTIONS) != 0; }

void BattleCharacter::EnhanceProc() { EnhanceTimerProc(); }

bool BattleCharacter::IsEnableBattleFace() const { return m_player; }

void BattleCharacter::NotifyHateElse() { SetBladeSupportCondition(BLADE_SUPPORT_CONDITION_HATE_ELSE); }

void BattleCharacter::ActionCommandEndIdle() {}

void BattleCharacter::ActionCommandPutOutWeapon(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndPutOutWeapon() {}

void BattleCharacter::ActionCommandPutAwayWeapon(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndPutAwayWeapon() {}

void BattleCharacter::ActionCommandKizunaMax(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndKizunaMax() {}

void BattleCharacter::ActionCommandEndAttack() {}

void BattleCharacter::ActionCommandEndArts() {}

void BattleCharacter::ActionCommandBladeChange(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndBladeChange() {}

void BattleCharacter::ActionCommandSpAttack(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndSpAttack() {}

void BattleCharacter::ActionCommandSupport(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndSupport() {}

void BattleCharacter::ActionCommandBladeGuard(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndBladeGuard() {}

void BattleCharacter::ActionCommandRepelled(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndRepelled() {}

void BattleCharacter::ActionCommandDown(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndDown() {}

void BattleCharacter::ActionCommandKnockBack(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndKnockBack() {}

void BattleCharacter::ActionCommandBreak(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndBreak() {}

void BattleCharacter::ActionCommandDead(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndDead() {}

void BattleCharacter::ActionCommandRescue(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndRescue() {}

void BattleCharacter::AddIdea(u32 idea, u32 point) { gf::SCOM_ADD_IDEA::create(unknown118, idea, point); }

void BattleCharacter::SetNoDamageTime(f32 time) { unknown10e0 = unknown10e0 > time ? unknown10e0 : time; }

void BattleCharacter::SetSuperArmorTime(f32 time) { unknown10e4 = unknown10e4 > time ? unknown10e4 : time; }

void BattleCharacter::SetPerfectAvoidTime(f32 time) { unknown10e8 = unknown10e8 > time ? unknown10e8 : time; }

f32 BattleCharacter::GetArtsDamageRate(const ARTS_DATA::LEVEL_DATA &level) const { return level.unknown00 * 0.01f; }

f32 BattleCharacter::ApplyResistantAttr(f32 damage, int attribute) const {
  if (GetCharacterParameterConst(false)->unknown59e & (1 << attribute)) {
    damage = BtlSystemBalanceAccess::get()->unknown10 * damage;
  }
  return damage;
}

f32 BattleCharacter::GetArtsDamageRate(const ARTS_DATA &data, int level) const { return GetArtsDamageRate(data.unknown90[level - 1]); }

void BattleCharacter::StopAI(f32 time) { unknown11cc = unknown11cc > time ? unknown11cc : time; }

bool BattleCharacter::CheckRandFriendEnhanceRate(int enhance) const {
  f32 rate = GetFriendEnhanceRate(enhance, false);
  if (rate <= 0.0f) {
    return false;
  }

  return ml::mtRandf1() <= rate;
}

void BattleCharacter::ResetBladeSupportConditionFlag() { unknown11e0 = 0; }

void BattleCharacter::FluctuatePartyGauge(int value) {
  if (!m_player) {
    return;
  }

  int partyId = GetGroupIndex();
  DataManager::get()->FluctuatePartyGauge(value, partyId);
}

void BattleCharacter::AddPartyGauge(f32 value) {
  if (!m_player) {
    return;
  }

  int partyId = GetGroupIndex();
  DataManager::get()->AddPartyGauge(value, partyId, true);
}

void BattleCharacter::NotifyFriendDead(int) { PlayCustomVoice(1); }

void BattleCharacter::NotifyDropHealpot() { PlayCustomVoice(3); }

void BattleCharacter::NotifyEnemyAngry(gf::GF_OBJ_HANDLE *) { PlayCustomVoice(7); }

void BattleCharacter::NotifyBackAttack(int) { PlayCustomVoice(10); }

void BattleCharacter::NotifyKillSpAttack() { PlayCustomVoice(9); }

void BattleCharacter::NotifyLostHateTarget(int) {
  if (!IsCustomVoice(5)) {
    return;
  }

  const CharacterParameter *parameter = GetCharacterParameterConst(false);
  if (parameter == nullptr) {
    return;
  }
  if (parameter->m_invalidTarget && gf::GfDataBlade::getRole(unknowncc8) == 1) {
    PlayCustomVoice(5);
  }
}

void BattleCharacter::AddKizuna(f32 kizuna) {
  if (kizuna == 0.0f) {
    return;
  }

  int partyId = GetGroupIndex();
  if (DataManager::get()->unknown001(partyId)) {
    DataManager::get()->unknown10758[partyId].unknown001(-1)->AddGauge(kizuna, true);
  }
}

void BattleCharacter::SetKizunaStage(int stage) {
  int partyId = GetGroupIndex();
  if (DataManager::get()->unknown001(partyId)) {
    DataManager::get()->unknown10758[partyId].unknown001(-1)->SetKizunaStage(stage, 0.5f, false);
  }
}

void BattleCharacter::AddKizunaStage(int value) { SetKizunaStage(mm::clamp(GetKizunaStage(nullptr) + value, 0, 6)); }

void BattleCharacter::ScoutProc() {
  if (m_player) {
    return;
  }

  gf::DataParamAcc acc(unknown118);
  int id = acc.getBdatIdEnParam();
  u8 radius = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_CHR_EN_PARAM), "ScoutJoinRad", id, 1);
  JoinProc(static_cast<f32>(radius), true);
}

f32 BattleCharacter::GetLaunchEffectScale() const {
  f32 scale = static_cast<f32>(unknownf72) * 0.01f;
  const CharacterParameter *parameter = GetCharacterParameterConst(false);
  if (parameter != nullptr) {
    scale *= parameter->unknown28;
  }
  return scale;
}

void BattleCharacter::NotifyAngryStart() {
  PlaySE(BTL_SE_HIT, 0x3c, nullptr, true);
  TalkManager::get()->NotifyTrigger(unknownf7d, static_cast<TalkManager::TRIGGER>(0x33), 0, 0);
  unknown130[6] = fw::EffectManager::get()->create("cmn_000_025", nullptr, true);
  UpdateEffectPositionScale(6, nullptr, GetLaunchEffectScale());
}

void BattleCharacter::SetActionCallback(ACTION_ID) {}

void BattleCharacter::StartFullBurst(int count) {
  const CharacterParameter *parameter = GetCharacterParameterConst(false);

  if (!parameter->unknown5df_6) {
    BattleCharacter *buddy = CharacterManager::get()->GetCharacterConst(parameter->unknown10);
    if (buddy == nullptr || !buddy->m_battle) {
      return;
    }
  }

  unknown10ac = 0;
  unknown10ae = count;
  unknown10b0 = static_cast<f32>(count << 3);
}

void BattleCharacter::ResetActionCommand() {
  int count = unknown1078;
  for (int i = 0; i < count; i++) {
    // The game resets a stack copy of each command (0x2ec4c..0x2ec68), not the stored one.
    ActionCommand command = unknownfb0[i];
    command.Reset();
  }
  unknown1078 = 0;
}

void BattleCharacter::ActionCommandEndRun() {
  if (!unknownf8e_4 && unknown1080 == 0) {
    SetAction(ACTION_ID_IDLE, false, false, 0, 0.0f);
  }
}

void BattleCharacter::UpdateCulling() {
  bool isDisable = unknownf83 != 0;
  gf::GfObjAcc acc(unknown118);
  acc.setCameraFadeDisableForBattle(isDisable);
}

void BattleCharacter::UpdateLaunchEffect() { UpdateEffectPositionScale(5, nullptr, GetLaunchEffectScale()); }

void BattleCharacter::UpdateBuffEffect() {
  UpdateEffectPositionScale(7, nullptr, -1.0f);
  UpdateTargetLockArrow();
  UpdateEffectPositionScale(9, nullptr, -1.0f);
  UpdateEffectPositionScale(10, nullptr, -1.0f);
  UpdateEffectPositionScale(11, nullptr, -1.0f);
  UpdateEffectPositionScale(12, nullptr, -1.0f);
}

void BattleCharacter::SlowProc() {
  f32 time = unknownf93_6 ? 0.0f : unknowncc0;
  SLOW_PROC_DATA &slow = unknownf4c[0];
  f32 rate = 1.0f;
  if (slow.unknown04 != 0.0f) {
    if (slow.unknown04 > 0.0f) {
      if (time + slow.unknown08 >= slow.unknown04) {
        slow.unknown00 = 1.0f;
        slow.unknown04 = 0.0f;
        slow.unknown08 = 0.0f;
        rate = 1.0f;
      } else {
        slow.unknown08 = time + slow.unknown08;
        rate = mm::min(1.0f, slow.unknown00);
      }
    } else {
      rate = mm::min(1.0f, slow.unknown00);
    }
  }

  unknownf58 = rate;
}

void BattleCharacter::DispElementalEffectUI(int effect) {
  u32 flags = unknown10f4;
  u32 bit = 1u << effect;
  if ((flags & bit) != 0) {
    return;
  }
  unknown10f4 = flags | bit;
  UIManager::get()->DispElementalEffectUI(unknown118, effect);
}

f32 BattleCharacter::GetChainSec() {
  f32 sec = static_cast<f32>(BtlSystemBalanceAccess::get()->unknown68) * (1.0f / 30.0f);
  f32 rate = SatisfyEnhanceCondition(0x147, 0, 0.0f, nullptr, true);
  return rate > 0.0f ? sec + rate * sec : sec;
}

} // namespace btl
