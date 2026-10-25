#include "battle/group_data.h"

#include "battle/battle_global.h"
#include "battle/data_manager_battle.h"
#include "battle/misc_battle.h"
#include "battle/utility_battle.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_party.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "mm_math/mm_math.h"

namespace btl {

constexpr int KIZUNA_STAGE_INVALID = 7;
constexpr int POUCH_COUNT = 3;

void KIZUNA_GAUGE_DATA::ResetGauge(int driver) {
  f32 value = static_cast<u16>(Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_BTL_BL_KIZUNA_BASE), "KizunaDef", unknown18, 2));
  if (driver < POUCH_COUNT) {
    value += DataManager::get()->GetPouchBuffParam(DataManager::POUCH_BUFF_TYPE_KIZUNA, driver);
  }
  SetGauge(value, false);
}

void KIZUNA_GAUGE_DATA::SetGauge(f32 value, bool) {
  if (unknown19_3 && unknown00 < value) {
    return;
  }

  f32 maximum = unknown14;
  value = value < maximum ? value : maximum;
  if (value <= 0.0f) {
    if (unknown00 > 0.0f) {
      unknown19_2 = true;
    }
    unknown00 = 0.0f;
    unknown04 = 0.0f;
    unknown08 = 0.0f;
  } else if (value >= KIZUNA_GAUGE_MAX) {
    if (!unknown19_0) {
      unknown00 = KIZUNA_GAUGE_MAX - 1.0f;
      unknown04 = -1.0f;
      unknown08 = 0.999f;
    } else {
      if (unknown00 < KIZUNA_GAUGE_MAX) {
        unknown19_1 = true;
      }
      unknown00 = KIZUNA_GAUGE_MAX;
      unknown04 = KIZUNA_GAUGE_MAX;
      unknown08 = 1.0f;
    }
    unknown16 = KIZUNA_STAGE_INVALID;
    return;
  } else {
    unknown00 = value;
    unknown04 = -1.0f;
    unknown08 = value * 0.001f;
  }
  unknown19_0 = false;
  unknown16 = KIZUNA_STAGE_INVALID;
}

void KIZUNA_GAUGE_DATA::SetKizunaMax(int kizunaMax) {
  int clamped = kizunaMax < 0 ? 0 : (kizunaMax > KIZUNA_GAUGE_MAX ? static_cast<int>(KIZUNA_GAUGE_MAX) : kizunaMax);
  this->unknown14 = clamped;
  if (unknown00 > clamped) {
    SetGauge(unknown00, false);
  }
}

int KIZUNA_GAUGE_DATA::GetKizunaStage(f32 *rate) const {
  if (unknown16 >= KIZUNA_STAGE_INVALID) {
    unknown16 = Misc::GetKizunaStage(unknown00, &unknown10);
  }
  if (rate != nullptr) {
    *rate = unknown10;
  }
  return unknown16;
}

void KIZUNA_GAUGE_DATA::ResetTimingFlag() {
  unknown19_1 = false;
  unknown19_2 = false;
}

void GROUP_BLADE_DATA::Initialize(int blade, int driver, int index) {
  unknown28_0 = index < 3;
  if (index > 2) {
    gf::DataParamAcc acc(5, blade, gf::GIMMICK_TYPE_NONE);
    blade = acc.getSDataEnemy()->unknown0a;
  }

  unknown24 = static_cast<u16>(blade);
  gf::DataParamAcc acc(4, blade, gf::GIMMICK_TYPE_NONE);
  int personality = acc.getPersonality();
  if (personality == 0) {
    personality = 1;
  }

  unknown18 = static_cast<u8>(Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_BTL_BL_PERSONALITY), "KizunaBase", personality, 1));
  InitializeCoolTime(0.0f);
  unknown26 = static_cast<u16>(acc.getBladeArtsEx(false));
  const BattleGlobal::MAP_DRIVER_REV_DATA *data = BattleGlobal::get()->GetMapDriverRevDataByBdatID(driver);
  SetKizunaMax(data != nullptr ? data->unknown00_0 : 1000);
  ResetGauge(index);
  unknown28_3 = true;
}

void GROUP_BLADE_DATA::InitializeCoolTime(f32 rate) {
  if (unknown28_0) {
    m_coolTime = Utility::GetBladeCoolTime(unknown24);
    unknown20 = m_coolTime * rate;
  } else {
    m_coolTime = 0.0f;
    unknown20 = 0.0f;
  }
}

int GROUP_BLADE_DATA::GetTrustRank() const { return Utility::GetTrustRank(unknown24); }

