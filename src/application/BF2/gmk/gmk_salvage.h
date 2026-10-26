#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_form_pc.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_set.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class GmkSalvageGobCustom;
class GmkSalvageLocator;
class GmkSalvageLocatorGob;

class GmkSalvage : public AGmkBase {
public:
  struct Data {
    int unknown00; // Role and original member name unknown.
    int unknown04; // Role and original member name unknown.
    int unknown08; // Role and original member name unknown.
    int unknown0c; // Role and original member name unknown.
    int unknown10; // Role and original member name unknown.
    int unknown14; // Role and original member name unknown.
  };

  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isCondMatched() const;

    u16 unknown00; // Inferred role: condition; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_SALVAGE;

  ~GmkSalvage() override;
  GmkType getGmkType() const override;
  int getGameFlagId() const;
  int getGmkSalvageLocatorNum() const;
  const GmkSalvageLocator *getGmkSalvageLocator(u32 index) const;
  const GmkFormPc *getGmkFormPc() const;
  void disposeGfObjHandle();
  void disposeRaffle(bool isFadeOut);
  void seqValidateGmkSalvageLocatorDetails(f32 deltaTime);
  void disposeTboxes(bool isFadeOut);
  void disposeEnemies(bool isFadeOut);
  void validateDisp() const;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  void (GmkSalvage::*unknown48)(f32);
  gf::GF_OBJ_HANDLE *unknown58;                           // Inferred role: game object; original member name unknown.
  f32 unknown60;                                          // Role and original member name unknown.
  f32 unknown64;                                          // Role and original member name unknown.
  mm::mtl::FixedVector<GmkSalvageLocator *, 3> unknown68; // Role and original member name unknown.
  mm::mtl::FixedVector<GmkSalvageLocator *, 3> unknown88; // Inferred role: treasure box locators; original member name unknown.
  void *unknownA8;                                        // Role and original member name unknown.
  mm::mtl::FixedVector<GmkSalvageLocator *, 3> unknownB0; // Inferred role: enemy locators; original member name unknown.
  u8 _d0[0x128 - 0xd0];
  bool unknown128; // Inferred role: display enabled; original member name unknown.
  bool unknown129; // Inferred role: request to sync the depop of the treasure boxes; original member name unknown.
  u8 _12a[0x130 - 0x12a];
};

static_assert(sizeof(GmkSalvage::BdatInfo) == 0x2, "");
static_assert(offsetof(GmkSalvage, unknown48) == 0x48, "");
static_assert(offsetof(GmkSalvage, unknown58) == 0x58, "");
static_assert(offsetof(GmkSalvage, unknown60) == 0x60, "");
static_assert(offsetof(GmkSalvage, unknown64) == 0x64, "");
static_assert(offsetof(GmkSalvage, unknown68) == 0x68, "");
static_assert(offsetof(GmkSalvage, unknown88) == 0x88, "");
static_assert(offsetof(GmkSalvage, unknownA8) == 0xa8, "");
static_assert(offsetof(GmkSalvage, unknownB0) == 0xb0, "");
static_assert(offsetof(GmkSalvage, unknown128) == 0x128, "");
static_assert(offsetof(GmkSalvage, unknown129) == 0x129, "");
static_assert(sizeof(GmkSalvage) == 0x130, "");

class GmkSetOfSalvageChildren : public GmkSet {
public:
  GmkSetOfSalvageChildren() : GmkSet(nullptr) {}
  ~GmkSetOfSalvageChildren() override {}

  const IGmkList *getGmkList(GmkType type) const;
};

static_assert(sizeof(GmkSetOfSalvageChildren) == 0x3a0, "");

class GmkSalvageList : public TGmkList<GmkSalvage, GmkSalvage::BdatInfo, 0x564c4153, 2, GmkSalvageGobCustom> {
public:
  explicit GmkSalvageList(u32 updateGmkNumPerFrame);
  ~GmkSalvageList() override {}

  void debugUpdateMmf() override;
  void debugDraw() const override;
  void update(f32 deltaTime) override;

  GmkSetOfSalvageChildren unknown230; // Inferred role: set of the salvage children lists; original member name unknown.

protected:
  void createGmk(void *data) override;
  void disposeGmk() override;
};

static_assert(sizeof(GmkSalvageList) == 0x5d0, "");

class GmkSalvageLocator : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  struct Data {
    u8 unknown00; // Role and original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_SALVAGE_LOCATOR;

  ~GmkSalvageLocator() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;
  void onEnemyDead(gf::GF_OBJ_HANDLE *handle);
  void onEnemyHomeToPlayerAccess(gf::GF_OBJ_HANDLE *handle);
  void setEnemyPopInfo(int, int, s8);
  void disposeGobInst(bool isFadeOut);
  void setTargetable(bool isTargetable) const;
  void reqDisposeTboxGobInst(f32 waitTime) const;
  void initWaitPopTime(f32 waitTime);
  void syncDepopTboxes();
  void seqWaitPop(f32 deltaTime);
  void seqPop(f32 deltaTime);

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  void (GmkSalvageLocator::*unknown48)(f32); // Inferred role: sequence; original member name unknown.
  u8 _58[0xc0 - 0x58];
  gf::GF_OBJ_HANDLE *unknownC0; // Inferred role: game object; original member name unknown.
  u8 unknownC8;                 // Role and original member name unknown.
  u8 _c9[0xd0 - 0xc9];
  GmkSalvage *unknownD0; // Inferred role: owner salvage, set by GmkSalvage; original member name unknown.
  f32 unknownD8;         // Role and original member name unknown.
  f32 unknownDC;         // Role and original member name unknown.
  mutable f32 unknownE0; // Role and original member name unknown.
  mutable u32 unknownE4; // Role and original member name unknown.
  int unknownE8;         // Role and original member name unknown.
  int unknownEC;         // Role and original member name unknown.
  s8 unknownF0;          // Role and original member name unknown.
  bool unknownF1;        // Role and original member name unknown.
  bool unknownF2;        // Role and original member name unknown.
  u8 _f3[0x100 - 0xf3];
};

static_assert(offsetof(GmkSalvageLocator, unknown48) == 0x48, "");
static_assert(offsetof(GmkSalvageLocator, unknownC0) == 0xc0, "");
static_assert(offsetof(GmkSalvageLocator, unknownC8) == 0xc8, "");
static_assert(offsetof(GmkSalvageLocator, unknownD0) == 0xd0, "");
static_assert(offsetof(GmkSalvageLocator, unknownD8) == 0xd8, "");
static_assert(offsetof(GmkSalvageLocator, unknownE0) == 0xe0, "");
static_assert(offsetof(GmkSalvageLocator, unknownE8) == 0xe8, "");
static_assert(offsetof(GmkSalvageLocator, unknownF0) == 0xf0, "");
static_assert(offsetof(GmkSalvageLocator, unknownF1) == 0xf1, "");
static_assert(offsetof(GmkSalvageLocator, unknownF2) == 0xf2, "");
static_assert(sizeof(GmkSalvageLocator) == 0x100, "");

class GmkSalvageLocatorList : public TGmkList<GmkSalvageLocator, GmkSalvageLocator::BdatInfo, 0x434c4c53, 1, GmkSalvageLocatorGob> {
public:
  explicit GmkSalvageLocatorList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

  const AGmkBase *getInst(u32 index) const override;

  // Inlined access to the locator vector; the original helper name is unknown.
  const GmkSalvageLocator *unknown001(u32 index) const { return &gmkInsts[index]; }
};

} // namespace gmk
