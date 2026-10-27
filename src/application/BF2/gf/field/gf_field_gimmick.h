#pragma once
#include <stddef.h>

#include "gf/field/gf_mob_slot_manager.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_anti_blade_area.h"
#include "gmk/gmk_ctrl_vol_se.h"
#include "gmk/gmk_dmg_gimmick.h"
#include "gmk/gmk_door.h"
#include "gmk/gmk_manager.h"
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
  void finalize();
  static void destroy();
  static bool isInitialized();
  static bool isGmkSetReady();
  static void update(const fw::UpdateInfo &info);
  static void createGmkSet(int gmkSet);
  static void disposeGmkSet(int gmkSet);
  static int getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(int map);
  static int getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(int gmkSet);
  static int getBdatIdOfActiveGmkAntiBladeArea();

private:
  friend class event::EnvManager;
  friend f32 gmk::getMobPopDistSq();
  friend void gmk::resetMobPopDistSq();
  friend bool gmk::addFailedPopDistSq(f32 distSq);
  friend bool gmk::isMapJumpingWithSaveData();

  u8 _00[0x20];
  gmk::GmkManager unknown20;                // Inferred role: gimmick manager; original member name unknown.
  gmk::GmkAccManager unknownf3b0;           // Inferred role: acc manager; original member name unknown.
  gmk::GmkDoorPhantomManager unknownf3e8;   // Inferred role: door phantom manager; original member name unknown.
  gmk::GmkDmgPhantomManager unknownf418;    // Inferred role: damage phantom manager; original member name unknown.
  gmk::GmkAntiBladeAreaManager unknownf458; // Inferred role: anti blade area manager; original member name unknown.
  gmk::GmkCtrlVolSeManager unknownf480;     // Inferred role: ctrl vol se manager; original member name unknown.
  bool unknownf4a8;                         // Inferred role: initialized; original member name unknown.
  u8 _f4a9[0xf4ac - 0xf4a9];
  bool unknownf4ac; // Role and original member name unknown.
  bool unknownf4ad; // Role and original member name unknown.
  bool unknownf4ae; // Role and original member name unknown.
  u8 _f4af[0xf4b0 - 0xf4af];
  f32 unknownf4b0; // Inferred role: elapsed time of the gimmick preparation; original member name unknown.
  u8 _f4b4[0xf910 - 0xf4b4];
  GfMobSlotManager unknownf910; // Inferred role: mob slot manager; original member name unknown.
  bool unknownfe40;             // Inferred role: map jumping with save data; original member name unknown.
  bool unknownfe41;             // Inferred role: player point savable; original member name unknown.
  u8 _fe42[0xfe50 - 0xfe42];

  friend struct GfFieldGimmickLayout;
};

struct GfFieldGimmickLayout {
  static_assert(offsetof(GfFieldGimmick, unknown20) == 0x20, "");
  static_assert(offsetof(GfFieldGimmick, unknownf3b0) == 0xf3b0, "");
  static_assert(offsetof(GfFieldGimmick, unknownf3e8) == 0xf3e8, "");
  static_assert(offsetof(GfFieldGimmick, unknownf418) == 0xf418, "");
  static_assert(offsetof(GfFieldGimmick, unknownf458) == 0xf458, "");
  static_assert(offsetof(GfFieldGimmick, unknownf480) == 0xf480, "");
  static_assert(offsetof(GfFieldGimmick, unknownf4a8) == 0xf4a8, "");
  static_assert(offsetof(GfFieldGimmick, unknownf4ac) == 0xf4ac, "");
  static_assert(offsetof(GfFieldGimmick, unknownf910) == 0xf910, "");
  static_assert(offsetof(GfFieldGimmick, unknownfe40) == 0xfe40, "");
  static_assert(offsetof(GfFieldGimmick, unknownfe41) == 0xfe41, "");
  static_assert(sizeof(GfFieldGimmick) == 0xfe50, "");
};

} // namespace gf
