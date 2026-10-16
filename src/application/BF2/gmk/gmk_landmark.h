#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkLandmarkGob;

class GmkLandmark : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0x10];
  };

  static const GmkType GMK_TYPE = GMK_TYPE_LANDMARK;

  ~GmkLandmark() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;

  u8 _48[0x100 - 0x48];
};

static_assert(sizeof(GmkLandmark::BdatInfo) == 0x10, "");
static_assert(sizeof(GmkLandmark) == 0x100, "");

typedef TGmkList<GmkLandmark, GmkLandmark::BdatInfo, 0x4b4d444c, 2, GmkLandmarkGob> GmkLandmarkList;

} // namespace gmk
