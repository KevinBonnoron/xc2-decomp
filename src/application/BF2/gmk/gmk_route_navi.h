#pragma once
#include <stddef.h>

#include "gmk/gmk_acc.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_route.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gmk {

class GmkRouteNavi {
public:
  struct InitResult {
    mm::Vec3 position;
    mm::Vec3 direction;
  };

  struct UpdateInfo {
    mm::Vec3 position;
  };

  struct CreateInfo {
    explicit CreateInfo(const GmkRoute *route);

    bool isValid() const;
    void validate(const GmkRoute &route);

    int unknown00;         // Inferred role: gmk set id; original member name unknown.
    GmkType unknown04;     // Inferred role: type; original member name unknown.
    u32 unknown08;         // Inferred role: index; original member name unknown.
    f32 unknown0c;         // Inferred role: width ratio; original member name unknown.
    f32 unknown10;         // Inferred role: arrive dist; original member name unknown.
    f32 unknown14;         // Inferred role: arrive height; original member name unknown.
    u32 unknown18;         // Inferred role: curve division num; original member name unknown.
    InitResult *unknown20; // Inferred role: init result; original member name unknown.
  };

  explicit GmkRouteNavi(const CreateInfo *info);

  void create(const CreateInfo &info);
  void dispose();
  void initIsReverse();
  bool initAtRandom(InitResult &result);
  void seqInit(const UpdateInfo &info);
  bool init(InitResult &result, u32 index, f32 ratio);
  int validatePointIndex(bool &isReverse, int index) const;
  bool getPosDirOnCurve(mm::Vec3 &position, mm::Vec3 &direction, u32 index, f32 ratio) const;
  bool getPosDirOnLine(mm::Vec3 &position, mm::Vec3 &direction, u32 index, f32 ratio) const;
  void update(const UpdateInfo &info);
  void updateNextPos();
  bool isArrived(const mm::Vec3 &targetPosition, const mm::Vec3 &position) const;
  void debugDraw();
  void updateNextPointIndx();
  f32 getWidthRatio() const;
  bool isRouteCurve(int index) const;
  void seqUpdateOnCurve(const UpdateInfo &info);
  void seqUpdateOnLine(const UpdateInfo &info);
  static const GmkRoute *findGmkRouteByBdatId(GmkType type, int bdatId);

  bool isValid() const { return unknown00.isValid() && unknown28.unknown38 != nullptr && unknown28.unknown38->isValid(); }
  const GmkRoute *getRoute() const { return static_cast<const GmkRoute *>(unknown28.unknown38); }
  int getPointStep() const { return unknowna4 ? -1 : 1; }

  CreateInfo unknown00;                                    // Inferred role: create info; original member name unknown.
  GmkAcc unknown28;                                        // Inferred role: acc; original member name unknown.
  f32 unknown68;                                           // Inferred role: arrive dist; original member name unknown.
  f32 unknown6c;                                           // Inferred role: arrive height; original member name unknown.
  void (GmkRouteNavi::*unknown70)(const UpdateInfo &info); // Inferred role: seq; original member name unknown.
  bool unknown80;                                          // Inferred role: has target pos; original member name unknown.
  mm::Vec3 unknown90;                                      // Inferred role: target pos; original member name unknown.
  int unknowna0;                                           // Inferred role: point index; original member name unknown.
  bool unknowna4;                                          // Inferred role: reverse; original member name unknown.
  u32 unknowna8;                                           // Inferred role: curve step; original member name unknown.
  f32 unknownac;                                           // Inferred role: curve angle; original member name unknown.
};

static_assert(sizeof(GmkRouteNavi::CreateInfo) == 0x28, "");
static_assert(offsetof(GmkRouteNavi, unknown28) == 0x28, "");
static_assert(offsetof(GmkRouteNavi, unknown68) == 0x68, "");
static_assert(offsetof(GmkRouteNavi, unknown70) == 0x70, "");
static_assert(offsetof(GmkRouteNavi, unknown80) == 0x80, "");
static_assert(offsetof(GmkRouteNavi, unknown90) == 0x90, "");
static_assert(offsetof(GmkRouteNavi, unknowna0) == 0xa0, "");
static_assert(offsetof(GmkRouteNavi, unknowna4) == 0xa4, "");
static_assert(offsetof(GmkRouteNavi, unknowna8) == 0xa8, "");
static_assert(offsetof(GmkRouteNavi, unknownac) == 0xac, "");
static_assert(sizeof(GmkRouteNavi) == 0xb0, "");

} // namespace gmk
