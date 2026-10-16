#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace ml {

class DrResMdoMeshParts {
public:
  void setMatrix(const mm::Mat44 &matrix);
  void setRegisterMatrix(int index, bool isRegister);
  void setDefAlpha(f32 alpha);
  f32 getDefAlpha() const;

  const char *m_name;
  const char *m_boneName;
  u8 _10[0x20 - 0x10];
  mm::Mat44 *m_ofsMat;
  u8 _28[0x2b - 0x28];
  u8 m_flags;
  u8 _2c[0x3a - 0x2c];
  u8 m_volumeFadeEffect;
  u8 _3b[0x40 - 0x3b];
};

static_assert(offsetof(DrResMdoMeshParts, m_boneName) == 0x08, "");
static_assert(offsetof(DrResMdoMeshParts, m_ofsMat) == 0x20, "");
static_assert(offsetof(DrResMdoMeshParts, m_flags) == 0x2b, "");
static_assert(offsetof(DrResMdoMeshParts, m_volumeFadeEffect) == 0x3a, "");
static_assert(sizeof(DrResMdoMeshParts) == 0x40, "");

class DrResMdoMeshObj {
public:
  int getIdx(const char *name) const;

  DrResMdoMeshParts *getParts(u32 index) const { return &m_parts[index]; }

  DrResMdoMeshParts *m_parts;
  int m_partsMax;
};

static_assert(offsetof(DrResMdoMeshObj, m_partsMax) == 0x08, "");

} // namespace ml
