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
  f32 value = static_cast<u16>(Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_BTL_BL_KIZUNA_BASE), "KizunaDef", personality, 2));
  if (driver < POUCH_COUNT) {
    value += DataManager::get()->GetPouchBuffParam(DataManager::POUCH_BUFF_TYPE_KIZUNA, driver);
  }
  SetGauge(value, false);
}

void KIZUNA_GAUGE_DATA::SetGauge(f32 value, bool) {
  if (isLock && gauge < value) {
    return;
  }

  f32 maximum = kizunaMax;
  value = value < maximum ? value : maximum;
  if (value <= 0.0f) {
    if (gauge > 0.0f) {
      isReachZero = true;
    }
    gauge = 0.0f;
    subGauge = 0.0f;
    gaugeRate = 0.0f;
  } else if (value >= KIZUNA_GAUGE_MAX) {
    if (!isPermitMax) {
      gauge = KIZUNA_GAUGE_MAX - 1.0f;
      subGauge = -1.0f;
      gaugeRate = 0.999f;
    } else {
      if (gauge < KIZUNA_GAUGE_MAX) {
        isReachMax = true;
      }
      gauge = KIZUNA_GAUGE_MAX;
      subGauge = KIZUNA_GAUGE_MAX;
      gaugeRate = 1.0f;
    }
    stage = KIZUNA_STAGE_INVALID;
    return;
  } else {
    gauge = value;
    subGauge = -1.0f;
    gaugeRate = value * 0.001f;
  }
  isPermitMax = false;
  stage = KIZUNA_STAGE_INVALID;
}

void KIZUNA_GAUGE_DATA::SetKizunaMax(int kizunaMax) {
  int clamped = kizunaMax < 0 ? 0 : (kizunaMax > KIZUNA_GAUGE_MAX ? static_cast<int>(KIZUNA_GAUGE_MAX) : kizunaMax);
  this->kizunaMax = clamped;
  if (gauge > clamped) {
    SetGauge(gauge, false);
  }
}

int KIZUNA_GAUGE_DATA::GetKizunaStage(f32 *rate) const {
  if (stage >= KIZUNA_STAGE_INVALID) {
    stage = Misc::GetKizunaStage(gauge, &stageRate);
  }
  if (rate != nullptr) {
    *rate = stageRate;
  }
  return stage;
}

void KIZUNA_GAUGE_DATA::ResetTimingFlag() {
  isReachMax = false;
  isReachZero = false;
}

void GROUP_BLADE_DATA::InitializeCoolTime(f32 rate) {
  if (isDriverBlade) {
    coolTime = Utility::GetBladeCoolTime(id);
    coolTimeCounter = coolTime * rate;
  } else {
    coolTime = 0.0f;
    coolTimeCounter = 0.0f;
  }
}

int GROUP_BLADE_DATA::GetTrustRank() const { return Utility::GetTrustRank(id); }

f32 GROUP_BLADE_DATA::GetCoolTime() const { return coolTime; }

void GROUP_BLADE_DATA::ProgressCoolTime(f32 time) {
  if (coolTimeCounter < coolTime) {
    f32 counter = coolTimeCounter + time;
    coolTimeCounter = counter < coolTime ? counter : coolTime;
  }
}

f32 GROUP_BLADE_DATA::GetCoolTimeRatio() const {
  if (coolTime <= 0.0f) {
    return 1.0f;
  }
  f32 ratio = coolTimeCounter / coolTime;
  if (ratio < 0.0f) {
    return 0.0f;
  }
  return mm::min(1.0f, ratio);
}

bool GROUP_BLADE_DATA::IsCoolTimeEnd() const { return coolTimeCounter >= coolTime; }

void GROUP_BLADE_DATA::SynchroHomnuraData(const GROUP_BLADE_DATA &blade) {
  static_cast<KIZUNA_GAUGE_DATA &>(*this) = blade;
  coolTime = blade.coolTime;
  coolTimeCounter = blade.coolTimeCounter;
}

void GROUP_DATA::SetBuddyBladeIndex(int index) {
  if (buddyBladeIndex != index) {
    buddyBladeIndex = index;
    buddyTime = 0.0f;
  }
}

const GROUP_BLADE_DATA *GROUP_DATA::GetBladeDataConst(int index) const {
  if (index < 0) {
    index = buddyBladeIndex;
  }
  return &blades[index];
}

void GROUP_DATA::SetNeedPermit(bool isNeedPermit) {
  if (!isNeedPermit) {
    permitState = 0;
  } else if (!this->isNeedPermit) {
    permitState = 0;
  }
  this->isNeedPermit = isNeedPermit;
}

void GROUP_DATA::ProgressCoolTime(f32 time) {
  for (int i = 0; i < 5; i++) {
    if (i != buddyBladeIndex && blades[i].isInitialized) {
      blades[i].ProgressCoolTime(time);
    }
  }
}

void GROUP_DATA::FinishCoolTime() {
  for (int i = 0; i < 5; i++) {
    if (blades[i].isInitialized) {
      blades[i].coolTimeCounter = blades[i].coolTime;
    }
  }
}

} // namespace btl
