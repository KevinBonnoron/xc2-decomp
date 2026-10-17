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

    int gmkSetId;
    GmkType type;
    u32 index;
    f32 widthRatio;
    f32 arriveDist;
    f32 arriveHeight;
    u32 curveDivisionNum;
    InitResult *initResult;
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

  bool isValid() const { return createInfo.isValid() && acc.gmk != nullptr && acc.gmk->isValid(); }
  const GmkRoute *getRoute() const { return static_cast<const GmkRoute *>(acc.gmk); }
  int getPointStep() const { return isReverse ? -1 : 1; }

  CreateInfo createInfo;
  GmkAcc acc;
  f32 arriveDist;
  f32 arriveHeight;
  void (GmkRouteNavi::*seq)(const UpdateInfo &info);
  bool hasTargetPos;
  mm::Vec3 targetPos;
  int pointIndex;
  bool isReverse;
  u32 curveStep;
  f32 curveAngle;
};

static_assert(sizeof(GmkRouteNavi::CreateInfo) == 0x28, "");
static_assert(offsetof(GmkRouteNavi, acc) == 0x28, "");
static_assert(offsetof(GmkRouteNavi, arriveDist) == 0x68, "");
static_assert(offsetof(GmkRouteNavi, seq) == 0x70, "");
static_assert(offsetof(GmkRouteNavi, hasTargetPos) == 0x80, "");
static_assert(offsetof(GmkRouteNavi, targetPos) == 0x90, "");
static_assert(offsetof(GmkRouteNavi, pointIndex) == 0xa0, "");
static_assert(offsetof(GmkRouteNavi, isReverse) == 0xa4, "");
static_assert(offsetof(GmkRouteNavi, curveStep) == 0xa8, "");
static_assert(offsetof(GmkRouteNavi, curveAngle) == 0xac, "");
static_assert(sizeof(GmkRouteNavi) == 0xb0, "");

} // namespace gmk
