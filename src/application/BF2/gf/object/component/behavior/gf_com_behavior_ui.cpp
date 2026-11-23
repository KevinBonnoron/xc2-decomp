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
    unknown014(comAsm);
  }

  m_pluginManager.beginSetup(*this, 4);
  m_pluginManager.unknown001<EyeBlinkPlugin>(1, info.unknown00);
  m_pluginManager.endSetup();

  EyeBlinkPlugin *plugin = unknown001<EyeBlinkPlugin>(1);
  if (plugin != nullptr) {
    plugin->setActivate(true);
  }
}

void GfComBehaviorUI::cleanup() { m_pluginManager.cleanup(); }

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

  m_pluginManager.update(info);
}

const mm::mtl::RTTI *GfComBehaviorUI::getRTTI() const { return &m_rtti; }

} // namespace gf
