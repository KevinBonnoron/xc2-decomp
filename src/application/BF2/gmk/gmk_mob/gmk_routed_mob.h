#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_mob/gmk_mob.h"
#include "gmk/gmk_route.h"
#include "types.h"

namespace gmk {

class GmkRouteGob;

class GmkRoutedMob : public GmkRoute {
public:
  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_MOB;

  ~GmkRoutedMob() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  u8 _50[0x148 - 0x50];
};

static_assert(sizeof(GmkRoutedMob) == 0x148, "");

typedef TGmkList<GmkRoutedMob, GmkMob::BdatInfo, 0x424f4d52, 6, GmkRouteGob> GmkRoutedMobList;

} // namespace gmk
