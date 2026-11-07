#pragma once
#include <stddef.h>

#include "types.h"

namespace navi {

class NvmshResMemMan;
class NvmshResMemObj;

// Read entry of a loaded .nvmh file; callers index an array of these by 0x10 bytes.
struct _NvMhAllReadObj {
  u32 unknown00; // Inferred role: flags; bit 0 selects the first data block and bit 1 the second; original member name unknown.
  u32 unknown04; // Inferred role: file offset; original member name unknown.
  u32 unknown08; // Inferred role: size; original member name unknown.
  u32 unknown0c; // Inferred role: offset of the second data block; original member name unknown.
};

static_assert(offsetof(_NvMhAllReadObj, unknown04) == 0x04, "");
static_assert(offsetof(_NvMhAllReadObj, unknown08) == 0x08, "");
static_assert(offsetof(_NvMhAllReadObj, unknown0c) == 0x0c, "");
static_assert(sizeof(_NvMhAllReadObj) == 0x10, "");

// Prefix of the .nvmh resource image. NvmshResObj::createNavi reads these offsets from the image, not from the
// _NvMhAllReadObj entries; the original type name is unknown.
struct unknown001 {
  u8 _00[0x28];
  u32 unknown28; // Inferred role: header offset; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  u32 unknown30; // Inferred role: header offset; original member name unknown.
  u8 _34[0x40 - 0x34];
  u32 unknown40; // Inferred role: header offset; original member name unknown.
  u8 _44[0x48 - 0x44];
  u32 unknown48; // Inferred role: header offset; original member name unknown.
  u8 _4c[0x50 - 0x4c];
  u32 unknown50; // Inferred role: header offset; original member name unknown.
  u32 unknown54; // Inferred role: header offset; original member name unknown.
  u8 _58[0x6c - 0x58];
  u32 unknown6c; // Inferred role: header offset; original member name unknown.
  u32 unknown70; // Inferred role: unknown; original member name unknown.
  u32 unknown74; // Inferred role: header offset; original member name unknown.
};

static_assert(offsetof(unknown001, unknown28) == 0x28, "");
static_assert(offsetof(unknown001, unknown30) == 0x30, "");
static_assert(offsetof(unknown001, unknown40) == 0x40, "");
static_assert(offsetof(unknown001, unknown48) == 0x48, "");
static_assert(offsetof(unknown001, unknown50) == 0x50, "");
static_assert(offsetof(unknown001, unknown54) == 0x54, "");
static_assert(offsetof(unknown001, unknown6c) == 0x6c, "");
static_assert(offsetof(unknown001, unknown70) == 0x70, "");
static_assert(offsetof(unknown001, unknown74) == 0x74, "");
static_assert(sizeof(unknown001) == 0x78, "");

// Holds the pointers into one navigation mesh resource file.
class NvmshResObj {
public:
  NvmshResObj();
  ~NvmshResObj();
  void releaseNavi();
  void resetNavi();
  void createNavi(const u8 *data);

  u32 unknown00; // Inferred role: flags, bit 0 set once the resource is created; original member name unknown.
  u8 _04[4];
  const u8 *unknown08; // Inferred role: resource data start; original member name unknown.
  const u8 *unknown10; // Inferred role: world header; original member name unknown.
  const u8 *unknown18; // Inferred role: mesh table; original member name unknown.
  const u8 *unknown20; // Inferred role: polygon table; original member name unknown.
  const u8 *unknown28; // Inferred role: read from the header offset at 0x54; original member name unknown.
  const u8 *unknown30; // Inferred role: read from the header offset at 0x48; original member name unknown.
  const u8 *unknown38; // Inferred role: read from the header offset at 0x6c; original member name unknown.
  const u8 *unknown40; // Inferred role: read from the header offset at 0x74; original member name unknown.
  const u8 *unknown48; // Inferred role: read from the header offset at 0x40; original member name unknown.
  const u8 *unknown50; // Inferred role: read from the header offset at 0x50; original member name unknown.
};

static_assert(offsetof(NvmshResObj, unknown08) == 0x08, "");
static_assert(offsetof(NvmshResObj, unknown10) == 0x10, "");
static_assert(offsetof(NvmshResObj, unknown18) == 0x18, "");
static_assert(offsetof(NvmshResObj, unknown20) == 0x20, "");
static_assert(offsetof(NvmshResObj, unknown28) == 0x28, "");
static_assert(offsetof(NvmshResObj, unknown30) == 0x30, "");
static_assert(offsetof(NvmshResObj, unknown38) == 0x38, "");
static_assert(offsetof(NvmshResObj, unknown40) == 0x40, "");
static_assert(offsetof(NvmshResObj, unknown48) == 0x48, "");
static_assert(offsetof(NvmshResObj, unknown50) == 0x50, "");
static_assert(sizeof(NvmshResObj) == 0x58, "");

// Holds the state of one loaded navigation mesh resource: two embedded NvmshResObj blocks, the read entry and the
// allocated memory object. The constructor, createNavi, resetNavi and releaseNavi operate on both blocks.
class NvmshResData {
public:
  NvmshResData();
  ~NvmshResData();
  void createNavi();
  void resetNavi();
  void setReadData(const _NvMhAllReadObj *readData, int offset);
  void releaseCall();
  void update(NvmshResMemMan *memMan);
  void releaseNavi(NvmshResMemMan *memMan);

  u32 unknown00; // Inferred role: state flags; createNavi sets bit 0 and bit 4, releaseCall sets bit 2 and update
                 // clears bit 4; original member name unknown.
  s16 unknown04; // Inferred role: update counter; after a release request 4 updates release the resource, otherwise 16
                 // updates request it; original member name unknown.
  u8 _06[2];
  const _NvMhAllReadObj *m_readData; // Name from setReadData; original member name unknown.
  NvmshResObj unknown10;             // Inferred role: first data block; original member name unknown.
  NvmshResObj unknown68;             // Inferred role: second data block; original member name unknown.
  int unknownc0;                     // Inferred role: read data offset; original member name unknown.
  u8 _c4[4];
  NvmshResMemObj *unknownc8; // Inferred role: allocated memory object; original member name unknown.
};

static_assert(offsetof(NvmshResData, unknown04) == 0x04, "");
static_assert(offsetof(NvmshResData, m_readData) == 0x08, "");
static_assert(offsetof(NvmshResData, unknown10) == 0x10, "");
static_assert(offsetof(NvmshResData, unknown68) == 0x68, "");
static_assert(offsetof(NvmshResData, unknownc0) == 0xc0, "");
static_assert(offsetof(NvmshResData, unknownc8) == 0xc8, "");
static_assert(sizeof(NvmshResData) == 0xd0, "");

} // namespace navi
