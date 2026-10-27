#pragma once
#include <stddef.h>

#include "grlib/cglib_vtl_mem_pool.h"
#include "types.h"

namespace grlib {

class CGLibShader;

// Inferred role: shader file header; original type name unknown.
struct unknown001 {
  u32 unknown00; // Inferred role: magic; original member name unknown.
  u32 unknown04; // Inferred role: version; original member name unknown.
  u32 unknown08; // Inferred role: declaration num; original member name unknown.
  u32 unknown0c; // Inferred role: declaration table offset; original member name unknown.
  u32 unknown10; // Inferred role: shader num; original member name unknown.
  u8 _14[0x18 - 0x14];
  u32 unknown18; // Inferred role: shader mode; original member name unknown.
};

// Inferred role: shader declaration entry; original type name unknown.
struct unknown002 {
  u32 unknown00; // Inferred role: max index; original member name unknown.
  u32 unknown04; // Inferred role: index stride; original member name unknown.
  u32 unknown08; // Inferred role: name offset; original member name unknown.
};

static_assert(sizeof(unknown002) == 0xc, "");

class CGLibDecShader {
public:
  CGLibDecShader();
  ~CGLibDecShader();
  void release();
  static u32 calcWorkSize(const void *data, bool isCopy);
  static u32 calcTblSize(const void *data);
  void changeShaderSetMem(const void *data);
  void getDeclarationInfo(const char *&name, int &num, int index) const;
  u32 getDeclarationMax() const;
  u32 getShaderMode();
  u32 getDeclarationOfs(const char *name) const;
  void setDeclarationIdx(u32 offset, u32 index);

  const unknown001 *unknown00; // Inferred role: shader data; original member name unknown.
  CGLibVtlMemPool unknown08;   // Inferred role: mem pool; original member name unknown.
  CGLibShader *unknown38;      // Inferred role: shaders; original member name unknown.
  s32 unknown40;               // Inferred role: shader num; original member name unknown.
  u8 _44[0x48 - 0x44];
  void *unknown48; // Inferred role: allocated buffer; original member name unknown.
  void *unknown50; // Inferred role: allocated buffer; original member name unknown.
  u32 unknown58;   // Inferred role: shader idx; original member name unknown.
  u8 *unknown60;   // Inferred role: declaration idx table; original member name unknown.
};

static_assert(offsetof(CGLibDecShader, unknown08) == 0x08, "");
static_assert(offsetof(CGLibDecShader, unknown38) == 0x38, "");
static_assert(offsetof(CGLibDecShader, unknown40) == 0x40, "");
static_assert(offsetof(CGLibDecShader, unknown48) == 0x48, "");
static_assert(offsetof(CGLibDecShader, unknown60) == 0x60, "");
static_assert(offsetof(CGLibDecShader, unknown58) == 0x58, "");
static_assert(sizeof(CGLibDecShader) == 0x68, "");

} // namespace grlib