f32 GROUP_BLADE_DATA::GetCoolTime() const { return m_coolTime; }

void GROUP_BLADE_DATA::ProgressCoolTime(f32 time) {
  if (unknown20 < m_coolTime) {
    f32 counter = unknown20 + time;
    unknown20 = counter < m_coolTime ? counter : m_coolTime;
  }
}

f32 GROUP_BLADE_DATA::GetCoolTimeRatio() const {
  if (m_coolTime <= 0.0f) {
    return 1.0f;
  }
  f32 ratio = unknown20 / m_coolTime;
  if (ratio < 0.0f) {
    return 0.0f;
  }
  return mm::min(1.0f, ratio);
}

bool GROUP_BLADE_DATA::IsCoolTimeEnd() const { return unknown20 >= m_coolTime; }

void GROUP_BLADE_DATA::SynchroHomnuraData(const GROUP_BLADE_DATA &blade) {
  static_cast<KIZUNA_GAUGE_DATA &>(*this) = blade;
  m_coolTime = blade.m_coolTime;
  unknown20 = blade.unknown20;
}

void GROUP_DATA::Reset(gf::GF_OBJ_HANDLE *handle, bool isParty) {
  if (handle == gf::INVALID_HANDLE) {
    unknown104 = unknown104 & 0xdfff;
    return;
  }

  if (isParty) {
    int driver = gf::GfGameParty::getDriverBdatId(unknownfe);
    for (int i = 0; i < 5; i++) {
      int blade = gf::GfGameParty::getBladeBdatId(unknownfe, i);
      if (blade == 0) {
        unknown08[i].unknown28_3 = false;
      } else {
        unknown08[i].Initialize(blade, driver, unknownfe);
      }
    }
  } else {
    gf::GfObjAcc acc(handle);
    int driver = acc.getBdatId();
    gf::GF_OBJ_HANDLE *mount = gf::GfMountManager::getHandle(handle, gf::GFATTACH_WEAPON, gf::OPTMNT_BLADE);
    gf::GfObjAcc mountAcc(mount);
    int blade = mountAcc.getBdatId();
    if (blade != 0) {
      unknown08[0].Initialize(blade, driver, unknownfe);
    } else {
      unknown08[0].unknown28_3 = false;
    }
  }

  unknownff = -1;
  unknownf4 = 1.0f;
  unknownf8 = 1.0f;
  unknown100 = 4;
  unknown101 = -1;
  __builtin_memset(unknowne4, 0, sizeof(unknowne4));
  unknown00 = handle;
  unknownfc = 0;
  unknown102 = 0;
  unknown104 = (unknown104 & 0xc808) | 0x2040;
}

void GROUP_DATA::SetBuddyBladeIndex(int index) {
  if (unknownff != index) {
    unknownff = index;
    unknownf0 = 0.0f;
  }
}

const GROUP_BLADE_DATA *GROUP_DATA::GetBladeDataConst(int index) const {
  if (index < 0) {
    index = unknownff;
  }
  return &unknown08[index];
}

void GROUP_DATA::SetNeedPermit(bool isNeedPermit) {
  if (!isNeedPermit) {
    unknown104_2 = 0;
  } else if (!this->unknown104_1) {
    unknown104_2 = 0;
  }
  this->unknown104_1 = isNeedPermit;
}

void GROUP_DATA::ProgressCoolTime(f32 time) {
  for (int i = 0; i < 5; i++) {
    if (i != unknownff && unknown08[i].unknown28_3) {
      unknown08[i].ProgressCoolTime(time);
    }
  }
}

void GROUP_DATA::FinishCoolTime() {
  for (int i = 0; i < 5; i++) {
    if (unknown08[i].unknown28_3) {
      unknown08[i].unknown20 = unknown08[i].m_coolTime;
    }
  }
}

void GROUP_DATA::SynchroHomnuraData(int from, int to) {
  GROUP_BLADE_DATA *dst1;
  GROUP_BLADE_DATA *dst2;
  if (from == to) {
    dst1 = &unknown08[3];
    dst2 = &unknown08[4];
  } else if (from == 3) {
    dst1 = &unknown08[to];
    dst2 = &unknown08[4];
  } else if (from == 4) {
    dst1 = &unknown08[to];
    dst2 = &unknown08[3];
  } else {
    return;
  }

  dst1->SynchroHomnuraData(unknown08[from]);
  dst2->SynchroHomnuraData(unknown08[from]);
}

} // namespace btl
