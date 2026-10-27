#pragma once
#include "types.h"

namespace fw {
struct Transform;
} // namespace fw

namespace gf {

// Interface of the owner of GfBehaviorEnemyField and GfFieldEnemySensor (parameter type of GfFieldEnemySensor::update).
// The methods and their order come from the secondary vtable of GfComBehaviorEnemy, which holds thunks to
// getTransform, getTransformToSearchPlayer, getBdatId_CHR_EnArrange and getGmkBattleLockInfo.
class IGfBehFieldOwner {
public:
  virtual const fw::Transform &getTransform() const = 0;
  virtual const fw::Transform &getTransformToSearchPlayer() const = 0;
  virtual u32 getBdatId_CHR_EnArrange() const = 0;
  virtual bool getGmkBattleLockInfo(int &param1, int &param2) const = 0;
};

} // namespace gf
