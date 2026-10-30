#pragma once
#include <stddef.h>

#include "gf/data/gf_data_blade.h"
#include "gf/event/gf_event.h"
#include "gf/field/gf_gmk_locator_atlas.h"
#include "gf/field/gf_mob_slot_manager.h"
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_anti_blade_area.h"
#include "gmk/gmk_ctrl_vol_se.h"
#include "gmk/gmk_dmg_gimmick.h"
#include "gmk/gmk_door.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/singleton.h"
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

// The IGfObjListener base sits at 0x08 and the IGfEvent base at 0x10: the game's non-virtual thunks adjust this by -8 and -16.
class GfFieldGimmick : public mm::mtl::PtrSingleton<GfFieldGimmick>, public IGfObjListener, public IGfEvent {
public:
  // Inferred role: state of the gimmick pop wait of event::EnvManager; original type name unknown. The GfFieldGimmick
  // destructor clears unknown00 between the destructions of unknownf4c0 and unknownf480.
  struct unknown001 {
    unknown001() : unknown00(false), unknown01(false), unknown02(false), unknown04(0.0f) {}
    ~unknown001() { unknown00 = false; }

    bool unknown00; // Inferred role: waiting; original member name unknown.
    bool unknown01; // Inferred role: immediate update done; original member name unknown.
    bool unknown02; // Inferred role: view valid; original member name unknown.
    f32 unknown04;  // Inferred role: elapsed time of the gimmick preparation; original member name unknown.
  };

  GfFieldGimmick(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  // Not decompiled yet: defining it emits the inline ~GfGmkLocatorAtlas and mm::mtl::destruct_n<GfGmkLocators>, whose
  // loop does not match the game's copy yet.
  ~GfFieldGimmick();
  void finalize();
  void listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) override;
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info) override;
  void gevBladeActivate(u32 blade, ActivateType activateType, ActivateType oldActivateType) override;
  static void build(const GfSetupParam &param);
  static void destroy();
  static bool isInitialized();
  static bool isGmkSetReady();
  static void update(const fw::UpdateInfo &info);
  static bool createGmkSet(int gmkSet);
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

  u8 _18[0x20 - 0x18];
  gmk::GmkManager unknown20;                // Inferred role: gimmick manager; original member name unknown.
  gmk::GmkAccManager unknownf3b0;           // Inferred role: acc manager; original member name unknown.
  gmk::GmkDoorPhantomManager unknownf3e8;   // Inferred role: door phantom manager; original member name unknown.
  gmk::GmkDmgPhantomManager unknownf418;    // Inferred role: damage phantom manager; original member name unknown.
  gmk::GmkAntiBladeAreaManager unknownf458; // Inferred role: anti blade area manager; original member name unknown.
  gmk::GmkCtrlVolSeManager unknownf480;     // Inferred role: ctrl vol se manager; original member name unknown.
  bool unknownf4a8;                         // Inferred role: initialized; original member name unknown.
  unknown001 unknownf4ac;                   // Inferred role: gimmick pop wait; original member name unknown.
  GfGmkLocatorAtlas unknownf4c0;            // Inferred role: gimmick locator atlas; original member name unknown.
  GfMobSlotManager unknownf910;             // Inferred role: mob slot manager; original member name unknown.
  bool unknownfe40;                         // Inferred role: map jumping with save data; original member name unknown.
  bool unknownfe41;                         // Inferred role: player point savable; original member name unknown.

  friend struct GfFieldGimmickLayout;
};

struct GfFieldGimmickLayout {
  static_assert(offsetof(GfFieldGimmick::unknown001, unknown04) == 0x04, "");
  static_assert(offsetof(GfFieldGimmick, _18) == 0x18, "");
  static_assert(offsetof(GfFieldGimmick, unknown20) == 0x20, "");
  static_assert(offsetof(GfFieldGimmick, unknownf3b0) == 0xf3b0, "");
  static_assert(offsetof(GfFieldGimmick, unknownf3e8) == 0xf3e8, "");
  static_assert(offsetof(GfFieldGimmick, unknownf418) == 0xf418, "");
  static_assert(offsetof(GfFieldGimmick, unknownf458) == 0xf458, "");
  static_assert(offsetof(GfFieldGimmick, unknownf480) == 0xf480, "");
  static_assert(offsetof(GfFieldGimmick, unknownf4a8) == 0xf4a8, "");
  static_assert(offsetof(GfFieldGimmick, unknownf4ac) == 0xf4ac, "");
  static_assert(offsetof(GfFieldGimmick, unknownf4c0) == 0xf4c0, "");
  static_assert(offsetof(GfFieldGimmick, unknownf910) == 0xf910, "");
  static_assert(offsetof(GfFieldGimmick, unknownfe40) == 0xfe40, "");
  static_assert(offsetof(GfFieldGimmick, unknownfe41) == 0xfe41, "");
  static_assert(sizeof(GfFieldGimmick) == 0xfe50, "");
};

} // namespace gf
