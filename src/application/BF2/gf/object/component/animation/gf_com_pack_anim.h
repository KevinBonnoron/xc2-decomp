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
    mm::mtl::FixedVector<void *, ARC_MAX> unknown00; // Inferred role: arcs; original member name unknown.
    const char *unknown48;                           // Inferred role: name; original member name unknown.
    bool unknown50;                                  // Inferred role: local space; original member name unknown.
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

    GfComModel *unknown00;              // Inferred role: model; original member name unknown.
    anm::Control *unknown08;            // Inferred role: control; original member name unknown.
    fw::AnimControlUpdater unknown10;   // Inferred role: updater; original member name unknown.
    fw::AnimSinglePoseSamper unknown30; // Inferred role: pose sampler; original member name unknown.
    f32 unknown68;                      // Inferred role: play back time; original member name unknown.
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

  Mot unknown10;                                            // Inferred role: mot; original member name unknown.
  mm::mtl::FixedVector<arc::CArcData *, ARC_MAX> unknown80; // Inferred role: arcs; original member name unknown.
  bool unknownc8;                                           // Inferred role: local space; original member name unknown.
};

static_assert(offsetof(GfComPackAnim::SetupInfo, unknown48) == 0x48, "");
static_assert(offsetof(GfComPackAnim::SetupInfo, unknown50) == 0x50, "");
static_assert(offsetof(GfComPackAnim::Mot, unknown10) == 0x10, "");
static_assert(offsetof(GfComPackAnim::Mot, unknown30) == 0x30, "");
static_assert(offsetof(GfComPackAnim::Mot, unknown68) == 0x68, "");
static_assert(offsetof(GfComPackAnim, unknown10) == 0x10, "");
static_assert(offsetof(GfComPackAnim, unknown80) == 0x80, "");
static_assert(offsetof(GfComPackAnim, unknownc8) == 0xc8, "");

} // namespace gf
