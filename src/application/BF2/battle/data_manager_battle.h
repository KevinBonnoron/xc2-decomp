#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace btl {

class DataManager : public mm::mtl::PtrSingleton<DataManager> {
public:
  int GetPartyGauge() const;
  void SetPartyGauge(int partyGauge, bool isNotify);
  bool IsSpecialEffects(int effect) const;

  u8 _08[0x132a3 - 0x08];
  u8 elementalEffectId;
};

static_assert(offsetof(DataManager, elementalEffectId) == 0x132a3, "");

} // namespace btl
