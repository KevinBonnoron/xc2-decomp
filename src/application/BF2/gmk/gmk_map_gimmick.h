#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkMapGimmickGob;

class GmkMapGimmick : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0x30];
  };

  static const GmkType GMK_TYPE = GMK_TYPE_MAP_GIMMICK;

  ~GmkMapGimmick() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0xb0 - 0x48];
};

static_assert(sizeof(GmkMapGimmick::BdatInfo) == 0x30, "");
static_assert(sizeof(GmkMapGimmick) == 0xb0, "");

class GmkMapGimmickList : public TGmkList<GmkMapGimmick, GmkMapGimmick::BdatInfo, 0x4750414d, 2, GmkMapGimmickGob> {
public:
  explicit GmkMapGimmickList(u32 updateGmkNumPerFrame);
  ~GmkMapGimmickList() override;

  const AGmkBase *getInst(u32 index) const override;
  void setUpdateGmkNumPerFrame(u32 num) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  bool updateImmediate() override;
  void debugUpdateMmf() override;
  void debugDraw() const override;

protected:
  void createGmk(void *data) override;

private:
  u8 _228[0x460 - 0x228];
};

static_assert(sizeof(GmkMapGimmickList) == 0x460, "");

} // namespace gmk
