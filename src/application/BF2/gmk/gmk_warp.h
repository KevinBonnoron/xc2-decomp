#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace mm {
struct Vec3;
} // namespace mm
struct CBdatWrapper;

namespace gmk {

class GmkWarpGobCustom;

class GmkWarp : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched(const mm::Vec3 &position) const;
    bool isPopCondCommonMatched() const;
    bool isDepopCondMatched(const mm::Vec3 &position) const;
    void debugDraw(const AGmkBase &gmk) const;

    u16 condition;
    u16 nameRadius;
    BootedGmkCond bootedGmk;
    DistHvCond popDist;
    DistHvCond depopDist;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_WARP;

  static const u32 POINT_NUM = 2;

  GmkWarp();
  ~GmkWarp() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  void create(const CreateInfo &info) override;
  void dispose() override;
  void clearIcons();
  void clearGobInsts();
  void update(f32 deltaTime) override;
  void createIcon(u32 index);
  void disposeIcon(u32 index, bool isFadeOut);
  void debugDraw() const override;
  void debugUpdateMmf() override;
  void validateIconPos();
  void validateDisp() const;
  void reqDeadIcon();
  void reqRecreateIcon();
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override {}

  u8 _48[0x50 - 0x48];
  gf::GF_OBJ_HANDLE *handles[POINT_NUM];
  u32 iconHandles[POINT_NUM];
  DistCond iconDist;
  bool isIconDead;
  bool isDisp;
};

static_assert(offsetof(GmkWarp, handles) == 0x50, "");
static_assert(offsetof(GmkWarp, iconHandles) == 0x60, "");
static_assert(offsetof(GmkWarp, iconDist) == 0x68, "");
static_assert(offsetof(GmkWarp, isIconDead) == 0x6c, "");
static_assert(offsetof(GmkWarp, isDisp) == 0x6d, "");

static_assert(sizeof(GmkWarp::BdatInfo) == 0x18, "");
static_assert(sizeof(GmkWarp) == 0x70, "");

typedef TGmkList<GmkWarp, GmkWarp::BdatInfo, 0x50524157, 1, GmkWarpGobCustom> GmkWarpList;

} // namespace gmk
