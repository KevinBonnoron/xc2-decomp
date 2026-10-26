#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

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
    u32 unknown00; // Inferred role: first point index; original member name unknown.
    u32 unknown04; // Inferred role: end point index; original member name unknown.
    f32 unknown08; // Inferred role: curve radius; original member name unknown.
    u32 unknown0c; // Inferred role: flags; original member name unknown.
    s8 unknown10;  // Inferred role: width side; original member name unknown.
  };

  static const u32 FLAG_CLOSED = 1 << 0;
  static const u32 FLAG_FORWARD = 1 << 1;
  static const u32 FLAG_REVERSE = 1 << 2;

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTE;

  GmkRoute();
  ~GmkRoute() override { GmkRoute::dispose(); }
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
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

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  u8 _48[0x50 - 0x48];
};

static_assert(offsetof(GmkRoute::Data, unknown10) == 0x10, "");
static_assert(sizeof(GmkRoute) == 0x50, "");

typedef TGmkList<GmkRoute, GmkRoute::BdatInfo, 0x56525543, 5, GmkRouteGob> GmkRouteList;

class GmkRoutePoint : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  struct Data {
    mm::Vec3 unknown00; // Inferred role: position; original member name unknown.
    f32 unknown10;      // Inferred role: side x; original member name unknown.
    f32 unknown14;      // Inferred role: side y; original member name unknown.
    f32 unknown18;      // Inferred role: side z; original member name unknown.
    u32 unknown1c;      // Inferred role: flags; original member name unknown.
  };

  static const u32 FLAG_LINE = 1 << 0;

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTE_POINT;

  ~GmkRoutePoint() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  bool isValid() const override { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugDraw() const override;
  void debugUpdateMmf() override;

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  u8 _48[0x50 - 0x48];
};

static_assert(offsetof(GmkRoutePoint::Data, unknown1c) == 0x1c, "");
static_assert(sizeof(GmkRoutePoint::Data) == 0x20, "");
static_assert(sizeof(GmkRoutePoint) == 0x50, "");

class GmkRoutePointList : public TGmkList<GmkRoutePoint, GmkRoutePoint::BdatInfo, 0x54505443, 2, GmkRoutePointGobCustom> {
public:
  explicit GmkRoutePointList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

protected:
  void createGmk(void *data) override;
};

} // namespace gmk
