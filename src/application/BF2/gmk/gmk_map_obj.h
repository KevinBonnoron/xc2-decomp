#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_route.h"
#include "types.h"

namespace gmk {

class GmkMapObjGob;
class GmkRouteGob;

class GmkMapObj : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0x14];
  };

  static const GmkType GMK_TYPE = GMK_TYPE_MAP_OBJ;

  ~GmkMapObj() override;
  GmkType getGmkType() const override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x60 - 0x48];
};

static_assert(sizeof(GmkMapObj::BdatInfo) == 0x14, "");
static_assert(sizeof(GmkMapObj) == 0x60, "");

typedef TGmkList<GmkMapObj, GmkMapObj::BdatInfo, 0x4f50414d, 3, GmkMapObjGob> GmkMapObjList;

class GmkRoutedMapObj : public GmkRoute {
public:
  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_MAP_OBJ;

  ~GmkRoutedMapObj() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  u8 _50[0x60 - 0x50];
};

static_assert(sizeof(GmkRoutedMapObj) == 0x60, "");

typedef TGmkList<GmkRoutedMapObj, GmkMapObj::BdatInfo, 0x4f504d52, 7, GmkRouteGob> GmkRoutedMapObjList;

} // namespace gmk
