#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class GmkMobGob;
class GmkSquad;

class GmkMobInsts {
public:
  class IPopXformFinder;

  enum Matched {
    MATCHED_UNKNOWN_0 = 1 << 0, // Inferred role: pop condition matched; original name unknown.
    MATCHED_UNKNOWN_1 = 1 << 1, // Inferred role: pop distance condition matched; original name unknown.
    MATCHED_UNKNOWN_2 = 1 << 2, // Inferred role: depop distance condition matched; original name unknown.
  };

  struct CreateInfo {
    CreateInfo() : unknown00(nullptr), unknown08(nullptr), unknown10(-1) {}

    AGmkBase *unknown00; // Inferred role: owner gimmick; original member name unknown.
    u8 *unknown08;       // Inferred role: bdat; original member name unknown.
    int unknown10;       // Inferred role: bdat id; original member name unknown.
  };

  struct UpdateInfo {
    f32 unknown00;                    // Inferred role: delta time; original member name unknown.
    const mm::Vec3 *unknown08;        // Inferred role: position; original member name unknown.
    const IPopXformFinder *unknown10; // Inferred role: pop xform finder; original member name unknown.
  };

  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    void debugDraw(const AGmkBase &gmk) const;

    u16 unknown00;              // Inferred role: condition; original member name unknown.
    u16 unknown02;              // Inferred role: group; original member name unknown.
    u16 unknown04;              // Inferred role: squad id; original member name unknown.
    u16 unknown06;              // Inferred role: motion; original member name unknown.
    u16 unknown08;              // Inferred role: collision; original member name unknown.
    u16 unknown0a;              // Inferred role: reaction range; original member name unknown.
    u16 unknown0c;              // Inferred role: reaction percent; original member name unknown.
    u16 unknown0e;              // Inferred role: reaction motion; original member name unknown.
    u16 unknown10;              // Inferred role: battle reaction; original member name unknown.
    ScenarioFlagCond unknown12; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown16;    // Inferred role: quest flag; original member name unknown.
    TimeCond unknown20;         // Inferred role: time cond; original member name unknown.
    DistHvCond unknown30;       // Inferred role: pop dist; original member name unknown.
    DistHvCond unknown38;       // Inferred role: depop dist; original member name unknown.
  };

  struct PopInfo {
    void dispose();

    u8 unknown00;                           // Inferred role: scale min; original member name unknown.
    u8 unknown01;                           // Inferred role: scale max; original member name unknown.
    u8 unknown02;                           // Inferred role: motion speed min; original member name unknown.
    u8 unknown03;                           // Inferred role: motion speed max; original member name unknown.
    u16 unknown04;                          // Inferred role: group; original member name unknown.
    u32 unknown08;                          // Inferred role: group member num; original member name unknown.
    u16 unknown0c;                          // Inferred role: motion; original member name unknown.
    u16 unknown0e;                          // Inferred role: mount point; original member name unknown.
    u16 unknown10;                          // Inferred role: mount object; original member name unknown.
    u16 unknown12;                          // Inferred role: mount point 2; original member name unknown.
    u16 unknown14;                          // Inferred role: mount object 2; original member name unknown.
    mm::mtl::FixedVector<u32, 8> unknown18; // Inferred role: mob ids; original member name unknown.
    u32 unknown40;                          // Inferred role: pop num; original member name unknown.
    bool unknown44;                         // Inferred role: has squad; original member name unknown.
  };

  void validateDisp(gf::GF_OBJ_HANDLE *handle) const;
  bool isValid() const;
  bool isPopFinished() const;
  bool isGobInstExist() const;
  bool canPopGobInst(const mm::Vec3 &position) const;
  bool canDepopGobInst(const mm::Vec3 &position) const;
  void removeGobInst(gf::GF_OBJ_HANDLE *handle);
  void disposeSquad();

  CreateInfo unknown00;                                   // Inferred role: create info; original member name unknown.
  BdatInfo unknown18;                                     // Inferred role: bdat info; original member name unknown.
  PopInfo unknown58;                                      // Inferred role: pop info; original member name unknown.
  bool unknowna0;                                         // Inferred role: display enabled; original member name unknown.
  mm::mtl::Vector<gf::GF_OBJ_HANDLE *> *unknowna8;        // Inferred role: game object handles; original member name unknown.
  GmkSquad *unknownb0;                                    // Inferred role: squad; original member name unknown.
  u64 unknownb8;                                          // Inferred role: matched condition flags; original member name unknown.
  void (GmkMobInsts::*unknownc0)(const UpdateInfo &info); // Inferred role: seq; original member name unknown.
};

static_assert(sizeof(GmkMobInsts::BdatInfo) == 0x40, "");
static_assert(sizeof(GmkMobInsts::PopInfo) == 0x48, "");
static_assert(offsetof(GmkMobInsts, unknown18) == 0x18, "");
static_assert(offsetof(GmkMobInsts, unknown58) == 0x58, "");
static_assert(offsetof(GmkMobInsts, unknowna0) == 0xa0, "");
static_assert(offsetof(GmkMobInsts, unknowna8) == 0xa8, "");
static_assert(offsetof(GmkMobInsts, unknownb0) == 0xb0, "");
static_assert(offsetof(GmkMobInsts, unknownc0) == 0xc0, "");
static_assert(sizeof(GmkMobInsts) == 0xd0, "");

class GmkMob : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  static const GmkType GMK_TYPE = GMK_TYPE_MOB;

  ~GmkMob() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  GmkMobInsts unknown48; // Inferred role: mob instances; original member name unknown.
};

static_assert(offsetof(GmkMob, unknown48) == 0x48, "");
static_assert(sizeof(GmkMob) == 0x118, "");

class GmkMobList : public TGmkList<GmkMob, GmkMob::BdatInfo, 0x424f4d, 2, GmkMobGob> {
public:
  explicit GmkMobList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame), unknown228(0) {}

protected:
  void onResetUpdateGmkIndex() override;

private:
  u32 unknown228; // Inferred role: update round count; original member name unknown.
};

static_assert(sizeof(GmkMobList) == 0x230, "");

} // namespace gmk
