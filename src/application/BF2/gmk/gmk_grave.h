#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

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

    bool isValid() const { return enemyPopId != 0 && enemyId != 0; }

    u16 enemyPopId;
    u16 enemyId;
    DistHvCond popDist;
    DistHvCond depopDist;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_GRAVE;

  GmkGrave();
  ~GmkGrave() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  void dispose() override;
  void disposeGobInst(bool isFadeOut);
  void update(f32 deltaTime) override;
  void validateTargetable();
  bool canPopGobInst() const;
  void createGobInst();
  bool canDepopGobInst() const;
  void debugDraw() const override;
  bool reqPopEnemy() const;
  template <typename T> bool reqPopEnemy() const;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override {}

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(createInfo.info); }

  bool isEnemyDefeated;
  gf::GF_OBJ_HANDLE *handle;
  GmkAcc enemy;
  bool isEnemyPopped;
};

static_assert(sizeof(GmkGrave::BdatInfo) == 0x14, "");
static_assert(offsetof(GmkGrave, isEnemyDefeated) == 0x48, "");
static_assert(offsetof(GmkGrave, handle) == 0x50, "");
static_assert(offsetof(GmkGrave, enemy) == 0x58, "");
static_assert(offsetof(GmkGrave, isEnemyPopped) == 0x98, "");
static_assert(sizeof(GmkGrave) == 0xa0, "");

typedef TGmkList<GmkGrave, GmkGrave::BdatInfo, 0x56415247, 4, GmkGraveGob> GmkGraveList;

} // namespace gmk
