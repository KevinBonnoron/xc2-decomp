#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm
struct CBdatWrapper;

namespace gmk {

class GmkBladeGob;

class GmkBlade : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched(const mm::Vec3 &position) const;
    bool isPopCommonCondMatched() const;
    bool isDepopCondMatched(const mm::Vec3 &position) const;

    u8 unknown00;               // Inferred role: blade size check; original member name unknown.
    u16 unknown02;              // Inferred role: condition; original member name unknown.
    u16 unknown04;              // Inferred role: battle reaction; original member name unknown.
    ScenarioFlagCond unknown06; // Inferred role: scenario flag; original member name unknown.
    TimeCond unknown10;         // Inferred role: time cond; original member name unknown.
    DistHvCond unknown20;       // Inferred role: pop dist; original member name unknown.
    DistHvCond unknown28;       // Inferred role: depop dist; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_BLADE;

  ~GmkBlade() override;
  GmkType getGmkType() const override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x58 - 0x48];
};

static_assert(sizeof(GmkBlade::BdatInfo) == 0x30, "");
static_assert(sizeof(GmkBlade) == 0x58, "");

typedef TGmkList<GmkBlade, GmkBlade::BdatInfo, 0x44414c42, 4, GmkBladeGob> GmkBladeList;

} // namespace gmk
