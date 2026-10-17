#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

struct CBdatWrapper;

namespace mm {
struct Col4;
}

namespace gmk {

class GmkRouteGob;
class GmkRoutePoint;
class GmkRoutePointGobCustom;

class GmkRoute : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
  };

  struct Data {
    u32 firstPointIndex;
    u32 endPointIndex;
    u8 _08[0xc - 0x8];
    u32 flags;
  };

  static const u32 FLAG_CLOSED = 1 << 0;

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTE;

  GmkRoute() : _48() {}
  ~GmkRoute() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  bool isValid() const override;
  void create(const CreateInfo &info) override { AGmkBase::create(info); }
  void dispose() override { AGmkBase::dispose(); }
  void debugDraw() const override;
  void debugUpdateMmf() override;
  virtual const IGmkList *getBindedRoutePointList() const;

  u32 getRoutePointNum() const;
  bool isClosed() const;
  const GmkRoutePoint *getRoutePoint(u32 index) const;
  bool getRoutePointPos(mm::Vec3 &position, u32 index) const;
  bool getNearestPos(mm::Vec3 &nearestPos, const mm::Vec3 &position) const;
  void debugDraw(bool isSelected) const;
  void debugDrawRoute(const mm::Col4 &color) const;

  const Data *getData() const { return static_cast<const Data *>(createInfo.data); }

  u8 _48[0x50 - 0x48];
};

static_assert(sizeof(GmkRoute::Data) == 0x10, "");
static_assert(sizeof(GmkRoute) == 0x50, "");

typedef TGmkList<GmkRoute, GmkRoute::BdatInfo, 0x56525543, 5, GmkRouteGob> GmkRouteList;

class GmkRoutePoint : public AGmkBase {
public:
  struct BdatInfo {};

  struct Data {
    mm::Vec3 position;
    mm::Vec3 extent;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTE_POINT;

  ~GmkRoutePoint() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  bool isValid() const override { return baseInfo.list != nullptr && createInfo.data != nullptr; }
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugDraw() const override;
  void debugUpdateMmf() override;

  const Data *getData() const { return static_cast<const Data *>(createInfo.data); }

  u8 _48[0x50 - 0x48];
};

static_assert(sizeof(GmkRoutePoint::Data) == 0x20, "");
static_assert(sizeof(GmkRoutePoint) == 0x50, "");

class GmkRoutePointList : public TGmkList<GmkRoutePoint, GmkRoutePoint::BdatInfo, 0x54505443, 2, GmkRoutePointGobCustom> {
public:
  explicit GmkRoutePointList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

protected:
  void createGmk(void *data) override;
};

} // namespace gmk
