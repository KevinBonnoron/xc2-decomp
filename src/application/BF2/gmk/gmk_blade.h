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

    u8 bladeSizeCheck;
    u16 condition;
    u16 battleReaction;
    ScenarioFlagCond scenarioFlag;
    TimeCond timeCond;
    DistHvCond popDist;
    DistHvCond depopDist;
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
