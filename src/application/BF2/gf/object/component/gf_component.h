#pragma once
#include "framework/message/message_object.h"
#include "framework/object/component_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

enum {
  MSG_UNKNOWN_16777219 = 0x1000003, // Inferred role: msg debug activate component window; original name unknown.
};

struct MsgDebugActivateComponentWindow : fw::Message {};

class GfComponent : public fw::ComponentObject {
public:
  static mm::mtl::RTTI m_rtti;

  virtual void changeLayer(u32 oldLayer, u32 newLayer) = 0;
  virtual bool recieveMessage(fw::MessageObject *sender, fw::Message &message) { return false; }
};

} // namespace gf
