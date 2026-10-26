#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkMobGob;

class GmkMob : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  static const GmkType GMK_TYPE = GMK_TYPE_MOB;

  ~GmkMob() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x118 - 0x48];
};

static_assert(sizeof(GmkMob) == 0x118, "");

class GmkMobList : public TGmkList<GmkMob, GmkMob::BdatInfo, 0x424f4d, 2, GmkMobGob> {
public:
  explicit GmkMobList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame), unknown228(0) {}

protected:
  void onResetUpdateGmkIndex() override;

private:
  u32 unknown228; // Inferred role: update round count; original member name unknown.
};

static_assert(sizeof(GmkMobList) == 0x230, "");

} // namespace gmk
