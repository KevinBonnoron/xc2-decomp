#pragma once
#include <stddef.h>

#include "gf/field/gf_mob_slot_manager.h"
#include "types.h"

namespace event {
class EnvManager;
} // namespace event

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gmk {
f32 getMobPopDistSq();
void resetMobPopDistSq();
bool addFailedPopDistSq(f32 distSq);
bool isMapJumpingWithSaveData();
} // namespace gmk

namespace gf {

struct GfSetupParam;

class GfFieldGimmick {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static int getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(int map);
  static int getBdatIdOfActiveGmkAntiBladeArea();

private:
  friend class event::EnvManager;
  friend f32 gmk::getMobPopDistSq();
  friend void gmk::resetMobPopDistSq();
  friend bool gmk::addFailedPopDistSq(f32 distSq);
  friend bool gmk::isMapJumpingWithSaveData();

  u8 _00[0xf4ac];
  bool unknownf4ac; // Role and original member name unknown.
  bool unknownf4ad; // Role and original member name unknown.
  bool unknownf4ae; // Role and original member name unknown.
  u8 _f4af[0xf4b0 - 0xf4af];
  u32 unknownf4b0; // Role and original member name unknown.
  u8 _f4b4[0xf910 - 0xf4b4];
  GfMobSlotManager unknownf910; // Inferred role: mob slot manager; original member name unknown.
  bool unknownfe40;             // Inferred role: map jumping with save data; original member name unknown.
  u8 _fe41[0xfe50 - 0xfe41];

  friend struct GfFieldGimmickLayout;
};

struct GfFieldGimmickLayout {
  static_assert(offsetof(GfFieldGimmick, unknownf4ac) == 0xf4ac, "");
  static_assert(offsetof(GfFieldGimmick, unknownf910) == 0xf910, "");
  static_assert(offsetof(GfFieldGimmick, unknownfe40) == 0xfe40, "");
  static_assert(sizeof(GfFieldGimmick) == 0xfe50, "");
};

} // namespace gf
