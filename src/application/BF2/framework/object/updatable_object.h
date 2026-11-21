#pragma once
#include <stddef.h>

#include "framework/object/component_object.h"
#include "framework/pointer_map.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/rtti.h"
#include "types.h"

namespace fw {

struct UpdateInfo;

enum OBJECT_EVENT {
  OBJECT_EVENT_UNKNOWN_0 = 0, // Inferred role: update end; original name unknown.
};

struct ObjectEvent {
  u32 type;
};

class UpdatableObject : public mm::mtl::IntrusiveListNode<UpdatableObject> {
public:
  static const u32 COMPONENT_UNKNOWN_12 = 12;      // Inferred role: maximum number of components; original name unknown.
  static const u32 COMPONENT_SLOT_UNKNOWN_16 = 16; // Inferred role: maximum number of component slots; original name unknown.

  static mm::mtl::RTTI m_rtti;

  UpdatableObject(u32 type, const HandlePtr<UpdatableObject> &handle, u32 layer);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~UpdatableObject();
  virtual void initialize();
  virtual void update(const UpdateInfo &info) = 0;
  virtual void onEvent(const ObjectEvent &event);

  void removeChild(const HandlePtr<UpdatableObject> &child);
  void setTerminate();
  bool isTerminate() const;
  void addChild(UpdatableObject *child);
  void setParent(const HandlePtr<UpdatableObject> &parent);
  void addChild(const HandlePtr<UpdatableObject> &child);
  void removeChild(UpdatableObject *child);
  void registComponentLocal(u32 index, ComponentObject *component);
  void removeComponentLocal(u32 index);

  // Inferred name; shared by every component class for getComponent<T>.
  //
  // Where the game keeps the null test of this function and the build drops it (a `cbz` before the inlined cast, joining at the first read of the component: StateUtilField::setWaterMode
  // 0x71005509b8 (cbz at 0x71005509d8), StateUtil::setEnableSpineIK 0x7100572bc4 (0x7100572bdc), changePlacementDownDist 0x7100572e54 (0x7100572e70), resetPlacementDownDist 0x7100572f30
  // (0x7100572f44), TargetIKPlugin::setup 0x710057bfbc (0x710057bfd8) and DeadColCheckPlugin::testDead 0x7100577a64 (0x7100577af4, second component)).
  // Cause, clang 3.9.1 -O3 (read in lib/Transforms/Utils/SimplifyCFG.cpp of release 3.9, and seen with -print-after-all on setWaterMode): once inlined, the function is
  // `phi [null, select(isKindOf, component, null)]`. The first SimplifyCFG after the inlining runs removeUndefIntroducingPredecessor, which deletes the null edge of that phi when
  // passingValueIsAlwaysUndefined holds; the cbz goes with the edge and the cast (getRTTI call, isKindOf) then runs for a null component too. That function looks only at the FIRST user of the
  // phi (`*user_begin()`, through GEPs and bitcasts): a load or a store through it with no instruction that may have side effects (a call, a store) between the phi and that user. When the first
  // user comes after a call or a store, the edge stays. Which user is first in the use list depends on how the inliner rebuilt it, so the forms below are measured, not derived.
  // Forms that drop the test (one instruction short of the game in each function: setWaterMode 37 against 38; the three IK functions 51, 54 and 49 against 52, 55 and 50; testDead 67 against 68):
  // the component read directly after getComponent<T>() (also through a `T &` reference, a local reference to the solver vector, or a named local for the collision object), a helper taking the solver
  // vector or the collision vector, a helper taking GfComBehaviorPc &, a static helper taking the owner for the IK or the collider component, and an `inline` or external-linkage helper with the body
  // of getPropertyComponent.
  // Forms that keep it (the game's instruction counts): a function taking the component, so that the first user is a call (GfComIK::unknown003, GfComCollider::unknown001, a `const GfComIK &`
  // parameter, getWallParam in gf_pc_state_field_wall_adsorption_air.cpp) and, for setWaterMode and getWaterHeight, a function of internal linkage (static, static template or anonymous namespace)
  // taking the owner and returning the component, its slot load being promoted into the caller before it is inlined (getPropertyComponent in gf_pc_state_util_field.cpp, getEnvSensorComponent in
  // gf_com_property_enemy.cpp). A Mat44 declared before the collider read also keeps it, but GfComCollider::unknown001 keeps it without that local.
  // Matched with them: LookAtPlugin::setup, StateUtil::reflectionAdsorption, setEnableSpineRotate, setSpineRotateAngles and changeGroundAnglesForMotion, StateFieldWallAdsorptionAir::update,
  // GfComPropertyEnemy::getWaterHeight, GfComBehaviorPc::warpBattle and warpExternal. GfComBehaviorEnemy::procMsgObjectNotifyDead keeps the test the same way but still differs in registers.
  template <typename T> T *getComponent() const {
    ComponentObject *component = unknown38[T::COMPONENT_INDEX];
    if (component == nullptr) {
      return nullptr;
    }

    return mm::mtl::dynamicCast<T>(component);
  }

  HandlePtr<UpdatableObject> unknown18; // Inferred role: self handle; original member name unknown.
  u32 unknown28;                        // Inferred role: type; original member name unknown.
  u32 unknown2c;                        // Inferred role: layer; original member name unknown.
  u16 unknown30;                        // Inferred role: flags; original member name unknown.
  u8 _32[0x38 - 0x32];
  ComponentObject *unknown38[COMPONENT_SLOT_UNKNOWN_16]; // Inferred role: components; original member name unknown.
  mm::mtl::IntrusiveList<UpdatableObject> unknownb8;     // Inferred role: children; original member name unknown.
  HandlePtr<UpdatableObject> unknownd0;                  // Inferred role: parent; original member name unknown.
};

static_assert(offsetof(UpdatableObject, unknown18) == 0x18, "");
static_assert(offsetof(UpdatableObject, unknown28) == 0x28, "");
static_assert(offsetof(UpdatableObject, unknown2c) == 0x2c, "");
static_assert(offsetof(UpdatableObject, unknown30) == 0x30, "");
static_assert(offsetof(UpdatableObject, unknown38) == 0x38, "");
static_assert(offsetof(UpdatableObject, unknownb8) == 0xb8, "");
static_assert(offsetof(UpdatableObject, unknownd0) == 0xd0, "");
static_assert(sizeof(UpdatableObject) == 0xe0, "");

} // namespace fw
