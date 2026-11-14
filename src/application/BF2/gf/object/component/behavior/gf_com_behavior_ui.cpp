#include "gf/object/component/behavior/gf_com_behavior_ui.h"

#include <string.h>

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/plugin/gf_eye_blink_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"

namespace gf {

GfComBehaviorUI::GfComBehaviorUI() {}

GfComBehaviorUI::~GfComBehaviorUI() {}

void GfComBehaviorUI::setup(const SetupInfo &info) {
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    comAsm->unknown70[0].unknown00 = "system";
    comAsm->unknown70[0].unknown08.bind<GfComBehavior>(this, &GfComBehavior::callbackAnim);
  }

  unknown10.beginSetup(*this, 4);
  unknown10.unknown001<EyeBlinkPlugin>(1, info.unknown00);
  unknown10.endSetup();

  EyeBlinkPlugin *plugin = unknown001<EyeBlinkPlugin>(1);
  if (plugin != nullptr) {
    plugin->setActivate(true);
  }
}

void GfComBehaviorUI::cleanup() { unknown10.cleanup(); }

void GfComBehaviorUI::update(const fw::UpdateInfo &info) {
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  EyeBlinkPlugin *plugin = unknown001<EyeBlinkPlugin>(1);
  if (comAsm != nullptr && plugin != nullptr) {
    const char *state = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
    bool isActive = true;
    if (state != nullptr) {
      if (strcmp(state, "S_hold_00") == 0 || strcmp(state, "S_hold_01") == 0) {
        isActive = false;
      }
    }
    plugin->setActivate(isActive);
  }

  unknown10.update(info);
}

const mm::mtl::RTTI *GfComBehaviorUI::getRTTI() const { return &m_rtti; }

} // namespace gf
