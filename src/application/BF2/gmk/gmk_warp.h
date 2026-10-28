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
    BdatInfo() : unknown00(0), unknown02(10), unknown08(), unknown10() {}
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched(const mm::Vec3 &position) const;
    bool isPopCondCommonMatched() const;
    bool isDepopCondMatched(const mm::Vec3 &position) const;
    void debugDraw(const AGmkBase &gmk) const;

    u16 unknown00;           // Inferred role: condition; original member name unknown.
    u16 unknown02;           // Inferred role: name radius; original member name unknown.
    BootedGmkCond unknown04; // Inferred role: booted gmk; original member name unknown.
    DistHvCond unknown08;    // Inferred role: pop dist; original member name unknown.
    DistHvCond unknown10;    // Inferred role: depop dist; original member name unknown.
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
  gf::GF_OBJ_HANDLE *unknown50[POINT_NUM]; // Inferred role: handles; original member name unknown.
  u32 unknown60[POINT_NUM];                // Inferred role: icon handles; original member name unknown.
  DistCond unknown68;                      // Inferred role: icon dist; original member name unknown.
  bool unknown6c;                          // Inferred role: icon dead; original member name unknown.
  bool unknown6d;                          // Inferred role: disp; original member name unknown.
};

static_assert(offsetof(GmkWarp, unknown50) == 0x50, "");
static_assert(offsetof(GmkWarp, unknown60) == 0x60, "");
static_assert(offsetof(GmkWarp, unknown68) == 0x68, "");
static_assert(offsetof(GmkWarp, unknown6c) == 0x6c, "");
static_assert(offsetof(GmkWarp, unknown6d) == 0x6d, "");

static_assert(sizeof(GmkWarp::BdatInfo) == 0x18, "");
static_assert(sizeof(GmkWarp) == 0x70, "");

typedef TGmkList<GmkWarp, GmkWarp::BdatInfo, 0x50524157, 1, GmkWarpGobCustom> GmkWarpList;

} // namespace gmk
