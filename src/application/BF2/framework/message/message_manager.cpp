#include "framework/message/message_manager.h"

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "framework/message/message_object.h"
#include "fw/fw_update_info.h"

namespace fw {

void MessageManager::Impl::destroy() {
  unknown50.clear();
  unknown08.destroy();
}

void MessageManager::Impl::update(const UpdateInfo &info) {
  for (mm::mtl::List<MessageInfo>::iterator it = unknown50.begin(); it != unknown50.end();) {
    MessageInfo &message = *it;
    message.unknown08 -= info.unknown04;
    if (message.unknown08 <= 0.0f) {
      MessageObject *receiver = message.unknown20.get();
      MessageObject *sender = message.unknown10.get();
      if (receiver != nullptr) {
        receiver->recieveMessage(sender, *message.unknown00->unknown10);
      }

      it = unknown50.erase(it);
    } else {
      ++it;
    }
  }
}

void MessageManager::Impl::registObject(MessageObject *object) {
  object->unknown08.id = unknown08.regist(object);
  object->unknown08.map = &unknown08;
}

void MessageManager::Impl::removeObject(MessageObject *object) {
  HandlePtr<MessageObject> &handle = object->unknown08;
  if (handle.id != 0 && handle.map != nullptr) {
    handle.map->remove(handle.id);
  }
}

u32 MessageManager::Impl::push(MessageObject *sender, MessageObject *receiver, Message *message, f32 delay) {
  MessageInfo info;
  // __LINE__ of the game: it is the line argument of the operator new.
#line 210
  info.unknown00 = new (Framework::getAllocator(), 8, __FILE__, __LINE__) MessageHolder(message);
  if (++unknown40 > unknown48) {
    unknown40 = unknown44;
  } else if (unknown40 < unknown44) {
    unknown40 = unknown44;
  }

  u32 id = unknown40;

  if (sender != nullptr) {
    info.unknown10 = sender->unknown08;
  }

  if (receiver != nullptr) {
    info.unknown20 = receiver->unknown08;
  }

  info.unknown08 = delay;
  info.unknown30 = id;
  unknown50.push_back(info);
  return id;
}

MessageManager::MessageManager(mm::mtl::IAllocator *allocator)
// __LINE__ of the game: it is the line argument of the operator new.
#line 248
    : unknown18(new (allocator, 8, __FILE__, __LINE__) Impl(allocator)) {
}

MessageManager::~MessageManager() {}

bool MessageManager::initialize() { return true; }

bool MessageManager::finalize() {
  unknown18.reset();
  return true;
}

void MessageManager::update(const UpdateInfo &info) {
  if (isFinalized()) {
    return;
  }

  unknown18->update(info);
}

void MessageManager::tail(const UpdateInfo &info) {
  if (isFinalized()) {
    return;
  }
}

void MessageManager::registObject(MessageObject *object) { unknown18->registObject(object); }

void MessageManager::removeObject(MessageObject *object) { unknown18->removeObject(object); }

void MessageManager::push(MessageObject *sender, MessageObject *receiver, Message *message, f32 delay) { unknown18->push(sender, receiver, message, delay); }

const char *MessageManager::getName() const { return "MessageManager"; }

} // namespace fw
