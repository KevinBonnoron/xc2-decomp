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
  mm::Mat44 *m_matrix;
  const mm::Mat44 *m_baseMat;
  mm::Mat44 *m_ofsMat;
  u32 m_flags;
  f32 m_defAlphas[2];
  f32 m_alpha;
  u16 m_matIndex;
  u8 m_volumeFadeEffect;
  u8 _3b[0x40 - 0x3b];
};

static_assert(offsetof(DrResMdoMeshParts, m_boneName) == 0x08, "");
static_assert(offsetof(DrResMdoMeshParts, m_ofsMat) == 0x20, "");
static_assert(offsetof(DrResMdoMeshParts, m_flags) == 0x28, "");
static_assert(offsetof(DrResMdoMeshParts, m_alpha) == 0x34, "");
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
