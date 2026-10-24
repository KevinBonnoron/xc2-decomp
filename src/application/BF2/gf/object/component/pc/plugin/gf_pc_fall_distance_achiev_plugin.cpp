#include "gf/object/component/pc/plugin/gf_pc_fall_distance_achiev_plugin.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/scom/gf_scom_achiev.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

enum {
  STATS_FALL_DISTANCE = 0x15,
};

constexpr f32 ACHIEV_FALL_DISTANCE_MIN = 10.0f;

FallDistanceAchievPlugin::FallDistanceAchievPlugin() : unknown10(nullptr), unknown18(0.0f) {}

FallDistanceAchievPlugin::~FallDistanceAchievPlugin() {}

bool FallDistanceAchievPlugin::setup(GfComBehaviorPc &behavior) {
  unknown10 = behavior.owner->getComponent<GfComPropertyPc>();
  return true;
}

void FallDistanceAchievPlugin::cleanup(GfComBehaviorPc &) {}

void FallDistanceAchievPlugin::onActivate() { unknown18 = unknown10->unknown160.y; }

void FallDistanceAchievPlugin::onDeactivate() {
  f32 distance = unknown18 - unknown10->unknown160.y;
  if (distance >= ACHIEV_FALL_DISTANCE_MIN) {
    SCOM_ACHIEV_INC::create(STATS_FALL_DISTANCE, distance, 0);
  }
}

void FallDistanceAchievPlugin::update(GfComBehaviorPc &, const fw::UpdateInfo &) {
  if (unknown10->unknown160.y > unknown18) {
    unknown18 = unknown10->unknown160.y;
  }
}

} // namespace pc
} // namespace gf
