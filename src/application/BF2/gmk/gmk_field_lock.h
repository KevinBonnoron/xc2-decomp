#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkFieldLockGob;

class GmkFieldLock : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0xe];
  };

  static const GmkType GMK_TYPE = GMK_TYPE_FIELD_LOCK;

  ~GmkFieldLock() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;

  u8 _48[0xd0 - 0x48];
};

static_assert(sizeof(GmkFieldLock::BdatInfo) == 0xe, "");
static_assert(sizeof(GmkFieldLock) == 0xd0, "");

typedef TGmkList<GmkFieldLock, GmkFieldLock::BdatInfo, 0x434c4446, 2, GmkFieldLockGob> GmkFieldLockList;

} // namespace gmk
