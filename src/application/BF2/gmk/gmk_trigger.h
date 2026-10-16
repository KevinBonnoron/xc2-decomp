#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkTriggerGob;

class GmkTrigger : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_TRIGGER;

  ~GmkTrigger() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;

  u8 _48[0xf0 - 0x48];
};

static_assert(sizeof(GmkTrigger) == 0xf0, "");

typedef TGmkList<GmkTrigger, GmkTrigger::BdatInfo, 0x52475254, 2, GmkTriggerGob> GmkTriggerList;

} // namespace gmk
