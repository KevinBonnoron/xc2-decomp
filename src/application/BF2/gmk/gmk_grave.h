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

namespace gmk {

class GmkGraveGob;

class GmkGrave : public AGmkBase {
public:
  struct BdatInfo {
    void create(u8 *bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched(const mm::Vec3 &position) const;
    bool isDepopCondMatched(const mm::Vec3 &position) const;
    void debugDraw(const AGmkBase &gmk) const;

    void dispose() {
      enemyPopId = 0;
      enemyId = 0;
    }

    u16 enemyPopId;
    u16 enemyId;
    DistHvCond popDist;
    DistHvCond depopDist;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_GRAVE;

  ~GmkGrave() override;
  GmkType getGmkType() const override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0xa0 - 0x48];
};

static_assert(sizeof(GmkGrave::BdatInfo) == 0x14, "");
static_assert(sizeof(GmkGrave) == 0xa0, "");

typedef TGmkList<GmkGrave, GmkGrave::BdatInfo, 0x56415247, 4, GmkGraveGob> GmkGraveList;

} // namespace gmk
