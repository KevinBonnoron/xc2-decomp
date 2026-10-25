#include "gf/object/component/behavior/plugin/gf_plugin.h"

#include "gf/gf_allocator.h"
#include "gf/object/component/behavior/plugin/gf_foot_step_plugin.h"
#include "gf/object/component/behavior/plugin/gf_lip_sync_plugin.h"

namespace gf {

Plugin::Plugin() : unknown08(false) {}

Plugin::~Plugin() {}

void Plugin::setActivate(bool isActive) {
  if (this->unknown08 == isActive) {
    return;
  }

  this->unknown08 = isActive;
  if (isActive) {
    onActivate();
  } else {
    onDeactivate();
  }
}

const mm::mtl::RTTI *Plugin::getRTTI() const { return &m_rtti; }

void Plugin::onActivate() {}

void Plugin::onDeactivate() {}

} // namespace gf

namespace gf {

// __LINE__ must be 23 as in the original header: it is the line argument of operator new.
#line 23 "gf/object/component/behavior/plugin/gf_lip_sync_plugin.h"
LipSyncPlugin *LipSyncPlugin::create() { return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LipSyncPlugin(); }

// __LINE__ must be 26 as in the original header: it is the line argument of operator new.
#line 26 "gf/object/component/behavior/plugin/gf_foot_step_plugin.h"
FootStepPlugin *FootStepPlugin::create() { return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) FootStepPlugin(); }

} // namespace gf
