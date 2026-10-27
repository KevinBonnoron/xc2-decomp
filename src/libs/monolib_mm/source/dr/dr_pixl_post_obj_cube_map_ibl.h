#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrPixlRenderCubeMapMipMap;

class DrPixlPostObjCubeMapIBL {
public:
  ~DrPixlPostObjCubeMapIBL();
  void render();
  void update();
  void setUniformBlock(u32 index) const;
  void setStorageBuffer(u32 index) const;
  u32 getPremMipCount() const;
  grlib::CGLibTextureBuffer *getPremTexture() const;
  const mm::Mat44 &getSHMatrix(u32 index) const;
  void updateUB_ToProxySpace(u8 *work);
  void updateUB_ShMatrixList(u8 *work);

  u8 _00[0x18];
  bool unknown18; // Inferred role: initialize flag; original member name unknown.
  u8 _19[0x20 - 0x19];
  DrPixlRenderCubeMapMipMap *m_premTexture[2];
  u32 m_premMipCount;
  u8 _34[0x40 - 0x34];
  mm::Mat44 m_shMatrix[2][3];
  mm::Mat44 unknown1c0; // Inferred role: proxy space matrix; original member name unknown.
  mm::Vec3 unknown200;  // Inferred role: IBL position; original member name unknown.
  u32 unknown210;
  u32 unknown214; // Inferred role: buffer index; original member name unknown.
  grlib::CGLibDblUniformBlock *m_uniformBlock;
};

static_assert(offsetof(DrPixlPostObjCubeMapIBL, m_premTexture) == 0x20, "");
static_assert(offsetof(DrPixlPostObjCubeMapIBL, m_premMipCount) == 0x30, "");
static_assert(offsetof(DrPixlPostObjCubeMapIBL, m_shMatrix) == 0x40, "");
static_assert(offsetof(DrPixlPostObjCubeMapIBL, unknown1c0) == 0x1c0, "");
static_assert(offsetof(DrPixlPostObjCubeMapIBL, unknown200) == 0x200, "");
static_assert(offsetof(DrPixlPostObjCubeMapIBL, unknown214) == 0x214, "");
static_assert(offsetof(DrPixlPostObjCubeMapIBL, m_uniformBlock) == 0x218, "");

} // namespace ml
