#pragma once
#include <stddef.h>

#include "nvn/nvn.h"
#include "types.h"

namespace grlib {

// Inferred role: shader block info; original type name unknown.
struct unknown028 {
  u32 unknown00; // Inferred role: name ofs; original member name unknown.
  u16 unknown04; // Inferred role: value num; original member name unknown.
  u16 unknown06; // Inferred role: value idx; original member name unknown.
  u32 unknown08; // Inferred role: stage bind ofs; original member name unknown.
  u8 unknown0c;  // Inferred role: index; original member name unknown.
  u8 unknown0d;  // Inferred role: stage bind num; original member name unknown.
  u16 unknown0e; // Inferred role: size; original member name unknown.
};

static_assert(sizeof(unknown028) == 0x10, "");

// Inferred role: shader info; original type name unknown.
struct unknown029 {
  u8 _00[0x20 - 0x00];
  s16 unknown20; // Inferred role: uniform block num; original member name unknown.
  u16 unknown22; // Inferred role: uniform block max; original member name unknown.
  u32 unknown24; // Inferred role: uniform block ofs; original member name unknown.
  u32 unknown28; // Inferred role: uniform block idx ofs; original member name unknown.
  s16 unknown2c; // Inferred role: storage buffer num; original member name unknown.
  u16 unknown2e; // Inferred role: storage buffer max; original member name unknown.
  u32 unknown30; // Inferred role: storage buffer ofs; original member name unknown.
  u32 unknown34; // Inferred role: storage buffer idx ofs; original member name unknown.
  s16 unknown38; // Inferred role: texture num; original member name unknown.
  u16 unknown3a; // Inferred role: texture max; original member name unknown.
  u32 unknown3c; // Inferred role: texture ofs; original member name unknown.
  u32 unknown40; // Inferred role: texture idx ofs; original member name unknown.
  s16 unknown44; // Inferred role: image num; original member name unknown.
  u16 unknown46; // Inferred role: image max; original member name unknown.
  u32 unknown48; // Inferred role: image ofs; original member name unknown.
  u32 unknown4c; // Inferred role: image idx ofs; original member name unknown.
  u8 _50[0x5c - 0x50];
  u32 unknown5c; // Inferred role: block value ofs; original member name unknown.
};

static_assert(offsetof(unknown029, unknown20) == 0x20, "");
static_assert(offsetof(unknown029, unknown34) == 0x34, "");
static_assert(offsetof(unknown029, unknown38) == 0x38, "");
static_assert(offsetof(unknown029, unknown4c) == 0x4c, "");
static_assert(offsetof(unknown029, unknown5c) == 0x5c, "");

class CGLibShader_plf {
public:
  void setUniformBlock(u32 index, NVNcommandBuffer *cmdBuf, u64 address, u32 size);
  void setStorageBuffer(u32 index, NVNcommandBuffer *cmdBuf, u64 address, u32 size);
  void setTextureHandle(u32 index, NVNcommandBuffer *cmdBuf, u64 handle);
  void setImageHandle(u32 index, NVNcommandBuffer *cmdBuf, u64 handle);

  // Inferred role: shader stage binding; original type name unknown.
  struct unknown001 {
    u8 unknown00; // Inferred role: stage; original member name unknown.
    u8 unknown01; // Inferred role: binding index; original member name unknown.
  };

  // Inferred role: texture or image slot; original type name unknown.
  struct unknown002 {
    u32 unknown00; // Inferred role: name ofs; original member name unknown.
    u32 unknown04; // Inferred role: stage bind ofs; original member name unknown.
    u8 unknown08;  // Inferred role: location; original member name unknown.
    u8 unknown09;  // Inferred role: stage bind num; original member name unknown.
  };

  const u8 *m_data;
  const unknown029 *unknown08; // Inferred role: info; original member name unknown.
};

static_assert(offsetof(CGLibShader_plf, unknown08) == 0x08, "");

class CGLibShader : public CGLibShader_plf {
public:
  CGLibShader();
  ~CGLibShader();
  void changeShaderSetMem(const void *data);
  void releaseShader();
  int getTextureLocation(const char *name) const;
  int getImageLocation(const char *name) const;
  int getUniformBlockOfs(const char *name) const;
  u16 getUniformBlockSize(u32 index) const;
  u32 getUniformBlockValOfs(u32 index, const char *name) const;
  int getStorageBufferOfs(const char *name) const;
  u16 getStorageBufferSize(u32 index) const;
  u32 getStorageBufferValOfs(u32 index, const char *name) const;

  // Inferred role: block value slot; original type name unknown.
  struct unknown003 {
    u32 unknown00; // Inferred role: name ofs; original member name unknown.
    u32 unknown04; // Inferred role: value ofs; original member name unknown.
  };

  u32 unknown10;        // Inferred role: state flags; original member name unknown.
  u32 unknown14;        // Inferred role: shader stage mask; original member name unknown.
  NVNprogram unknown18; // Inferred role: program; original member name unknown.
};

static_assert(offsetof(CGLibShader, unknown10) == 0x10, "");
static_assert(offsetof(CGLibShader, unknown14) == 0x14, "");
static_assert(offsetof(CGLibShader, unknown18) == 0x18, "");
static_assert(sizeof(CGLibShader) == 0xd8, "");
static_assert(sizeof(CGLibShader_plf::unknown001) == 0x2, "");
static_assert(sizeof(CGLibShader_plf::unknown002) == 0xc, "");
static_assert(sizeof(CGLibShader::unknown003) == 0x8, "");

class CGLibSetupShader {
public:
  static void releaseShader(CGLibShader *shader);
};

} // namespace grlib
