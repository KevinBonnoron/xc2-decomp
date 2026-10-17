#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_route.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace mm {
struct Vec3;
} // namespace mm
struct CBdatWrapper;

namespace gmk {

class GmkMapObjGob;
class GmkRouteGob;

class GmkMapObj : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched(const mm::Vec3 &position) const;
    bool isDepopCondMatched(const mm::Vec3 &position) const;

    u16 condition;
    u8 priority;
    DistHvCond popDist;
    DistHvCond depopDist;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_MAP_OBJ;

  GmkMapObj();
  ~GmkMapObj() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  void reqDisposeGob(f32 fadeTime, u32 attribute) const;
  void dispose() override;
  void disposeGobInst(bool isFadeOut);
  void update(f32 deltaTime) override;
  bool canPopGobInst() const;
  void createGobInst();
  bool canDepopGobInst() const;
  void validateDisp() const;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(createInfo.info); }

  gf::GF_OBJ_HANDLE *handle;
  bool isDisp;
  bool isRemoved;
  bool isRevived;
  mutable f32 disposeFadeTime;
  mutable u32 disposeAttribute;
};

static_assert(sizeof(GmkMapObj::BdatInfo) == 0x14, "");
static_assert(offsetof(GmkMapObj, handle) == 0x48, "");
static_assert(offsetof(GmkMapObj, isDisp) == 0x50, "");
static_assert(offsetof(GmkMapObj, isRemoved) == 0x51, "");
static_assert(offsetof(GmkMapObj, isRevived) == 0x52, "");
static_assert(offsetof(GmkMapObj, disposeFadeTime) == 0x54, "");
static_assert(offsetof(GmkMapObj, disposeAttribute) == 0x58, "");
static_assert(sizeof(GmkMapObj) == 0x60, "");

typedef TGmkList<GmkMapObj, GmkMapObj::BdatInfo, 0x4f50414d, 3, GmkMapObjGob> GmkMapObjList;

class GmkRoutedMapObj : public GmkRoute {
public:
  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_MAP_OBJ;

  GmkRoutedMapObj();
  ~GmkRoutedMapObj() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  void create(const CreateInfo &info) override;
  void dispose() override;
  void disposeGobInst();
  void update(f32 deltaTime) override;
  bool canPopGobInst() const;
  void createGobInst();
  bool canDepopGobInst() const;
  void validateDisp() const;
  const IGmkList *getBindedRoutePointList() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  const GmkMapObj::BdatInfo *getBdatInfo() const { return reinterpret_cast<const GmkMapObj::BdatInfo *>(createInfo.info); }

  gf::GF_OBJ_HANDLE *handle;
  bool isDisp;
};

static_assert(offsetof(GmkRoutedMapObj, handle) == 0x50, "");
static_assert(offsetof(GmkRoutedMapObj, isDisp) == 0x58, "");
static_assert(sizeof(GmkRoutedMapObj) == 0x60, "");

typedef TGmkList<GmkRoutedMapObj, GmkMapObj::BdatInfo, 0x4f504d52, 7, GmkRouteGob> GmkRoutedMapObjList;

} // namespace gmk
