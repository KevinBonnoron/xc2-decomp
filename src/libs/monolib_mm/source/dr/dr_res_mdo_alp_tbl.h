#pragma once
#include <stddef.h>

#include "grlib/cglib_vtx_instans.h"
#include "types.h"

namespace ml {
class DrResMdoLodObj;
class DrResMdoMeshObj;

class DrResMdoAlpTbl : public grlib::CGLibVtxInstans {
public:
  // Inferred role: model resource header holding the offset of the alpha table; original type name unknown.
  struct unknown001 {
    u8 _00[0x02];
    u8 unknown02; // Inferred role: flags, bit 2 marks alpha table data; original member name unknown.
    u8 _03[0x90 - 0x03];
    u32 unknown90; // Inferred role: offset of the alpha table data; original member name unknown.
  };

  // Inferred role: alpha table data header; original type name unknown.
  struct unknown002 {
    u32 unknown00; // Inferred role: offset of the alpha entries; original member name unknown.
    s32 unknown04; // Inferred role: alpha entry count; original member name unknown.
  };

  // Inferred role: alpha table entry; original type name unknown.
  struct unknown003 {
    u16 unknown00; // Inferred role: mesh parts index plus one, 0 without mesh; original member name unknown.
    u16 unknown02; // Inferred role: lod parts index; original member name unknown.
  };

  DrResMdoAlpTbl();
  ~DrResMdoAlpTbl();
  int setup(const u8 *resource, u8 *work);
  int setupCnt(u32 count, u8 *work);
  void updateInstace();
  void update(f32 alpha, const DrResMdoLodObj *lodObj, const DrResMdoMeshObj *meshObj);
  void update();
  static void release(DrResMdoAlpTbl *&table);
  static int calcCntWorkSize(u32 count);
  static int calcWorkSize(const u8 *resource);
  static int create(u8 *work, const u8 *resource);
  static int createCnt(u8 *work, u32 count);

  f32 *unknown30;              // Inferred role: alpha values; original member name unknown.
  u32 *unknown38;              // Inferred role: inverted alpha bits; original member name unknown.
  const unknown003 *unknown40; // Inferred role: alpha entries; original member name unknown.
  u32 unknown48;               // Inferred role: alpha entry count; original member name unknown.
};

static_assert(offsetof(DrResMdoAlpTbl::unknown001, unknown02) == 0x02, "");
static_assert(offsetof(DrResMdoAlpTbl::unknown001, unknown90) == 0x90, "");
static_assert(offsetof(DrResMdoAlpTbl::unknown002, unknown04) == 0x04, "");
static_assert(sizeof(DrResMdoAlpTbl::unknown003) == 0x04, "");
static_assert(offsetof(DrResMdoAlpTbl, unknown30) == 0x30, "");
static_assert(offsetof(DrResMdoAlpTbl, unknown38) == 0x38, "");
static_assert(offsetof(DrResMdoAlpTbl, unknown40) == 0x40, "");
static_assert(offsetof(DrResMdoAlpTbl, unknown48) == 0x48, "");
static_assert(sizeof(DrResMdoAlpTbl) == 0x50, "");

} // namespace ml
