#include "battle/data_manager_battle.h"

#include "battle/battle_global.h"
#include "gf/game/gf_game_party.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_party_status.h"
#include "gf/object/gf_obj_handle.h"

namespace btl {

constexpr int ENEMY_GROUP_NUM = 35;
constexpr int ENEMY_GROUP_INDEX_OFFSET = 3;
constexpr u16 GROUP_FLAGS_PERMIT = 0x2006;
constexpr int PARTY_COUNT = 3;

DataManager::~DataManager() {}

void DataManager::Destroy() {
  DataManager *manager = get();
  manager->Finalize();
  if (manager != nullptr) {
    delete manager;
  }
}

void DataManager::Finalize() {
  if (unknown13290 != nullptr) {
    unknown13290->release();
    unknown13290 = nullptr;
  }
}

void DataManager::InitializeComboRequestUI() {
  if (unknown13290 == nullptr) {
    unknown13290 = gf::GfMenuCallContext::create();
    if (unknown13290 != nullptr) {
      gf::GfMenuObjPartyStatus::attachComboRequest(unknown13290);
    }
  }
}

f32 DataManager::GetPouchBuffParam(int type, int pouch) const {
  if (pouch > 2) {
    return 0.0f;
  }

  return unknown131d0[pouch].unknown00[type];
}

int DataManager::GetPartyGauge() const { return gf::GfGameParty::getPartyGauge(); }

bool DataManager::IsPouchBuffTiming(int pouch) const {
  if (pouch > 2) {
    return false;
  }

  return unknown131d0[pouch].unknown3b;
}

int DataManager::RegisterEnemyGroup(gf::GF_OBJ_HANDLE *leader, gf::GF_OBJ_HANDLE *member) {
  if (leader == gf::INVALID_HANDLE || member == gf::INVALID_HANDLE) {
    return -1;
  }

  for (int i = 0; i < ENEMY_GROUP_NUM; i++) {
    if (unknown12e88[i].unknown00 == gf::INVALID_HANDLE) {
      unknown12e88[i].unknown00 = leader;
      unknown12e88[i].unknown08 = member;
      return i + ENEMY_GROUP_INDEX_OFFSET;
    }
  }

  return -1;
}

int DataManager::GetEnemyGroupIndex(gf::GF_OBJ_HANDLE *handle) {
  if (handle == gf::INVALID_HANDLE) {
    return -1;
  }

  int index = -1;
  for (int i = 0; i < ENEMY_GROUP_NUM; i++) {
    if (unknown12e88[i].unknown00 == handle || unknown12e88[i].unknown08 == handle) {
      index = i + ENEMY_GROUP_INDEX_OFFSET;
      break;
    }
  }

  return index;
}

void DataManager::DeleteElementalEffect() { unknown132a3 = 0; }

void DataManager::PreUpdate(const fw::UpdateInfo &updateInfo) {
  if (get() != nullptr) {
    get()->PreUpdateProc(updateInfo);
  }
}

void DataManager::PreUpdateProc(const fw::UpdateInfo &updateInfo) {
  for (int i = 0; i < PLAYER_PARAMETER_COUNT; i++) {
    if (unknown08[i].unknown08 != gf::INVALID_HANDLE) {
      unknown08[i].PreUpdate(updateInfo);
    }
  }
  for (EnemyParameter *parameter : unknown7358) {
    if (parameter != nullptr && parameter->unknown08 != gf::INVALID_HANDLE) {
      parameter->PreUpdate(updateInfo);
    }
  }
}

void DataManager::Update(const fw::UpdateInfo &updateInfo) {
  if (get() != nullptr) {
    get()->UpdateProc(updateInfo);
  }
}

void DataManager::UpdateElementalEffect(f32) {
  if (!BattleGlobal::get()->unknown65de_0) {
    unknown132a3 = 0;
  }
}

void DataManager::SetSpecialEffects(int effect, bool isEnable) { unknown132a5[effect] = isEnable; }

void DataManager::ResetRequestPermit() {
  unknown13298 = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  unknown132a0 = -1;
  unknown132a1 = 0;
  unknown132a2 = 0;
  unknown132a8 = false;
}

void DataManager::PostUpdate(const fw::UpdateInfo &updateInfo) { get()->PostUpdateProc(updateInfo); }

void DataManager::PostUpdateProc(const fw::UpdateInfo &updateInfo) {
  for (int i = 0; i < PLAYER_PARAMETER_COUNT; i++) {
    if (unknown08[i].unknown08 != gf::INVALID_HANDLE) {
      unknown08[i].PostUpdate(updateInfo);
    }
  }
  for (EnemyParameter *parameter : unknown7358) {
    if (parameter != nullptr && parameter->unknown08 != gf::INVALID_HANDLE) {
      parameter->PostUpdate(updateInfo);
    }
  }
}

bool DataManager::IsSpecialEffects(int effect) const { return unknown132a5[effect]; }

bool DataManager::IsValidDeadEnhance(int enhance) {
  switch (enhance) {
  case 0xa8:
  case 0xc1:
  case 0xc4:
  case 0xf5:
  case 0x14f:
  case 0x173:
    return true;
  default:
    return false;
  }
}

const CharacterParameter *DataManager::SearchCharacterParameterConst(gf::GF_OBJ_HANDLE *handle, bool) const {
  if (handle == gf::INVALID_HANDLE) {
    return nullptr;
  }
  for (const PlayerParameter &parameter : unknown08) {
    if (parameter.unknown08 == handle) {
      return &parameter;
    }
  }
  for (int i = 0; i < CHARACTER_COUNT - CHARACTER_PLAYER_COUNT; i++) {
    if (unknown7358[i] != nullptr && unknown7358[i]->unknown08 == handle) {
      return unknown7358[i];
    }
  }
  return nullptr;
}

bool DataManager::IsExistRequestPermit() const {
  if (unknown132a0 >= 0) {
    return true;
  }
  for (int i = 0; i < PARTY_COUNT; i++) {
    if ((unknown10758[i].unknown104 & GROUP_FLAGS_PERMIT) == GROUP_FLAGS_PERMIT) {
      return true;
    }
  }
  return false;
}

} // namespace btl
