#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrShdMdoExtTblObj;

// Inferred role: model data dec shd info; original type name unknown.
struct unknown041 {
  u32 unknown00; // Inferred role: name ofs; original member name unknown.
  u32 unknown04; // Inferred role: id; original member name unknown.
  u32 unknown08; // Inferred role: parm max; original member name unknown.
  u32 unknown0c; // Inferred role: shader idx ofs; original member name unknown.
  s32 unknown10; // Inferred role: shader num; original member name unknown.
};

static_assert(sizeof(unknown041) == 0x14, "");

// Inferred role: model data dec shd header; original type name unknown.
struct unknown042 {
  s32 num;
  u32 infoOfs;
};

// Inferred role: resource mdo dec shd; original type name unknown.
struct unknown043 {
  const unknown041 *unknown00; // Inferred role: info; original member name unknown.
  u8 *unknown08;               // Inferred role: decl ofs; original member name unknown.
  u32 unknown10;               // Inferred role: parm; original member name unknown.
  u32 unknown14;               // Inferred role: prev parm; original member name unknown.
};

static_assert(sizeof(unknown043) == 0x18, "");

class DrResMdoShdObj {
public:
  DrResMdoShdObj();
  ~DrResMdoShdObj();
  int setup(const u8 *resource, u8 *work);
  void bindShader(DrShdMdoExtTblObj *extTblObj);
  bool update(DrShdMdoExtTblObj *extTblObj);
  u32 getDecShdID(u32 index) const;
  int getDecShdIdx(const char *name) const;
  int getDecShdIdx(u32 id) const;
  void setDecShdParm(u32 index, u32 parm);
  u32 getDecShdParm(u32 index) const;
  u32 getDecShdParmMax(u32 index) const;
  static int calcWorkSize(const u8 *resource);
  static int create(u8 *work, const u8 *resource);
  static void release(DrResMdoShdObj *&shdObj);

  const unknown042 *unknown00; // Inferred role: header; original member name unknown.
  unknown043 *unknown08;       // Inferred role: dec shds; original member name unknown.
  u32 unknown10;               // Inferred role: dec shd max; original member name unknown.
};

static_assert(offsetof(DrResMdoShdObj, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoShdObj, unknown10) == 0x10, "");
static_assert(sizeof(DrResMdoShdObj) == 0x18, "");

} // namespace ml
