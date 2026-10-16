#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ui {

class UIPadRead;
struct EventData;

class UIManager : public mm::mtl::PtrSingleton<UIManager> {
public:
  UIManager(const UIPadRead *padRead, mtl::ALLOC_HANDLE handle);

  void requestObjectEvent(u32 handle, const EventData &event, f32 delay);
  void requestGameEvent(u32 handle, const EventData &event);
  void registObjectTimer(u32 handle, u16 id, u64 time, bool repeat);
  void releaseObjectTimer(u32 handle);
  u32 createLayer(u32 layer);
  void releaseLayer(u32 layer);

  u8 _08[0x3d8 - 0x08];
  const UIPadRead *padRead;
};

static_assert(offsetof(UIManager, padRead) == 0x3d8, "");

} // namespace ui
