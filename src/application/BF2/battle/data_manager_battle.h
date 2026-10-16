#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

class DataManager : public mm::mtl::PtrSingleton<DataManager> {
public:
  void ReleaseEnemyGroup(gf::GF_OBJ_HANDLE *handle);
  int GetPartyGauge() const;
  void SetPartyGauge(int partyGauge, bool isNotify);
  bool IsSpecialEffects(int effect) const;

  u8 _08[0x132a3 - 0x08];
  u8 elementalEffectId;
};

static_assert(offsetof(DataManager, elementalEffectId) == 0x132a3, "");

} // namespace btl
