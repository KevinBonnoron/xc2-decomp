#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkBattleLockGob;

class GmkBattleLock : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_BATTLE_LOCK;

  ~GmkBattleLock() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;

  u8 _48[0xd0 - 0x48];
};

static_assert(sizeof(GmkBattleLock) == 0xd0, "");

typedef TGmkList<GmkBattleLock, GmkBattleLock::BdatInfo, 0x434c5442, 3, GmkBattleLockGob> GmkBattleLockList;

} // namespace gmk
