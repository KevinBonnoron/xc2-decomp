#pragma once
#include "mm_mtl/delegate.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
class GfWeapon;

class GfTrinityAttack : public mm::mtl::PtrSingleton<GfTrinityAttack> {
public:
  GfTrinityAttack();
  ~GfTrinityAttack();
  void update(const fw::UpdateInfo &info);
  void updateForSetup(const fw::UpdateInfo &info);
  void updateForPlay(const fw::UpdateInfo &info);
  static GfTrinityAttack *create();
  static void destroy();
  void finish();
  void endAttack();
  u32 getBladeId() const;
  bool isEnableAttackMember() const;
  bool isLoading() const;
  s32 getState() const;
  GF_OBJ_HANDLE *getBlade() const;
  GfWeapon *getWeapon() const;

  s32 m_state;                                               // Name from getState().
  mm::mtl::Delegate<void(const fw::UpdateInfo &)> unknown10; // Inferred role: update callback; original member name unknown.
  GF_OBJ_HANDLE *m_blade;                                    // Name from getBlade().
};

static_assert(offsetof(GfTrinityAttack, m_state) == 0x08, "");
static_assert(offsetof(GfTrinityAttack, unknown10) == 0x10, "");
static_assert(offsetof(GfTrinityAttack, m_blade) == 0x30, "");
static_assert(sizeof(GfTrinityAttack) == 0x38, "");

} // namespace gf
