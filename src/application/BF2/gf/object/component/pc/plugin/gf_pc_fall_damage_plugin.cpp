#include "gf/object/component/pc/plugin/gf_pc_fall_damage_plugin.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

FallDamagePlugin::FallDamagePlugin() : property(nullptr), maxHeight(0.0f), isDamageDisabled(false), attachObj(INVALID_HANDLE) {}

FallDamagePlugin::~FallDamagePlugin() {}

bool FallDamagePlugin::setup(GfComBehaviorPc &behavior) {
  property = behavior.owner->getComponent<GfComPropertyPc>();
  return true;
}

void FallDamagePlugin::cleanup(GfComBehaviorPc &) {}

void FallDamagePlugin::onActivate() {
  maxHeight = property->position.y;
  attachObj = getAttachObj();
}

void FallDamagePlugin::update(GfComBehaviorPc &, const fw::UpdateInfo &) {
  if (property->position.y > maxHeight) {
    maxHeight = property->position.y;
  }
  attachObj = getAttachObj();
}

void FallDamagePlugin::procMsgPcFieldGetFallMaxHeight(fw::MessageObject *, MsgPcFieldGetFallMaxHeight &message) {
  bool isValid = isActive;
  message.isValid = isValid;
  if (isValid) {
    message.maxHeight = maxHeight;
  }
}

void FallDamagePlugin::procMsgPcFieldSetFallMaxHeight(fw::MessageObject *, MsgPcFieldSetFallMaxHeight &message) {
  if (isActive) {
    maxHeight = message.maxHeight;
  }
}

} // namespace pc
} // namespace gf
