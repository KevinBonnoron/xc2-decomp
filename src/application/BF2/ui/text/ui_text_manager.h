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
    u32 unknown00; // Inferred role: hash; original member name unknown.
    u32 unknown04; // Inferred role: handle; original member name unknown.
    u32 unknown08; // Inferred role: ref count; original member name unknown.
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

  mm::mtl::FixedVector<FileInfo, 256> unknown08; // Inferred role: files; original member name unknown.
  fw::PointerMap unknownc10;                     // Inferred role: file map; original member name unknown.
};

static_assert(sizeof(UITextManager::FileInfo) == 0x0c, "");
static_assert(offsetof(UITextManager, unknown08) == 0x08, "");
static_assert(offsetof(UITextManager, unknownc10) == 0xc10, "");
static_assert(sizeof(UITextManager) == 0xc48, "");

} // namespace ui
