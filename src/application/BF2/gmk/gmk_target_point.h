#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"

namespace gmk {

class GmkTargetPointGob;

class GmkTargetPoint : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  static const GmkType GMK_TYPE = GMK_TYPE_TARGET_POINT;

  GmkTargetPoint() {}
  ~GmkTargetPoint() override { dispose(); }
  GmkType getGmkType() const override;
  bool isValid() const override;
};

static_assert(sizeof(GmkTargetPoint) == 0x48, "");

typedef TGmkList<GmkTargetPoint, GmkTargetPoint::BdatInfo, 0x54504754, 1, GmkTargetPointGob> GmkTargetPointList;

} // namespace gmk
