#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkClimbingGob;

class GmkClimbing : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0x10];
  };

  static const GmkType GMK_TYPE = GMK_TYPE_CLIMBING;

  ~GmkClimbing() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;

  u8 _48[0x60 - 0x48];
};

static_assert(sizeof(GmkClimbing::BdatInfo) == 0x10, "");
static_assert(sizeof(GmkClimbing) == 0x60, "");

typedef TGmkList<GmkClimbing, GmkClimbing::BdatInfo, 0x424d4c43, 2, GmkClimbingGob> GmkClimbingList;

} // namespace gmk
