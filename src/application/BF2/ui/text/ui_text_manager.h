#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {

class UITextManager : public mm::mtl::PtrSingleton<UITextManager> {
public:
  u32 registTextFile(u8 *data);
  void unregistTextFile(u32 handle);
  const char *getText(u32 handle, u32 id) const;
  u16 getStyle(u32 handle, u32 id) const;
  u8 *getTextFile(u32 handle) const;
};

} // namespace ui
