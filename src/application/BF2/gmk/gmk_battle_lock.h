#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_collision.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkBattleLockGob;

class GmkBattleLock : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  static const GmkType GMK_TYPE = GMK_TYPE_BATTLE_LOCK;

  ~GmkBattleLock() override { dispose(); }
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void applyEffectParam() const;
  void createGmkCollision();
  void createEffect();
  void disposeEffect(bool isFadeOut);

  u8 _48[0x50 - 0x48];
  GmkCollision unknown50; // Inferred role: collision; original member name unknown.
  u8 _b8[0xc0 - 0xb8];
  u32 unknownc0;         // Inferred role: effect handle; original member name unknown.
  mutable int unknownc4; // Inferred role: number of enemies that hold the battle lock; original member name unknown.
  u8 _c8[0xd0 - 0xc8];
};

static_assert(offsetof(GmkBattleLock, unknown50) == 0x50, "");
static_assert(offsetof(GmkBattleLock, unknownc0) == 0xc0, "");
static_assert(offsetof(GmkBattleLock, unknownc4) == 0xc4, "");
static_assert(sizeof(GmkBattleLock) == 0xd0, "");

typedef TGmkList<GmkBattleLock, GmkBattleLock::BdatInfo, 0x434c5442, 3, GmkBattleLockGob> GmkBattleLockList;

} // namespace gmk
