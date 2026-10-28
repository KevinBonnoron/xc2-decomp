#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_npc/gmk_npc.h"
#include "gmk/gmk_route.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class GmkRouteGob;
class GmkRouteNavi;

class GmkRoutedNpc : public GmkRoute, public AGmkNpc {
public:
  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_NPC;

  ~GmkRoutedNpc() override;
  GmkType getGmkType() const override;
  const IGmkList *getBindedRoutePointList() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  gf::GF_OBJ_HANDLE *getGobInst() const;
  bool isPopCondMatchedExceptDist() const;
  bool isPopCondMatched() const override;
  bool isDepopCondMatched() const override;
  bool isPopDistCondMatched() const override;
  bool isDepopDistCondMatched() const override;
  u8 *getBindedBdatFp() const override;
  int getBindedBdatId() const override;
  bool findPopPosRot(mm::Vec3 &position, mm::Vec3 &rotation) const override;
  void bindToGameObj(gf::GF_OBJ_HANDLE *handle) const override;
  void unbindToGameObj(gf::GF_OBJ_HANDLE *handle) const override;
  void validateDisp() const override;

  const GmkNpc::BdatInfo *getBdatInfo() const { return reinterpret_cast<const GmkNpc::BdatInfo *>(GmkRoute::unknown20.unknown10); }

  GmkRouteNavi *unknown70;    // Inferred role: route navi; original member name unknown.
  bool unknown78;             // Role and original member name unknown.
  bool unknown79;             // Inferred role: display enabled; original member name unknown.
  mutable mm::Vec3 unknown80; // Inferred role: position; original member name unknown.
  mutable mm::Quat unknown90; // Inferred role: rotation; original member name unknown.
};

static_assert(offsetof(GmkRoutedNpc, unknown70) == 0x70, "");
static_assert(offsetof(GmkRoutedNpc, unknown78) == 0x78, "");
static_assert(offsetof(GmkRoutedNpc, unknown79) == 0x79, "");
static_assert(offsetof(GmkRoutedNpc, unknown80) == 0x80, "");
static_assert(offsetof(GmkRoutedNpc, unknown90) == 0x90, "");
static_assert(sizeof(GmkRoutedNpc) == 0xa0, "");

class GmkRoutedNpcList : public TGmkList<GmkRoutedNpc, GmkNpc::BdatInfo, 0x43504e52, 6, GmkRouteGob> {
public:
  explicit GmkRoutedNpcList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}
  ~GmkRoutedNpcList() override { dispose(); }

  void create(const CreateInfo &info) override;

protected:
  void createGmk(void *data) override;
  void disposeGmk() override;
};

} // namespace gmk
