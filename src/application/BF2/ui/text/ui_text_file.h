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

  u8 *unknown08;                 // Inferred role: data; original member name unknown.
  mm::mtl::FixStr<64> unknown10; // Inferred role: name; original member name unknown.
};

static_assert(offsetof(UITextFile, unknown08) == 0x08, "");
static_assert(offsetof(UITextFile, unknown10) == 0x10, "");
static_assert(sizeof(UITextFile) == 0x58, "");

} // namespace ui
