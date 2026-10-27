#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {

struct MLLANG_STRUCT;

struct LanguageInfoParam {
  const char *unknown00[12]; // Inferred role: text per language; original member name unknown.
  u32 unknown60;             // Inferred role: fallback language; original member name unknown.
};

static_assert(offsetof(LanguageInfoParam, unknown60) == 0x60, "");

class LanguageInfo : public mm::mtl::PtrSingleton<LanguageInfo> {
public:
  LanguageInfo();
  ~LanguageInfo();
  static void initialize(mtl::ALLOC_HANDLE handle);
  static const char *getText(MLLANG_STRUCT *text);

  u32 unknown08;                // Inferred role: entry generation; original member name unknown.
  u32 unknown0c;                // Inferred role: language index; original member name unknown.
  LanguageInfoParam *unknown10; // Inferred role: entries; original member name unknown.
  u32 unknown18;                // Inferred role: entry count; original member name unknown.
  u32 unknown1c;                // Inferred role: entry max; original member name unknown.
  mtl::ALLOC_HANDLE unknown20;  // Inferred role: memory; original member name unknown.
  void *unknown28;              // Inferred role: unused buffer; original member name unknown.
  u32 unknown30;                // Inferred role: unused value; original member name unknown.
};

static_assert(offsetof(LanguageInfo, unknown08) == 0x08, "");
static_assert(offsetof(LanguageInfo, unknown10) == 0x10, "");
static_assert(offsetof(LanguageInfo, unknown20) == 0x20, "");
static_assert(offsetof(LanguageInfo, unknown28) == 0x28, "");
static_assert(offsetof(LanguageInfo, unknown30) == 0x30, "");

} // namespace ml
