#pragma once
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_mtl/rtti.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace gf {

struct MsgDebugActivateComponentWindow;

class GfComBehaviorPc : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void setEnableAgentField(bool isEnable);
  void setEnableAgentBattle(bool isEnable);

  GfComPropertyPc *getProperty() const { return mm::mtl::dynamicCast<GfComPropertyPc>(unknown08->unknown38[GfComPropertyPc::COMPONENT_INDEX]); }
};

} // namespace gf
