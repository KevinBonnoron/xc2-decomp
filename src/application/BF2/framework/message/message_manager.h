#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "framework/pointer_map.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace fw {

class MessageObject;
struct Message;
struct UpdateInfo;

class MessageManager : public ManagerObject, public mm::mtl::PtrSingleton<MessageManager> {
public:
  class Impl {
  public:
    ~Impl();
    void update(const UpdateInfo &info);
    void registObject(MessageObject *object);
    void removeObject(MessageObject *object);
    void push(MessageObject *sender, MessageObject *receiver, Message *message, f32 delay);

    u8 _00[0x08 - 0x00];
    PointerMap objectMap;
  };

  ~MessageManager();
  bool initialize() override;
  bool finalize() override;
  const char *getName() const override;
  virtual void update(const UpdateInfo &info);
  virtual void tail(const UpdateInfo &info);
  void registObject(MessageObject *object);
  void removeObject(MessageObject *object);
  void push(MessageObject *sender, MessageObject *receiver, Message *message, f32 delay);

  mm::mtl::UniquePtr<Impl> impl;
};

static_assert(offsetof(MessageManager::Impl, objectMap) == 0x08, "");
static_assert(offsetof(MessageManager, impl) == 0x18, "");

} // namespace fw
