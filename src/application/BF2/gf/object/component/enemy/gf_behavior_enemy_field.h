#pragma once
#include <stddef.h>

#include "gf/field/gf_field_enemy_sensor.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/field/gf_field_move_speed.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gmk {
class GmkRouteNavi;
} // namespace gmk

namespace gf {

struct GF_OBJ_HANDLE;
class IGfBehFieldOwner;

// Field behavior of GfComBehaviorEnemy. Its layout follows the inlined constructor in GfComBehaviorEnemy::GfComBehaviorEnemy
// (0x7100514074) and GfBehaviorEnemyField::GfBehaviorEnemyField (0x7100511c74); the offsets below are relative to the object.
// Sub objects not reconstructed yet (GmkSquadNavi, the array of GfFieldLocalSteer, GfFieldPitchRollController) are padding.
class GfBehaviorEnemyField {
public:
  enum MoveSpeed {
    MOVE_SPEED_UNKNOWN_0 = 0,
    MOVE_SPEED_UNKNOWN_1 = 1,
    MOVE_SPEED_UNKNOWN_2 = 2,
  };

  virtual ~GfBehaviorEnemyField();

  void update(f32 deltaTime);
  f32 getWalkSpeed() const;
  f32 getRunSpeed() const;
  gmk::GmkRouteNavi *getGmkRouteNavi() const;
  bool isArrivedToGoal() const;

  bool isChangeBattleCondMatch() const {
    if (!unknown52a8) {
      return false;
    }

    if (unknown52a4 < unknown52a0) {
      return false;
    }

    return unknownd0.isPlayerEnter() || unknownd0.unknown80;
  }

  MoveSpeed getFieldMoveSpeedType(enemy::STATE_ID stateId) const {
    if (stateId >= enemy::STATE_ID_UNKNOWN_1 && stateId <= enemy::STATE_ID_UNKNOWN_7) {
      return MOVE_SPEED_UNKNOWN_0;
    }

    if (stateId >= enemy::STATE_ID_UNKNOWN_8 && stateId <= enemy::STATE_ID_UNKNOWN_9) {
      return MOVE_SPEED_UNKNOWN_1;
    }

    if (stateId >= enemy::STATE_ID_UNKNOWN_10 && stateId <= enemy::STATE_ID_UNKNOWN_11) {
      return MOVE_SPEED_UNKNOWN_2;
    }

    if (stateId >= enemy::STATE_ID_UNKNOWN_13 && stateId <= enemy::STATE_ID_UNKNOWN_15) {
      return MOVE_SPEED_UNKNOWN_1;
    }

    return MOVE_SPEED_UNKNOWN_0;
  }

  IGfBehFieldOwner *unknown08; // Inferred role: owner; original member name unknown.
  GF_OBJ_HANDLE *unknown10;    // Inferred role: object; original member name unknown.
  f32 unknown18;               // Inferred role: radius; original member name unknown.
  f32 unknown1c;               // Inferred role: height; original member name unknown.
  u8 unknown20;                // Inferred role: move type; original member name unknown.
  u8 _21[0x28 - 0x21];
  u8 unknown28; // Inferred role: Dir_Per of BDAT_FLD_ENACT_MOVE; original member name unknown.
  u8 _29[0x2c - 0x29];
  f32 unknown2c;  // Inferred role: Dir_Line of BDAT_FLD_ENACT_MOVE in radians; original member name unknown.
  f32 unknown30;  // Inferred role: Dir_Curve of BDAT_FLD_ENACT_MOVE in radians; original member name unknown.
  u8 unknown34;   // Inferred role: Dis_Min of BDAT_FLD_ENACT_MOVE; original member name unknown.
  u8 unknown35;   // Inferred role: Dis_Max of BDAT_FLD_ENACT_MOVE; original member name unknown.
  u8 unknown36;   // Inferred role: fldEne_Param of BDAT_FLD_ENACT_MOVE; original member name unknown.
  u8 unknown37;   // Inferred role: party_flag of the gimmick bdat; original member name unknown.
  bool unknown38; // Inferred role: noNaviMesh; original member name unknown.
  u8 _39[0x40 - 0x39];
  void *unknown40; // Inferred role: navi mesh object; original member name unknown.
  u8 _48[0x50 - 0x48];
  u8 unknown50[0x80 - 0x50]; // Inferred role: gmk::GmkSquadNavi, not reconstructed; original member name unknown.
  mm::Vec3 unknown80;        // Inferred role: offset applied at pop; original member name unknown.
  bool unknown90;            // Inferred role: gravity; original member name unknown.
  u8 _91[0xa0 - 0x91];
  mm::Vec3 unknowna0; // Inferred role: velocity; original member name unknown.
  u32 unknownb0;      // Role and original member name unknown.
  u8 _b4[0xc0 - 0xb4];
  mm::Vec3 unknownc0;               // Inferred role: position; original member name unknown.
  GfFieldEnemySensor unknownd0;     // Inferred role: sensor; original member name unknown.
  GfEnemyFieldMoveSpeed unknown1d0; // Inferred role: move speed; original member name unknown.
  GfFieldLocalSteer unknown200;     // Inferred role: local steer; original member name unknown.
  u8 _240[0x5240 - 0x240];
  void *unknown5240; // Inferred role: pointer cleared by the destructor; original member name unknown.
  u8 _5248[0x5260 - 0x5248];
  u8 unknown5260[0x5268 - 0x5260]; // Inferred role: GfFieldLocalSteer::TIsTargetNotSameSquad<GfComBehaviorEnemy>, only a vtable pointer; original member name unknown.
  u8 unknown5268[0x5298 - 0x5268]; // Inferred role: GfFieldPitchRollController, not reconstructed; original member name unknown.
  bool unknown5298;                // Inferred role: set with unknown5299 when the enemy returns to the battle state; original member name unknown.
  bool unknown5299;                // Inferred role: set with unknown5298 when the enemy returns to the battle state; original member name unknown.
  u8 _529a[0x52a0 - 0x529a];
  f32 unknown52a0;  // Inferred role: change battle delay; original member name unknown.
  f32 unknown52a4;  // Inferred role: elapsed time compared with unknown52a0; original member name unknown.
  bool unknown52a8; // Inferred role: change battle enabled, true by default; original member name unknown.
  bool unknown52a9; // Role and original member name unknown.
  u8 _52aa[0x52b0 - 0x52aa];
};

static_assert(offsetof(GfBehaviorEnemyField, unknown08) == 0x08, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown10) == 0x10, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown20) == 0x20, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown30) == 0x30, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown36) == 0x36, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown38) == 0x38, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown40) == 0x40, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown80) == 0x80, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown90) == 0x90, "");
static_assert(offsetof(GfBehaviorEnemyField, unknowna0) == 0xa0, "");
static_assert(offsetof(GfBehaviorEnemyField, unknownc0) == 0xc0, "");
static_assert(offsetof(GfBehaviorEnemyField, unknownd0) == 0xd0, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown1d0) == 0x1d0, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown200) == 0x200, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown5240) == 0x5240, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown5298) == 0x5298, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown52a0) == 0x52a0, "");
static_assert(offsetof(GfBehaviorEnemyField, unknown52a8) == 0x52a8, "");
static_assert(sizeof(GfBehaviorEnemyField) == 0x52b0, "");

} // namespace gf
