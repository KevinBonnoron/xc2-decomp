#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkRoutedFootPrintGobCustom;
class GmkRoutedFootPrintPointGobCustom;

class GmkRoutedFootPrint : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched() const;

    const char *unknown00;      // Inferred role: foot effect; original member name unknown.
    u16 unknown08;              // Inferred role: condition; original member name unknown.
    ScenarioFlagCond unknown0a; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown0e;    // Inferred role: quest flag; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_FOOT_PRINT;

  ~GmkRoutedFootPrint() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;

  u8 _48[0x60 - 0x48];
};

static_assert(sizeof(GmkRoutedFootPrint::BdatInfo) == 0x18, "");
static_assert(sizeof(GmkRoutedFootPrint) == 0x60, "");

typedef TGmkList<GmkRoutedFootPrint, GmkRoutedFootPrint::BdatInfo, 0x54504652, 2, GmkRoutedFootPrintGobCustom> GmkRoutedFootPrintList;

class GmkRoutedFootPrintPoint : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_FOOT_PRINT_POINT;

  ~GmkRoutedFootPrintPoint() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void dispose() override;

  u8 _48[0x58 - 0x48];
};

static_assert(sizeof(GmkRoutedFootPrintPoint) == 0x58, "");

class GmkRoutedFootPrintPointList : public TGmkList<GmkRoutedFootPrintPoint, GmkRoutedFootPrintPoint::BdatInfo, 0x50504652, 1, GmkRoutedFootPrintPointGobCustom> {
public:
  explicit GmkRoutedFootPrintPointList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}
};

} // namespace gmk
