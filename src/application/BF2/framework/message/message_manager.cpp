#include "framework/message/message_manager.h"

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "framework/message/message_object.h"
#include "fw/fw_update_info.h"

namespace fw {

void MessageManager::Impl::destroy() {
  messages.clear();
  objectMap.destroy();
}

void MessageManager::Impl::update(const UpdateInfo &info) {
  for (mm::mtl::List<MessageInfo>::iterator it = messages.begin(); it != messages.end();) {
    MessageInfo &message = *it;
    message.delay -= info.deltaTime;
    if (message.delay <= 0.0f) {
      MessageObject *receiver = message.receiver.get();
      MessageObject *sender = message.sender.get();
      if (receiver != nullptr) {
        receiver->recieveMessage(sender, *message.holder->message);
      }

      it = messages.erase(it);
    } else {
      ++it;
    }
  }
}

void MessageManager::Impl::registObject(MessageObject *object) {
  object->selfHandle.id = objectMap.regist(object);
  object->selfHandle.map = &objectMap;
}

void MessageManager::Impl::removeObject(MessageObject *object) {
  HandlePtr<MessageObject> &handle = object->selfHandle;
  if (handle.id != 0 && handle.map != nullptr) {
    handle.map->remove(handle.id);
  }
}

u32 MessageManager::Impl::push(MessageObject *sender, MessageObject *receiver, Message *message, f32 delay) {
  MessageInfo info;
  // __LINE__ of the game: it is the line argument of the operator new.
#line 210
  info.holder = new (Framework::getAllocator(), 8, __FILE__, __LINE__) MessageHolder(message);
  if (++messageId > messageIdMax) {
    messageId = messageIdMin;
  } else if (messageId < messageIdMin) {
    messageId = messageIdMin;
  }

  u32 id = messageId;

  if (sender != nullptr) {
    info.sender = sender->selfHandle;
  }

  if (receiver != nullptr) {
    info.receiver = receiver->selfHandle;
  }

  info.delay = delay;
  info.id = id;
  messages.push_back(info);
  return id;
}

MessageManager::MessageManager(mm::mtl::IAllocator *allocator)
// __LINE__ of the game: it is the line argument of the operator new.
#line 248
    : impl(new (allocator, 8, __FILE__, __LINE__) Impl(allocator)) {
}

MessageManager::~MessageManager() {}

bool MessageManager::initialize() { return true; }

bool MessageManager::finalize() {
  impl.reset();
  return true;
}

void MessageManager::update(const UpdateInfo &info) {
  if (isFinalized()) {
    return;
  }

  impl->update(info);
}

void MessageManager::tail(const UpdateInfo &info) {
  if (isFinalized()) {
    return;
  }
}

void MessageManager::registObject(MessageObject *object) { impl->registObject(object); }

void MessageManager::removeObject(MessageObject *object) { impl->removeObject(object); }

void MessageManager::push(MessageObject *sender, MessageObject *receiver, Message *message, f32 delay) {
  impl->push(sender, receiver, message, delay);
}

const char *MessageManager::getName() const { return "MessageManager"; }

} // namespace fw
