#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkRouteGob;
class GmkRoutePointGobCustom;

class GmkRoute : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTE;

  ~GmkRoute() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugDraw() const override;
  void debugUpdateMmf() override;

  u8 _48[0x50 - 0x48];
};

static_assert(sizeof(GmkRoute) == 0x50, "");

typedef TGmkList<GmkRoute, GmkRoute::BdatInfo, 0x56525543, 5, GmkRouteGob> GmkRouteList;

class GmkRoutePoint : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTE_POINT;

  ~GmkRoutePoint() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugDraw() const override;
  void debugUpdateMmf() override;

  u8 _48[0x50 - 0x48];
};

static_assert(sizeof(GmkRoutePoint) == 0x50, "");

class GmkRoutePointList : public TGmkList<GmkRoutePoint, GmkRoutePoint::BdatInfo, 0x54505443, 2, GmkRoutePointGobCustom> {
public:
  explicit GmkRoutePointList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

protected:
  void createGmk(void *data) override;
};

} // namespace gmk
