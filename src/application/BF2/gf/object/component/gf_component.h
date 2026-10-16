#pragma once
#include "framework/object/updatable_object.h"
#include "types.h"

namespace fw {
class MessageObject;
struct Message;
} // namespace fw
namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComponent : public fw::ComponentObject {
public:
  static mm::mtl::RTTI m_rtti;

  virtual u32 changeLayer(u32 oldLayer, u32 newLayer);
  virtual bool recieveMessage(fw::MessageObject *sender, fw::Message &message);
};

} // namespace gf
