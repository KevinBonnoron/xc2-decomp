#pragma once
#include <stddef.h>

#include "framework/pointer_map.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {

struct Message {
  Message(u32 id, u32 componentMask) : id(id), componentMask(componentMask) {}

  u32 id;
  u32 componentMask;
};

class MessageObject {
public:
  static mm::mtl::RTTI m_rtti;

  MessageObject();
  virtual const mm::mtl::RTTI *getRTTI() const { return &m_rtti; }
  virtual ~MessageObject();
  virtual bool recieveMessage(MessageObject *sender, Message &message) { return false; }

  bool sendMessage(MessageObject *receiver, Message &message) { return receiver->recieveMessage(this, message); }

  HandlePtr<MessageObject> selfHandle;
};

static_assert(offsetof(MessageObject, selfHandle) == 0x08, "");
static_assert(sizeof(MessageObject) == 0x18, "");

} // namespace fw
