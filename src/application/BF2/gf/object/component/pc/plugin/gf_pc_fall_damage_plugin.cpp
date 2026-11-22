#include "gf/object/component/pc/plugin/gf_pc_fall_damage_plugin.h"

#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

FallDamagePlugin::FallDamagePlugin() : m_comPropertyPc(nullptr), unknown18(0.0f), unknown1c(false), m_GF_OBJ_HANDLE(unknown020) {}

FallDamagePlugin::~FallDamagePlugin() {}

bool FallDamagePlugin::setup(GfComBehaviorPc &behavior) {
  m_comPropertyPc = behavior.unknown08->getComponent<GfComPropertyPc>();
  return true;
}

void FallDamagePlugin::cleanup(GfComBehaviorPc &) {}

void FallDamagePlugin::onActivate() {
  unknown18 = m_comPropertyPc->unknown160.unknown00.y;
  m_GF_OBJ_HANDLE = getAttachObj();
}

void FallDamagePlugin::update(GfComBehaviorPc &, const fw::UpdateInfo &) {
  if (m_comPropertyPc->unknown160.unknown00.y > unknown18) {
    unknown18 = m_comPropertyPc->unknown160.unknown00.y;
  }
  m_GF_OBJ_HANDLE = getAttachObj();
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
