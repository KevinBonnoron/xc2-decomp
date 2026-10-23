#include "battle/group_data.h"

#include "battle/data_manager_battle.h"
#include "battle/misc_battle.h"
#include "battle/utility_battle.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
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

} // namespace btl
