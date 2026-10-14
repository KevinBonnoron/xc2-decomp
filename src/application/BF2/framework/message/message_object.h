#pragma once
#include "mm_mtl/rtti.h"
#include "types.h"

namespace fw {

struct Message {
  Message(u32 id, u32 size) : id(id), size(size) {}

  u32 id;
  u32 size;
};

class MessageObject {
public:
  MessageObject();
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~MessageObject();
  virtual bool recieveMessage(MessageObject *sender, Message &message);

  bool sendMessage(MessageObject *receiver, Message &message) { return receiver->recieveMessage(this, message); }

  u8 _08[0x18 - 0x08];
};

static_assert(sizeof(MessageObject) == 0x18, "");

} // namespace fw
