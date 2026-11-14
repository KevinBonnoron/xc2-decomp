#include "gf/object/component/pc/plugin/gf_pc_fall_distance_achiev_plugin.h"

#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/scom/gf_scom_achiev.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

enum {
  STATS_UNKNOWN_21 = 0x15, // Inferred role: stats fall distance; original name unknown.
};

constexpr f32 unknown017 = 10.0f; // Inferred role: achiev fall distance min; original name unknown.

FallDistanceAchievPlugin::FallDistanceAchievPlugin() : unknown10(nullptr), unknown18(0.0f) {}

FallDistanceAchievPlugin::~FallDistanceAchievPlugin() {}

bool FallDistanceAchievPlugin::setup(GfComBehaviorPc &behavior) {
  unknown10 = behavior.unknown08->getComponent<GfComPropertyPc>();
  return true;
}

void FallDistanceAchievPlugin::cleanup(GfComBehaviorPc &) {}

void FallDistanceAchievPlugin::onActivate() { unknown18 = unknown10->unknown160.unknown00.y; }

void FallDistanceAchievPlugin::onDeactivate() {
  f32 distance = unknown18 - unknown10->unknown160.unknown00.y;
  if (distance >= unknown017) {
    SCOM_ACHIEV_INC::create(STATS_UNKNOWN_21, distance, 0);
  }
}

void FallDistanceAchievPlugin::update(GfComBehaviorPc &, const fw::UpdateInfo &) {
  if (unknown10->unknown160.unknown00.y > unknown18) {
    unknown18 = unknown10->unknown160.unknown00.y;
  }
}

} // namespace pc
} // namespace gf
