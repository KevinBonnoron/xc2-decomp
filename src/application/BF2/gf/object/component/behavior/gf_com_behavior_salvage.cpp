#include "gf/object/component/behavior/gf_com_behavior_salvage.h"

#include <string.h>

#include "anm/anm_asm_listener.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/plugin/gf_foot_step_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"

namespace gf {

GfComBehaviorSalvage::GfComBehaviorSalvage() {}

GfComBehaviorSalvage::~GfComBehaviorSalvage() {}

void GfComBehaviorSalvage::setup() {
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    unknown014(comAsm);
  }

  m_pluginManager.beginSetup(*this, 4);
  m_pluginManager.unknown001<FootStepPlugin>(0, true);
  m_pluginManager.endSetup();

  FootStepPlugin *plugin = unknown001<FootStepPlugin>(0);
  if (plugin != nullptr) {
    plugin->setActivate(true);
  }
}

void GfComBehaviorSalvage::cleanup() { m_pluginManager.cleanup(); }

void GfComBehaviorSalvage::update(const fw::UpdateInfo &info) { m_pluginManager.update(info); }

void GfComBehaviorSalvage::procAnimCallback(GfComAsm *comAsm, const CallBackCache &cache) {
  if (!unknown98.isValid()) {
    return;
  }

  const char *name = cache.unknown08->unknown00;
  if (strcmp(name, "salvageStep") == 0) {
    unknown98();
  } else if (strcmp(name, "vibration") == 0) {
    unknown98();
  }
}

const mm::mtl::RTTI *GfComBehaviorSalvage::getRTTI() const { return &m_rtti; }

} // namespace gf
