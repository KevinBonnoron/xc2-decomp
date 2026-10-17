#pragma once
#include <stddef.h>

#include "framework/pointer_map.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {

class UITextManager : public mm::mtl::PtrSingleton<UITextManager> {
public:
  struct FileInfo {
    u32 hash;
    u32 handle;
    u32 refCount;
  };

  UITextManager();
  virtual ~UITextManager();
  u32 registTextFile(u8 *data);
  void unregistTextFile(u32 handle);
  void reloadAll();
  void reload(u32 handle);
  const char *getText(u32 handle, u32 id) const;
  u16 getStyle(u32 handle, u32 id) const;
  u8 *getTextFile(u32 handle) const;

  mm::mtl::FixedVector<FileInfo, 256> files;
  fw::PointerMap fileMap;
};

static_assert(sizeof(UITextManager::FileInfo) == 0x0c, "");
static_assert(offsetof(UITextManager, files) == 0x08, "");
static_assert(offsetof(UITextManager, fileMap) == 0xc10, "");
static_assert(sizeof(UITextManager) == 0xc48, "");

} // namespace ui
