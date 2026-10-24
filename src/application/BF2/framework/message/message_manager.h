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
      explicit MessageHolder(Message *message) : unknown10(message) {}
      ~MessageHolder() {
        if (unknown10 != nullptr) {
          delete unknown10;
          unknown10 = nullptr;
        }
      }

      Message *unknown10; // Inferred role: message; original member name unknown.
    };

    struct MessageInfo {
      mm::mtl::IntrusivePtr<MessageHolder> unknown00; // Inferred role: holder; original member name unknown.
      f32 unknown08;                                  // Inferred role: delay; original member name unknown.
      HandlePtr<MessageObject> unknown10;             // Inferred role: sender; original member name unknown.
      HandlePtr<MessageObject> unknown20;             // Inferred role: receiver; original member name unknown.
      u32 unknown30;                                  // Inferred role: id; original member name unknown.
    };

    explicit Impl(mm::mtl::IAllocator *allocator) : unknown00(allocator), unknown40(0), unknown44(MESSAGE_ID_MIN), unknown48(MESSAGE_ID_MAX), unknown50(allocator) {
      unknown08.reserve(allocator, OBJECT_CAPACITY);
      unknown50.reserve(MESSAGE_RESERVE);
    }

    ~Impl() { destroy(); }
    void destroy();
    void update(const UpdateInfo &info);
    void registObject(MessageObject *object);
    void removeObject(MessageObject *object);
    u32 push(MessageObject *sender, MessageObject *receiver, Message *message, f32 delay);
    void remove(u32 id);

    mm::mtl::IAllocator *unknown00;       // Inferred role: allocator; original member name unknown.
    PointerMap unknown08;                 // Inferred role: object map; original member name unknown.
    u32 unknown40;                        // Inferred role: message id; original member name unknown.
    u32 unknown44;                        // Inferred role: message id min; original member name unknown.
    u32 unknown48;                        // Inferred role: message id max; original member name unknown.
    mm::mtl::List<MessageInfo> unknown50; // Inferred role: messages; original member name unknown.
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

  mm::mtl::UniquePtr<Impl> unknown18; // Inferred role: impl; original member name unknown.
};

static_assert(sizeof(MessageManager::Impl::MessageHolder) == 0x18, "");
static_assert(offsetof(MessageManager::Impl::MessageInfo, unknown10) == 0x10, "");
static_assert(offsetof(MessageManager::Impl::MessageInfo, unknown30) == 0x30, "");
static_assert(sizeof(MessageManager::Impl::MessageInfo) == 0x38, "");
static_assert(offsetof(MessageManager::Impl, unknown08) == 0x08, "");
static_assert(offsetof(MessageManager::Impl, unknown40) == 0x40, "");
static_assert(offsetof(MessageManager::Impl, unknown50) == 0x50, "");
static_assert(sizeof(MessageManager::Impl) == 0xc0, "");
static_assert(offsetof(MessageManager, unknown18) == 0x18, "");

} // namespace fw
