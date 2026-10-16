#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkWarpGobCustom;

class GmkWarp : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0x18];
  };

  static const GmkType GMK_TYPE = GMK_TYPE_WARP;

  ~GmkWarp() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;
  void debugUpdateMmf() override;

  u8 _48[0x70 - 0x48];
};

static_assert(sizeof(GmkWarp::BdatInfo) == 0x18, "");
static_assert(sizeof(GmkWarp) == 0x70, "");

typedef TGmkList<GmkWarp, GmkWarp::BdatInfo, 0x50524157, 1, GmkWarpGobCustom> GmkWarpList;

} // namespace gmk
