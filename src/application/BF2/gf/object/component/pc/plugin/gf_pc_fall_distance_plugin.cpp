#include "gf/object/component/pc/plugin/gf_pc_fall_distance_plugin.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

FallDistancePlugin::FallDistancePlugin() : property(nullptr), maxHeight(0.0f) {}

FallDistancePlugin::~FallDistancePlugin() {}

bool FallDistancePlugin::setup(GfComBehaviorPc &behavior) {
  property = behavior.owner->getComponent<GfComPropertyPc>();
  return true;
}

void FallDistancePlugin::cleanup(GfComBehaviorPc &) {}

f32 FallDistancePlugin::calcDistance(const mm::Vec3 &position) const {
  if (isActive) {
    return maxHeight - position.y;
  }
  return 0.0f;
}

void FallDistancePlugin::onActivate() { maxHeight = property->position.y; }

void FallDistancePlugin::onDeactivate() {}

void FallDistancePlugin::update(GfComBehaviorPc &, const fw::UpdateInfo &) {
  if (property->position.y > maxHeight) {
    maxHeight = property->position.y;
  }
}

} // namespace pc
} // namespace gf
