#include "framework/message/message_manager.h"

#include "framework/message/message_object.h"

namespace fw {

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
