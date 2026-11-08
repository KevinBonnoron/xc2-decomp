#pragma once
#include <stddef.h>

#include "mm_mtl/queue.h"
#include "mm_mtl/singleton.h"
#include "types.h"

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

} // namespace gf
