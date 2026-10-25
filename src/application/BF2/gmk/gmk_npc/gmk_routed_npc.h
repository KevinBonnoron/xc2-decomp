#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_npc/gmk_npc.h"
#include "gmk/gmk_route.h"
#include "types.h"

namespace gmk {

class GmkRouteGob;

class GmkRoutedNpc : public GmkRoute {
public:
  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_NPC;

  ~GmkRoutedNpc() override;
  GmkType getGmkType() const override;
  const IGmkList *getBindedRoutePointList() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  int getBindedBdatId() const;
  u8 *getBindedBdatFp() const;
  bool isPopCondMatched() const;
  bool isDepopCondMatched() const;
  bool isPopDistCondMatched() const;
  bool isDepopDistCondMatched() const;

  const GmkNpc::BdatInfo *getBdatInfo() const { return reinterpret_cast<const GmkNpc::BdatInfo *>(unknown20.unknown10); }

  u8 _50[0xa0 - 0x50];
};

static_assert(sizeof(GmkRoutedNpc) == 0xa0, "");

class GmkRoutedNpcList : public TGmkList<GmkRoutedNpc, GmkNpc::BdatInfo, 0x43504e52, 6, GmkRouteGob> {
public:
  explicit GmkRoutedNpcList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}
  ~GmkRoutedNpcList() override;

  void create(const CreateInfo &info) override;

protected:
  void createGmk(void *data) override;
  void disposeGmk() override;
};

} // namespace gmk
