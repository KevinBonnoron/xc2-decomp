#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkPreciousGob;

class GmkPrecious : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0x30];
  };

  static const GmkType GMK_TYPE = GMK_TYPE_PRECIOUS;

  ~GmkPrecious() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x78 - 0x48];
};

static_assert(sizeof(GmkPrecious::BdatInfo) == 0x30, "");
static_assert(sizeof(GmkPrecious) == 0x78, "");

typedef TGmkList<GmkPrecious, GmkPrecious::BdatInfo, 0x53435250, 2, GmkPreciousGob> GmkPreciousList;

} // namespace gmk
