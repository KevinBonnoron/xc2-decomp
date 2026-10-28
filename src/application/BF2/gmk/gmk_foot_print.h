#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_route.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
struct Col4;
struct Vec3;
} // namespace mm

namespace gmk {

class GmkRoutedFootPrintGobCustom;
class GmkRoutedFootPrintPoint;
class GmkRoutedFootPrintPointGobCustom;
class GmkRoutedFootPrintPointList;

class GmkRoutedFootPrint : public AGmkBase {
public:
  struct BdatInfo {
    BdatInfo() : unknown00(nullptr), unknown08(0) {}
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched() const;

    const char *unknown00;      // Inferred role: foot effect; original member name unknown.
    u16 unknown08;              // Inferred role: condition; original member name unknown.
    ScenarioFlagCond unknown0a; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown0e;    // Inferred role: quest flag; original member name unknown.
  };

  struct Data {
    u8 _00[0xc];
    u32 unknown0c; // Inferred role: first point index; original member name unknown.
    u32 unknown10; // Inferred role: end point index; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_FOOT_PRINT;

  GmkRoutedFootPrint();
  ~GmkRoutedFootPrint() override { dispose(); }
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void debugDraw(bool isSelected) const;
  void debugDrawRoute(const mm::Col4 &color) const;
  const GmkRoutedFootPrintPoint *getRoutePoint(u32 index) const;
  u32 getRoutePointNum() const;
  bool getRoutePointPos(mm::Vec3 &position, u32 index) const;
  const GmkRoutedFootPrintPointList *getBindedRoutePointList() const;

  void *unknown48; // Role and original member name unknown.
  void *unknown50; // Role and original member name unknown.
  void *unknown58; // Role and original member name unknown.

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }
};

static_assert(sizeof(GmkRoutedFootPrint::BdatInfo) == 0x18, "");
static_assert(offsetof(GmkRoutedFootPrint, unknown48) == 0x48, "");
static_assert(offsetof(GmkRoutedFootPrint, unknown50) == 0x50, "");
static_assert(offsetof(GmkRoutedFootPrint, unknown58) == 0x58, "");
static_assert(sizeof(GmkRoutedFootPrint) == 0x60, "");

typedef TGmkList<GmkRoutedFootPrint, GmkRoutedFootPrint::BdatInfo, 0x54504652, 2, GmkRoutedFootPrintGobCustom> GmkRoutedFootPrintList;

class GmkRoutedFootPrintPoint : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_FOOT_PRINT_POINT;

  GmkRoutedFootPrintPoint();
  ~GmkRoutedFootPrintPoint() override { dispose(); }
  GmkType getGmkType() const override;
  bool isValid() const override;
  void dispose() override;
  void disposeEffInst(bool isFadeOut);
  void createEffInst(void *data);
  void updateConcrete(void *data, f32 deltaTime);
  void applyEffectParam(bool isDisp) const;
  void validateDisp() const;

  DistHvCond unknown48; // Role and original member name unknown.
  u32 unknown50;        // Inferred role: effect handle; original member name unknown.
  bool unknown54;       // Inferred role: disp; original member name unknown.

  const GmkRoutePoint::Data *getData() const { return static_cast<const GmkRoutePoint::Data *>(unknown20.unknown08); }
};

static_assert(offsetof(GmkRoutedFootPrintPoint, unknown48) == 0x48, "");
static_assert(offsetof(GmkRoutedFootPrintPoint, unknown50) == 0x50, "");
static_assert(offsetof(GmkRoutedFootPrintPoint, unknown54) == 0x54, "");
static_assert(sizeof(GmkRoutedFootPrintPoint) == 0x58, "");

class GmkRoutedFootPrintPointList : public TGmkList<GmkRoutedFootPrintPoint, GmkRoutedFootPrintPoint::BdatInfo, 0x50504652, 1, GmkRoutedFootPrintPointGobCustom> {
public:
  explicit GmkRoutedFootPrintPointList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

  // Inlined access to the point vector; the original helper name is unknown.
  const GmkRoutedFootPrintPoint *unknown001(u32 index) const { return &gmkInsts[index]; }
};

} // namespace gmk
