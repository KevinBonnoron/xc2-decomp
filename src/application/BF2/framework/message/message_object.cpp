#include "framework/message/message_object.h"

#include "framework/message/message_manager.h"

namespace fw {

MessageObject::MessageObject() { MessageManager::get()->registObject(this); }

MessageObject::~MessageObject() { MessageManager::get()->removeObject(this); }

} // namespace fw
