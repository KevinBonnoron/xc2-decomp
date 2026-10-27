#pragma once
#include <stddef.h>
#include <utility>

#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_mob/gmk_mob.h"
#include "gmk/gmk_route.h"
#include "gmk/gmk_route_navi.h" // IWYU pragma: keep
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class GmkRouteGob;

class GmkRoutedMob : public GmkRoute {
public:
  // Layout evidence: the vtable at 0x11a3d58 holds the three virtual functions of GmkMobInsts::IPopXformFinder and the
  // functions at 0x71006043ec to 0x71006047a0 read the routed mob at offset 8 and a route navi at offset 0x10.
  class PopXformFinder : public GmkMobInsts::IPopXformFinder {
  public:
    bool findPosRot(mm::Vec3 &position, mm::Vec3 &rotation) const override;
    void onPopGob(gf::GF_OBJ_HANDLE *handle) const override;
    void onCreateGobInsts(u32 num) const override;

    GmkRoutedMob *unknown08;         // Inferred role: owner; original member name unknown.
    mutable GmkRouteNavi *unknown10; // Inferred role: route navi found by findPosRot; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_MOB;

  GmkRoutedMob();
  ~GmkRoutedMob() override;
  GmkType getGmkType() const override;
  const IGmkList *getBindedRoutePointList() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  void bindRouteNavi(gf::GF_OBJ_HANDLE *handle, GmkRouteNavi &navi);
  void unbindRouteNavi(gf::GF_OBJ_HANDLE *handle);
  GmkRouteNavi *findFreeRouteNavi() const;
  GmkRouteNavi *findRouteNavi(gf::GF_OBJ_HANDLE *handle) const;
  void createRouteNavis(u32 num);

  GmkMobInsts unknown50;                                                            // Inferred role: mob instances; original member name unknown.
  mutable mm::mtl::Vector<std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi>> unknown120; // Inferred role: route navis with the game object they are bound to; original member name unknown.
};

static_assert(sizeof(GmkRoutedMob::PopXformFinder) == 0x18, "");
static_assert(offsetof(GmkRoutedMob, unknown50) == 0x50, "");
static_assert(offsetof(GmkRoutedMob, unknown120) == 0x120, "");
static_assert(sizeof(GmkRoutedMob) == 0x148, "");

typedef TGmkList<GmkRoutedMob, GmkMob::BdatInfo, 0x424f4d52, 6, GmkRouteGob> GmkRoutedMobList;

} // namespace gmk
