#pragma once
#include <stddef.h>

#include "grlib/cglib_vtl_mem_pool.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace grlib {

class CGLibShader;

// Inferred role: shader file header; original type name unknown.
struct unknown001 {
  u32 unknown00; // Inferred role: magic; original member name unknown.
  u32 unknown04; // Inferred role: version; original member name unknown.
  u32 unknown08; // Inferred role: declaration num; original member name unknown.
  u32 unknown0c; // Inferred role: declaration table offset; original member name unknown.
  u32 unknown10; // Inferred role: shader num; original member name unknown.
  u32 unknown14; // Inferred role: shader data table offset; original member name unknown.
  u32 unknown18; // Inferred role: shader mode; original member name unknown.
  u32 unknown1c; // Inferred role: shader code table offset; original member name unknown.
  u8 _20[0x28 - 0x20];
  u32 unknown28; // Inferred role: control offset; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  u32 unknown30; // Inferred role: code offset; original member name unknown.
  u32 unknown34; // Inferred role: code size; original member name unknown.
};

static_assert(offsetof(unknown001, unknown14) == 0x14, "");
static_assert(offsetof(unknown001, unknown1c) == 0x1c, "");
static_assert(offsetof(unknown001, unknown28) == 0x28, "");
static_assert(offsetof(unknown001, unknown34) == 0x34, "");

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
  u32 createShader(mtl::ALLOC_HANDLE handle, const void *data, bool isTbl);
  void setupDefShader(const void *data, u8 *buffer, bool isTbl);
  u32 createShader(void *buffer, const void *data, bool isTbl);
  u32 createCopyShader(mtl::ALLOC_HANDLE handle, const void *data, bool isTbl);
  void setupCopyShader(const void *data, u8 *buffer, bool isTbl);
  u32 createCopyShader(void *buffer, const void *data, bool isTbl);
  u32 createMemPoolShader(void *buffer, const u8 *data, const u8 *control, CGLibVtlMemPool *pool, bool isTbl);
  void setupMemPoolShader(const u8 *data, const u8 *control, CGLibVtlMemPool *pool, u8 *buffer, bool isTbl);
  void setupHeadShader(const void *data, u8 *buffer, bool isTbl);
  void setupDataShader(bool isCopy);
  void setupDataMemPoolShader(const u8 *control, CGLibVtlMemPool *pool);
  void changeShaderSetMem(const void *data);
  void changeMemPoolSetMem(const u8 *data, const u8 *control, CGLibVtlMemPool *pool);
  void getDeclarationInfo(const char *&name, int &num, int index) const;
  u32 getDeclarationMax() const;
  u32 getShaderMode();
  u32 getDeclarationOfs(const char *name) const;
  void setDeclarationIdx(u32 offset, u32 index);

  // Inferred role: shader data table entry; original type name unknown.
  struct unknown003 {
    u32 unknown00; // Inferred role: shader data offset; original member name unknown.
    u8 _04[0x08 - 0x04];
  };

  // Inferred role: shader code table entry; original type name unknown.
  struct unknown004 {
    u32 unknown00; // Inferred role: code offset; original member name unknown.
    u32 unknown04; // Inferred role: control offset; original member name unknown.
  };

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
static_assert(sizeof(CGLibDecShader::unknown003) == 0x8, "");
static_assert(sizeof(CGLibDecShader::unknown004) == 0x8, "");

} // namespace grlib
