#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkNpcGob;

class GmkNpc : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0x30];
  };

  static const GmkType GMK_TYPE = GMK_TYPE_NPC;

  ~GmkNpc() override;
  GmkType getGmkType() const override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x70 - 0x48];
};

static_assert(sizeof(GmkNpc::BdatInfo) == 0x30, "");
static_assert(sizeof(GmkNpc) == 0x70, "");

class GmkNpcList : public TGmkList<GmkNpc, GmkNpc::BdatInfo, 0x43504e, 4, GmkNpcGob> {
public:
  explicit GmkNpcList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}
  ~GmkNpcList() override;

protected:
  void createGmk(void *data) override;
  void disposeGmk() override;
};

} // namespace gmk
