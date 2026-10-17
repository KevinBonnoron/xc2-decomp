#pragma once
#include "anm/anm_asm_blender.h"
#include "anm/anm_asm_state.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {
class ResStateData;

class FrozenState : public AsmState {
public:
  FrozenState(const ResStateData *pResStateData, mm::mtl::IAllocator &allocator);
  ~FrozenState() override;
  void attach(AsmBlender *blender) override;
  void dettach(AsmBlender *blender) override;
  void onEnter(AsmListener *listener) override;
  void onLeave(AsmListener *listener) override;
  void update(f32 deltaTime, AsmListener *listener) override;
  f32 getLocalTime() const override;
  void onSetWeight() override;
  void setLocalTime(f32 time) override;
  void onSetSpeed() override;
  const AsmClip *getBaseClip() const override;

  AsmClip m_clip;
};

} // namespace anm
