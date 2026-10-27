#pragma once
#include "mm_mtl/delegate.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

class GfSlowAttack : public mm::mtl::PtrSingleton<GfSlowAttack> {
public:
  GfSlowAttack();
  ~GfSlowAttack();
  void update(const fw::UpdateInfo &info);
  void updateForIdle(const fw::UpdateInfo &info);
  void updateForPlay(const fw::UpdateInfo &info);
  void updateForTerm(const fw::UpdateInfo &info);
  void setSpeedEnvronment(f32 speed);
  f32 getPlaySpeed() const;
  static GfSlowAttack *create();
  static void destroy();
  void finish();
  s32 getState() const;
  void executeSlow();

  s32 m_state;                                               // Name from getState().
  mm::mtl::Delegate<void(const fw::UpdateInfo &)> unknown10; // Inferred role: update callback; original member name unknown.
  bool unknown30;                                            // Inferred role: slow requested by executeSlow; original member name unknown.
};

static_assert(offsetof(GfSlowAttack, m_state) == 0x08, "");
static_assert(offsetof(GfSlowAttack, unknown10) == 0x10, "");
static_assert(offsetof(GfSlowAttack, unknown30) == 0x30, "");
static_assert(sizeof(GfSlowAttack) == 0x38, "");

} // namespace gf
