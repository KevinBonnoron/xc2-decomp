#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkDoorGob;

class GmkDoor : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0x48];
  };

  static const GmkType GMK_TYPE = GMK_TYPE_DOOR;

  ~GmkDoor() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x360 - 0x48];
};

static_assert(sizeof(GmkDoor::BdatInfo) == 0x48, "");
static_assert(sizeof(GmkDoor) == 0x360, "");

typedef TGmkList<GmkDoor, GmkDoor::BdatInfo, 0x524f4f44, 2, GmkDoorGob> GmkDoorList;

} // namespace gmk
