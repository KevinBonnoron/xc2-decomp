#include "gf/object/component/pc/plugin/gf_pc_fall_damage_plugin.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

FallDamagePlugin::FallDamagePlugin() : unknown10(nullptr), unknown18(0.0f), unknown1c(false), unknown20(INVALID_HANDLE) {}

FallDamagePlugin::~FallDamagePlugin() {}

bool FallDamagePlugin::setup(GfComBehaviorPc &behavior) {
  unknown10 = behavior.owner->getComponent<GfComPropertyPc>();
  return true;
}

void FallDamagePlugin::cleanup(GfComBehaviorPc &) {}

void FallDamagePlugin::onActivate() {
  unknown18 = unknown10->unknown160.y;
  unknown20 = getAttachObj();
}

void FallDamagePlugin::update(GfComBehaviorPc &, const fw::UpdateInfo &) {
  if (unknown10->unknown160.y > unknown18) {
    unknown18 = unknown10->unknown160.y;
  }
  unknown20 = getAttachObj();
}

void FallDamagePlugin::procMsgPcFieldGetFallMaxHeight(fw::MessageObject *, MsgPcFieldGetFallMaxHeight &message) {
  bool isValid = unknown08;
  message.unknown0c = isValid;
  if (isValid) {
    message.unknown08 = unknown18;
  }
}

void FallDamagePlugin::procMsgPcFieldSetFallMaxHeight(fw::MessageObject *, MsgPcFieldSetFallMaxHeight &message) {
  if (unknown08) {
    unknown18 = message.unknown08;
  }
}

} // namespace pc
} // namespace gf
