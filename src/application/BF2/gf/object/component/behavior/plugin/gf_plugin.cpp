#include "gf/object/component/behavior/plugin/gf_plugin.h"

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
