#pragma once
#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "types.h"

namespace gf {

class GfComponent : public fw::ComponentObject {
public:
  static mm::mtl::RTTI m_rtti;

  virtual u32 changeLayer(u32 oldLayer, u32 newLayer);
  virtual bool recieveMessage(fw::MessageObject *sender, fw::Message &message);
};

} // namespace gf
