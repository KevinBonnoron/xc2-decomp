#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ui {

class UITextFile {
public:
  UITextFile(u8 *data);
  virtual ~UITextFile();
  static UITextFile *create(u8 *data);
  void reload();
  const char *getText(u32 id) const;
  u16 getStyle(u32 id) const;

  u8 *data;
  mm::mtl::FixStr<64> name;
};

static_assert(offsetof(UITextFile, data) == 0x08, "");
static_assert(offsetof(UITextFile, name) == 0x10, "");
static_assert(sizeof(UITextFile) == 0x58, "");

} // namespace ui
