#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkJumpGobCustom;

class GmkJump : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0x6];
  };

  static const GmkType GMK_TYPE = GMK_TYPE_JUMP;

  ~GmkJump() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;
  void debugUpdateMmf() override;

  u8 _48[0x80 - 0x48];
};

static_assert(sizeof(GmkJump::BdatInfo) == 0x6, "");
static_assert(sizeof(GmkJump) == 0x80, "");

typedef TGmkList<GmkJump, GmkJump::BdatInfo, 0x504d554a, 3, GmkJumpGobCustom> GmkJumpList;

} // namespace gmk
