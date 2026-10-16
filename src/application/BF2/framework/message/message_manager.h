#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "framework/message/message_object.h"
#include "framework/pointer_map.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/list.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

struct UpdateInfo;

class MessageManager : public ManagerObject, public mm::mtl::PtrSingleton<MessageManager> {
public:
  class Impl {
  public:
    static const u32 OBJECT_CAPACITY = 0x600;
    static const u32 MESSAGE_RESERVE = 0x800;
    static const u32 MESSAGE_ID_MIN = 1;
    static const u32 MESSAGE_ID_MAX = 0xffffffff;

    class MessageHolder : public mm::mtl::ReferenceObject {
    public:
      explicit MessageHolder(Message *message) : message(message) {}
      ~MessageHolder() {
        if (message != nullptr) {
          delete message;
          message = nullptr;
        }
      }

      Message *message;
    };

    struct MessageInfo {
      mm::mtl::IntrusivePtr<MessageHolder> holder;
      f32 delay;
      HandlePtr<MessageObject> sender;
      HandlePtr<MessageObject> receiver;
      u32 id;
    };

    explicit Impl(mm::mtl::IAllocator *allocator)
        : allocator(allocator), messageId(0), messageIdMin(MESSAGE_ID_MIN), messageIdMax(MESSAGE_ID_MAX), messages(allocator) {
      objectMap.reserve(allocator, OBJECT_CAPACITY);
      messages.reserve(MESSAGE_RESERVE);
    }

    ~Impl() { destroy(); }
    void destroy();
    void update(const UpdateInfo &info);
    void registObject(MessageObject *object);
    void removeObject(MessageObject *object);
    u32 push(MessageObject *sender, MessageObject *receiver, Message *message, f32 delay);
    void remove(u32 id);

    mm::mtl::IAllocator *allocator;
    PointerMap objectMap;
    u32 messageId;
    u32 messageIdMin;
    u32 messageIdMax;
    mm::mtl::List<MessageInfo> messages;
  };

  explicit MessageManager(mm::mtl::IAllocator *allocator);
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

static_assert(sizeof(MessageManager::Impl::MessageHolder) == 0x18, "");
static_assert(offsetof(MessageManager::Impl::MessageInfo, sender) == 0x10, "");
static_assert(offsetof(MessageManager::Impl::MessageInfo, id) == 0x30, "");
static_assert(sizeof(MessageManager::Impl::MessageInfo) == 0x38, "");
static_assert(offsetof(MessageManager::Impl, objectMap) == 0x08, "");
static_assert(offsetof(MessageManager::Impl, messageId) == 0x40, "");
static_assert(offsetof(MessageManager::Impl, messages) == 0x50, "");
static_assert(sizeof(MessageManager::Impl) == 0xc0, "");
static_assert(offsetof(MessageManager, impl) == 0x18, "");

} // namespace fw
