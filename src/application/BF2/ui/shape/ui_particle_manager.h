#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace ui {

class UIParticleData;
class UIParticleEmitter;

class UIParticleManager : public mm::mtl::PtrSingleton<UIParticleManager> {
public:
  struct EmitterInfo : mm::mtl::IntrusiveListNodeBase {
    int unknown10;                // Inferred role: emitter id; original member name unknown.
    f32 unknown14;                // Inferred role: emission scale; original member name unknown.
    UIParticleEmitter *unknown18; // Inferred role: emitter; original member name unknown.
  };

  UIParticleManager();
  virtual ~UIParticleManager();
  int create(const UIParticleData &data);
  void remove(int emitter);
  UIParticleEmitter *getEmitter(int emitter);
  void setEmitterPos(int emitter, const mm::Pnt<s16> &pos);
  void setEmitterRot(int emitter, f32 rot);
  void setActivate(int emitter, bool activate);
  bool isActive(int emitter) const;
  void setLoadReduction(f32 reduction);
  int getAllEmissionCount();
  void update(const fw::UpdateInfo &info);

  mm::mtl::IntrusiveList<EmitterInfo> unknown08; // Inferred role: emitters; original member name unknown.
  u32 unknown20;                                 // Role and original member name unknown.
  f32 m_loadReduction;
};

static_assert(offsetof(UIParticleManager::EmitterInfo, unknown10) == 0x10, "");
static_assert(offsetof(UIParticleManager::EmitterInfo, unknown18) == 0x18, "");
static_assert(sizeof(UIParticleManager::EmitterInfo) == 0x20, "");
static_assert(offsetof(UIParticleManager, unknown08) == 0x08, "");
static_assert(offsetof(UIParticleManager, unknown20) == 0x20, "");
static_assert(offsetof(UIParticleManager, m_loadReduction) == 0x24, "");
static_assert(sizeof(UIParticleManager) == 0x28, "");

} // namespace ui
