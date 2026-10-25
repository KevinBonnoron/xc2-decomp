#pragma once
#include <stddef.h>

#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkTriggerGob;

class GmkTrigger : public AGmkBase {
public:
  struct BdatInfo {};

  struct Data {
    int unknown00; // Role and original member name unknown.
    int unknown04; // Role and original member name unknown.
    int unknown08; // Role and original member name unknown.
    int unknown0c; // Role and original member name unknown.
    int unknown10; // Role and original member name unknown.
    int unknown14; // Role and original member name unknown.
    int unknown18; // Role and original member name unknown.
    int unknown1c; // Role and original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_TRIGGER;

  ~GmkTrigger() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void seqUpdate(f32 deltaTime);
  void applyPopCondMatched(bool matched);
  int getBindedMapGimmickNum() const;
  int getBindedEnemyNum() const;
  int getBindedRoutedEnemyNum() const;
  const AGmkBase *getBindedMapGimmick(u32 index) const;
  const AGmkBase *getBindedEnemy(u32 index) const;
  const AGmkBase *getBindedRoutedEnemy(u32 index) const;

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  u8 _48[0xd3 - 0x48];
  bool unknownD3; // Role and original member name unknown.
  u8 _d4[0xf0 - 0xd4];
};

static_assert(offsetof(GmkTrigger, unknownD3) == 0xd3, "");
static_assert(sizeof(GmkTrigger) == 0xf0, "");

typedef TGmkList<GmkTrigger, GmkTrigger::BdatInfo, 0x52475254, 2, GmkTriggerGob> GmkTriggerList;

} // namespace gmk
