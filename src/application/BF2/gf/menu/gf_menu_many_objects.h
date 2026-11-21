#pragma once
#include <stddef.h>

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h" // IWYU pragma: keep
#include "mm_mtl/queue.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfMenuManyObjects : public mm::mtl::PtrSingleton<GfMenuManyObjects> {
public:
  // Inferred role: kind of pooled object, the index of its queue; original enum and enumerator names unknown.
  enum unknown001 {
    unknown001_0 = 0,
    unknown001_1 = 1,
    unknown001_2 = 2,
    unknown001_3 = 3,
    unknown001_4 = 4,
    unknown001_5 = 5,
    unknown001_6 = 6,
    unknown001_7 = 7,
  };

  // Base of the objects queued by the pooled menu objects (ExpGetInfo, PopupInfo...); the game gives it a vtable and a dispose virtual.
  class InfoType {
  public:
    // GfMenuObjDamageBuff::open and openUniteCombo (0x7100443854, 0x7100443bec) and GfMenuObjDropItem::open (0x7100446c10) store the handle before
    // the vtable pointer of their queued record: the base constructor sets the handle after its own vtable pointer, which the derived constructor
    // then overwrites (the dead first store disappears).
    // The default constructor is the one of the pop destination (Queue::unknown002): the game constructs it before the pop's assertions, and does not
    // initialise the handle (initialising it adds a store the game does not have; the pop assigns the whole record before any read).
    InfoType() {}
    InfoType(u32 handle) : unknown08(handle) {}
    virtual void dispose() {}

    u32 unknown08; // Inferred role: handle of the queued UI object, compared by remove; original member name unknown.
  };

  GfMenuManyObjects(const GfSetupParam &param);
  ~GfMenuManyObjects();
  static void build(const GfSetupParam &param);
  static void destroy();
  void initialize(const GfSetupParam &param);
  void finalize();
  static bool isInitialized();
  void postUpdate(const fw::UpdateInfo &info);
  // Inferred role: creates the queue of a pooled object kind; the game inlines it; original name unknown.
  template <typename T> static void unknown002(u32 type, size_t capacity);
  // Inferred role: appends a record to the queue of a pooled object kind, closing and disposing the oldest one first when the queue is full; the game inlines it
  // in four functions (GfMenuObjPopup::open, GfMenuObjDropItem::open, GfMenuObjDamageValue::open, GfMenuObjChainIcon::open); original name unknown.
  template <typename T> static void unknown003(u32 type, T info, void (*callback)(u32));
  template <typename T> static void remove(u32 type, u32 handle);
  template <typename T> static void destroy(u32 type);
  template <typename T> static void closeAll(u32 type, void (*callback)(u32));

  bool unknown08;     // Inferred role: initialized; original member name unknown.
  void *unknown10[8]; // Inferred role: queues of the pooled objects, indexed by type (0 to 7); original member name unknown.
  bool unknown50[8];  // Inferred role: per type flag, cleared with the queues by initialize (the popup continue sequence clears the one of type 7); original member name unknown.
};

static_assert(offsetof(GfMenuManyObjects, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuManyObjects, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuManyObjects, unknown50) == 0x50, "");
static_assert(sizeof(GfMenuManyObjects) == 0x58, "");

template <typename T> void GfMenuManyObjects::remove(u32 type, u32 handle) {
  if (type < 8) {
    mm::mtl::Queue<T> *queue = static_cast<mm::mtl::Queue<T> *>(get()->unknown10[type]);
    if (queue != nullptr) {
      for (typename mm::mtl::Queue<T>::iterator it = queue->begin(); it != queue->end(); ++it) {
        T &info = *it;
        if (info.unknown08 == handle) {
          info.dispose();
          it = queue->erase(it);
          break;
        }
      }
    }
  }
}

template <typename T> void GfMenuManyObjects::destroy(u32 type) {
  if (type < 8) {
    void *&slot = get()->unknown10[type];
    mm::mtl::Queue<T> *queue = static_cast<mm::mtl::Queue<T> *>(slot);
    if (queue != nullptr) {
      closeAll<T>(type, nullptr);
      delete queue;
      slot = nullptr;
    }
  }
}

template <typename T> void GfMenuManyObjects::closeAll(u32 type, void (*callback)(u32)) {
  if (type < 8) {
    mm::mtl::Queue<T> *queue = static_cast<mm::mtl::Queue<T> *>(get()->unknown10[type]);
    if (queue != nullptr) {
      for (typename mm::mtl::Queue<T>::iterator it = queue->begin(); it != queue->end();) {
        T &info = *it;
        if (callback != nullptr) {
          callback(info.unknown08);
        }
        info.dispose();
        it = queue->erase(it);
      }
    }
  }
}

template <typename T> void GfMenuManyObjects::unknown002(u32 type, size_t capacity) {
  if (type < 8) {
    void *&slot = get()->unknown10[type];
    if (slot == nullptr) {
      mm::mtl::IAllocator *allocator = fw::Allocator::getProcAllocator();
      if (allocator != nullptr) {
// __LINE__ must be 105 as in the original header: it is the line argument of operator new.
#line 105
        mm::mtl::Queue<T> *queue = new (allocator, 16, __FILE__, __LINE__) mm::mtl::Queue<T>(allocator);
        if (queue != nullptr) {
          queue->reserve(capacity);
          slot = queue;
        }
      }
    }
  }
}

// The record is taken by value, as GfMenuObjPopup::open (0x71004b3434), GfMenuObjDropItem::open (0x7100446c10), GfMenuObjDamageValue::open (0x7100445578) and
// GfMenuObjChainIcon::open (0x71004282d8) need: the same eviction (one close call, one virtual dispose call, the !empty() assertion at line 769) is in the four of
// them. Written inline in Popup::open it gives a different frame (the oldest record then lies below the queued copy), and a const reference parameter stores the
// copy differently. The oldest record is a local of the helper, whose stack slot lies above the argument copy, and the virtual dispose call reloads the vtable
// pointer that the default constructor stored before the pop's assertions.
template <typename T> void GfMenuManyObjects::unknown003(u32 type, T info, void (*callback)(u32)) {
  if (type < 8) {
    mm::mtl::Queue<T> *queue = static_cast<mm::mtl::Queue<T> *>(get()->unknown10[type]);
    if (queue != nullptr) {
      if (queue->full()) {
        T oldest;
        queue->unknown002(oldest);
        callback(oldest.unknown08);
        oldest.dispose();
      }
      queue->push_back(info);
    }
  }
}

} // namespace gf
