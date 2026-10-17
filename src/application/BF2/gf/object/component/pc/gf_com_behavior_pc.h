#pragma once
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_mtl/rtti.h"

namespace gf {

class GfComBehaviorPc : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  GfComPropertyPc *getProperty() const { return mm::mtl::dynamicCast<GfComPropertyPc>(owner->components[GfComPropertyPc::COMPONENT_INDEX]); }
};

} // namespace gf
