#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace ml {

class DrResMdoMeshParts {
public:
  static const u32 FLAG_MAT_ADD = 0x8000000;

  DrResMdoMeshParts();
  ~DrResMdoMeshParts();
  DrResMdoMeshParts &operator=(const DrResMdoMeshParts &other);
  void setName(const char *name);
  void setBoneName(const char *name);
  void setMatAdd(mm::Mat44 *matrix, const mm::Mat44 *baseMat, const mm::Mat44 *ofsMat, int index);
  void setMatrix(const mm::Mat44 &matrix);
  void setRegisterMatrix(int index, bool isRegister);
  void setDefAlpha(f32 alpha);
  f32 getDefAlpha() const;
  void updateAlpha();

  const char *m_name;
  const char *m_boneName;
  mm::Mat44 *unknown10;       // Inferred role: matrix; original member name unknown.
  const mm::Mat44 *unknown18; // Inferred role: base mat; original member name unknown.
  mm::Mat44 *unknown20;       // Inferred role: ofs mat; original member name unknown.
  u32 unknown28;              // Inferred role: flags; original member name unknown.
  f32 unknown2c[2];           // Inferred role: def alphas; original member name unknown.
  f32 unknown34;              // Inferred role: alpha; original member name unknown.
  u16 unknown38;              // Inferred role: mat index; original member name unknown.
  u8 unknown3a;               // Inferred role: volume fade effect; original member name unknown.
  u8 _3b[0x40 - 0x3b];
};

static_assert(offsetof(DrResMdoMeshParts, m_boneName) == 0x08, "");
static_assert(offsetof(DrResMdoMeshParts, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoMeshParts, unknown28) == 0x28, "");
static_assert(offsetof(DrResMdoMeshParts, unknown34) == 0x34, "");
static_assert(offsetof(DrResMdoMeshParts, unknown3a) == 0x3a, "");
static_assert(sizeof(DrResMdoMeshParts) == 0x40, "");

class DrResMdoMeshObj {
public:
  DrResMdoMeshObj();
  ~DrResMdoMeshObj();
  int setup(const u8 *resource, u8 *work);
  int getIdx(const char *name) const;
  static int calcWorkSize(const u8 *resource);
  static int create(u8 *work, const u8 *resource);
  static void release(DrResMdoMeshObj *&meshObj);
  DrResMdoMeshObj &operator=(const DrResMdoMeshObj &other);

  DrResMdoMeshParts *getParts(u32 index) const { return &unknown00[index]; }

  DrResMdoMeshParts *unknown00; // Inferred role: parts; original member name unknown.
  u32 unknown08;                // Inferred role: parts max; original member name unknown.
};

static_assert(offsetof(DrResMdoMeshObj, unknown08) == 0x08, "");

} // namespace ml
