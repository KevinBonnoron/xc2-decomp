#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {

class UIStreamManager : public mm::mtl::PtrSingleton<UIStreamManager> {
public:
  struct Content : mm::mtl::IntrusiveListNodeBase {
    u32 unknown10; // Inferred role: stream hash; original member name unknown.
    u32 unknown14; // Inferred role: stream data; original member name unknown.
    u8 *unknown18; // Inferred role: bdat; original member name unknown.
  };

  u32 regist(u8 *bdat);
  void start(u32 streamId, u32 handle, u32 index);
  u32 getContentsNum(u32 streamId);

  u8 _08[0x10 - 0x08];
  mm::mtl::IntrusiveList<Content> unknown10; // Inferred role: contents; original member name unknown.
};

static_assert(offsetof(UIStreamManager::Content, unknown10) == 0x10, "");
static_assert(offsetof(UIStreamManager::Content, unknown18) == 0x18, "");
static_assert(offsetof(UIStreamManager, unknown10) == 0x10, "");

} // namespace ui
