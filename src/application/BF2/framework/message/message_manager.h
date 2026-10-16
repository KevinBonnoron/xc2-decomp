#pragma once
#include "framework/manager_object.h"
#include "mm_mtl/singleton.h"

namespace fw {

class MessageObject;

class MessageManager : public ManagerObject, public mm::mtl::PtrSingleton<MessageManager> {
public:
  void registObject(MessageObject *object);
  void removeObject(MessageObject *object);
};

} // namespace fw
