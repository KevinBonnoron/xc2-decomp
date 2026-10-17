#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include "ui/ui_group.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ui {

class UIGameListener;
class UIPadRead;
class UIUpdateCallback;
struct EventData;

class UIManager : public mm::mtl::PtrSingleton<UIManager> {
public:
  enum {
    GROUP_MAX = 8,
  };

  struct LayerInfo {
    u16 group;
    u16 layer;
  };

  UIManager(const UIPadRead *padRead, mtl::ALLOC_HANDLE handle);
  void terminate();
  u32 createLayer(u32 layer);
  bool isLayerCreated(u32 layer);
  u32 searchObject(const char *name, u16 group);
  void initializeLayer(u32 layer);
  void terminateLayer(u32 layer, bool isImmediate);
  void releaseLayer(u32 layer);
  bool preloadLayer(u32 layer);
  void terminateObject(const char *name, u8 group, bool isImmediate);
  void requestObjectEvent(u32 handle, const EventData &event, f32 delay);
  void requestGameEvent(u32 handle, const EventData &event);
  void setGameEventLisenter(UIGameListener *listener);
  void setUpdateCallback(UIUpdateCallback *callback);
  void registObjectTimer(u32 handle, u16 id, u64 time, bool repeat);
  void releaseObjectTimer(u32 handle);
  void setDisp(u16 group, bool disp);
  bool isLoading() const;
  void reloadText();
  u32 getLoadedResourceSize();
  bool isTerminated() const;

  UIGroup groups[GROUP_MAX];
  mm::mtl::FixedVector<LayerInfo, 32> layers;
  u8 _3d0[0x3d8 - 0x3d0];
  const UIPadRead *padRead;
  UIUpdateCallback *updateCallback;
};

static_assert(offsetof(UIManager, groups) == 0x08, "");
static_assert(offsetof(UIManager, layers) == 0x348, "");
static_assert(offsetof(UIManager, padRead) == 0x3d8, "");
static_assert(offsetof(UIManager, updateCallback) == 0x3e0, "");
static_assert(sizeof(UIManager) == 0x3e8, "");

} // namespace ui
