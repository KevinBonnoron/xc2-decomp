#pragma once
#include <stddef.h>

#include "framework/anim/anim_control_updater.h"
#include "framework/anim/anim_pose_sampler.h"
#include "gf/object/component/animation/gf_com_animation.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace anm {
class Control;
} // namespace anm
namespace arc {
class CArcData;
} // namespace arc
namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComModel;

class GfComPackAnim : public GfComAnimation {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 ARC_MAX = 8;

  struct SetupInfo {
    mm::mtl::FixedVector<void *, ARC_MAX> arcs;
    const char *name;
    bool isLocalSpace;
  };

  class Mot {
  public:
    Mot();
    void cleanup(u32 layer);
    void stop(u32 layer);
    void setup(GfComModel *model, u32 layer);
    void play(u32 layer, void *motion, bool isLocalSpace);
    bool isPlayEnd() const;
    void setSpeed(f32 speed);
    void changeLayer(u32 oldLayer, u32 newLayer);

    GfComModel *model;
    anm::Control *control;
    fw::AnimControlUpdater updater;
    fw::AnimSinglePoseSamper poseSampler;
    f32 playBackTime;
  };

  GfComPackAnim();
  void cleanup();
  void setup(const SetupInfo &info);
  void play(const char *name);
  void play(void *motion);
  void stop();
  bool isPlayEnd() const;
  void setSpeed(f32 speed);
  void changeLayer(u32 oldLayer, u32 newLayer) override;
  const mm::mtl::RTTI *getRTTI() const override;

  Mot mot;
  mm::mtl::FixedVector<arc::CArcData *, ARC_MAX> arcs;
  bool isLocalSpace;
};

static_assert(offsetof(GfComPackAnim::SetupInfo, name) == 0x48, "");
static_assert(offsetof(GfComPackAnim::SetupInfo, isLocalSpace) == 0x50, "");
static_assert(offsetof(GfComPackAnim::Mot, updater) == 0x10, "");
static_assert(offsetof(GfComPackAnim::Mot, poseSampler) == 0x30, "");
static_assert(offsetof(GfComPackAnim::Mot, playBackTime) == 0x68, "");
static_assert(offsetof(GfComPackAnim, mot) == 0x10, "");
static_assert(offsetof(GfComPackAnim, arcs) == 0x80, "");
static_assert(offsetof(GfComPackAnim, isLocalSpace) == 0xc8, "");

} // namespace gf
