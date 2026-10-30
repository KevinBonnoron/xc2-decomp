#pragma once
#include <stddef.h>

#include "framework/coli/coli_object.h"
#include "gmk/gmk_acc.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_quat.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
class IGfBehFieldOwner;

// Sensor of GfBehaviorEnemyField, a sub object at 0xd0 of it. The layout follows the inlined constructor in
// GfBehaviorEnemyField::GfBehaviorEnemyField (0x7100511c74), GfFieldEnemySensor::GfFieldEnemySensor (0x7100511068), the copy of
// the CreateInfo in GfFieldEnemySensor::create (0x71005110f4) and the vtable at 0x119bd90, which holds the slots enter, leave and
// contact of fw::IColiEventListener.
class GfFieldEnemySensor : public fw::IColiEventListener {
public:
  struct CreateInfo {
    CreateInfo() : unknown40(-1), unknown44(-1), unknown48(-1), unknown4c(-1) { unknown00 = mm::Mat44::identity; }

    mm::Mat44 unknown00; // Inferred role: transform; original member name unknown.
    int unknown40;       // Inferred role: row of BDAT_RSC_EN; original member name unknown.
    int unknown44;       // Inferred role: row of BDAT_CHR_EN_ARRANGE; original member name unknown.
    int unknown48;       // Inferred role: battle lock gimmick set id; original member name unknown.
    int unknown4c;       // Inferred role: battle lock gimmick index; original member name unknown.
  };

  GfFieldEnemySensor(const CreateInfo *info = nullptr);
  ~GfFieldEnemySensor() { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  void createByGmkBattleLock();
  void update(GF_OBJ_HANDLE *handle, const IGfBehFieldOwner &owner);
  bool isPlayerEnter() const;
  f32 getEyeRadiusSq() const;
  void enter(const EnterInfo &info) override;
  void leave(const LeaveInfo &info) override;

  CreateInfo unknown10;      // Inferred role: create info; original member name unknown.
  u8 unknown60;              // Inferred role: Detects of BDAT_CHR_EN_ARRANGE, bit 0 for the sight and bit 1 for the radius; original member name unknown.
  bool unknown61;            // Inferred role: UseSearchBone of BDAT_RSC_EN; original member name unknown.
  mm::Quat unknown70;        // Inferred role: rotation of the search bone; original member name unknown.
  bool unknown80;            // Inferred role: owner is a genus link enemy; original member name unknown.
  fw::ColiObject *unknown88; // Inferred role: sight collision; original member name unknown.
  f32 unknown90;             // Inferred role: sight radius squared; original member name unknown.
  f32 unknown94;             // Inferred role: cosine of the half sight angle; original member name unknown.
  bool unknown98;            // Inferred role: player in the sight radius; original member name unknown.
  bool unknown99;            // Inferred role: player in the sight angle; original member name unknown.
  fw::ColiObject *unknowna0; // Inferred role: search radius collision; original member name unknown.
  f32 unknowna8;             // Inferred role: search radius squared; original member name unknown.
  bool unknownac;            // Inferred role: player in the search radius; original member name unknown.
  gmk::GmkAcc unknownb0;     // Inferred role: battle lock; original member name unknown.
  bool unknownf0;            // Inferred role: player inside the battle lock shape; original member name unknown.
};

static_assert(sizeof(GfFieldEnemySensor::CreateInfo) == 0x50, "");
static_assert(offsetof(GfFieldEnemySensor, unknown10) == 0x10, "");
static_assert(offsetof(GfFieldEnemySensor, unknown60) == 0x60, "");
static_assert(offsetof(GfFieldEnemySensor, unknown70) == 0x70, "");
static_assert(offsetof(GfFieldEnemySensor, unknown80) == 0x80, "");
static_assert(offsetof(GfFieldEnemySensor, unknown88) == 0x88, "");
static_assert(offsetof(GfFieldEnemySensor, unknown90) == 0x90, "");
static_assert(offsetof(GfFieldEnemySensor, unknown98) == 0x98, "");
static_assert(offsetof(GfFieldEnemySensor, unknowna0) == 0xa0, "");
static_assert(offsetof(GfFieldEnemySensor, unknowna8) == 0xa8, "");
static_assert(offsetof(GfFieldEnemySensor, unknownac) == 0xac, "");
static_assert(offsetof(GfFieldEnemySensor, unknownb0) == 0xb0, "");
static_assert(offsetof(GfFieldEnemySensor, unknownf0) == 0xf0, "");
static_assert(sizeof(GfFieldEnemySensor) == 0x100, "");

} // namespace gf
