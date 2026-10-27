#pragma once
#include <stddef.h>
#include <utility>

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_enemy/gmk_enemy.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_route.h"
#include "gmk/gmk_route_navi.h" // IWYU pragma: keep
#include "gmk/gmk_trigger.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class GmkRoutedEnemyGobCustom;
class GmkRoutedEnemyPointGobCustom;
class AGmkBase;

class GmkRoutedEnemy : public GmkRoute {
public:
  struct Data : GmkRoute::Data {
    int unknown14; // Inferred role: pop point index; original member name unknown.
  };

  static const u32 FLAG_UNKNOWN_3 = 1 << 3;

  // Layout evidence: the vtable at 0x11a3720 holds the four virtual functions of GmkEnemyInsts::IPopXformFinder and the
  // functions at 0x71005f2984 to 0x7100623c38 read the routed enemy at offset 8.
  class PopXformFinder : public GmkEnemyInsts::IPopXformFinder {
  public:
    bool findPosRot(mm::Vec3 &position, mm::Vec3 &rotation, gf::GF_OBJ_HANDLE *handle, const GmkEnemyInsts::PopInfo::PopEnemyInfo &info) const override;
    bool isYSnap() const override;
    bool onPopGob(gf::GF_OBJ_HANDLE *handle) const override;
    void onCreateGobInsts(u32 num) const override;

    GmkRoutedEnemy *unknown08; // Inferred role: owner; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_ENEMY;

  ~GmkRoutedEnemy() override;
  GmkType getGmkType() const override;
  const IGmkList *getBindedRoutePointList() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  IGmkList *getOwnerGmkEnemyList() const;
  bool isPopPointRouteEnd(const GmkRouteNavi &navi) const;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void bindRouteNavi(gf::GF_OBJ_HANDLE *handle, GmkRouteNavi &navi);
  void unbindRouteNavi(gf::GF_OBJ_HANDLE *handle, bool isDispose);
  GmkRouteNavi *findFreeRouteNavi() const;
  GmkRouteNavi *findRouteNavi(gf::GF_OBJ_HANDLE *handle) const;
  void createRouteNavis(u32 num);

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  GmkEnemyInsts unknown50;                                                          // Inferred role: enemy instances; original member name unknown.
  mutable mm::mtl::Vector<std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi>> unknown1D8; // Inferred role: route navis with the game object they are bound to; original member name unknown.
};

static_assert(sizeof(GmkRoutedEnemy::PopXformFinder) == 0x10, "");
static_assert(offsetof(GmkRoutedEnemy::Data, unknown14) == 0x14, "");
static_assert(offsetof(GmkRoutedEnemy, unknown50) == 0x50, "");
static_assert(offsetof(GmkRoutedEnemy, unknown1D8) == 0x1d8, "");
static_assert(sizeof(GmkRoutedEnemy) == 0x200, "");

class GmkRoutedEnemyList : public TGmkList<GmkRoutedEnemy, GmkEnemy::BdatInfo, 0x4d4e4552, 8, GmkRoutedEnemyGobCustom> {
public:
  explicit GmkRoutedEnemyList(u32 updateGmkNumPerFrame);
  ~GmkRoutedEnemyList() override { dispose(); }

  void setUpdateGmkNumPerFrame(u32 num) override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  bool updateImmediate() override;
  void debugUpdateMmf() override;
  void debugDraw() const override;

protected:
  void createGmk(void *data) override;

private:
  GmkEnemyList::BdatInfo unknown228; // Inferred role: bdat info; original member name unknown.
  GmkTriggerList unknown240;         // Inferred role: trigger list; original member name unknown.
};

static_assert(sizeof(GmkRoutedEnemyList) == 0x470, "");

class GmkRoutedEnemyPoint : public GmkRoutePoint {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_ENEMY_POINT;

  ~GmkRoutedEnemyPoint() override { dispose(); }
  GmkType getGmkType() const override;
};

static_assert(sizeof(GmkRoutedEnemyPoint) == 0x50, "");

class GmkRoutedEnemyPointList : public TGmkList<GmkRoutedEnemyPoint, GmkRoutedEnemyPoint::BdatInfo, 0x50524e45, 4, GmkRoutedEnemyPointGobCustom> {
public:
  explicit GmkRoutedEnemyPointList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

protected:
  void createGmk(void *data) override;
};

} // namespace gmk
