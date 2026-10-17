#include "dr/dr_mdl_obj.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_mdo_node.h"
#include "dr/dr_mdo_sml_shadow_man.h"
#include "dr/dr_res_mdo_tex_list.h"
#include "dr/dr_res_mdo_vertex.h"
#include "mm_math/mm_vec3.h"

namespace ml {

DrMdlObj::DrMdlObj(int viewNum) : DrMdoCtl(viewNum) {}

void DrMdlObj::chageShadowObject(DrMdoSmlShadowMan *shadowMan) {
  if (m_smlShadow != nullptr) {
    shadowMan->changeViewNum(m_smlShadow, m_viewNum);
  }
}

void DrMdlObj::setFrame(f32 frame) { setMatAnmFrme(frame); }

void DrMdlObj::setMatrix(const mm::Mat44 &matrix) { DrMdoCtl::setMatrix(matrix); }

void DrMdlObj::setOffsetPos(const mm::Vec3 &position) { DrMdoCtl::setOffsetPos(position); }

int DrMdlObj::getNodeMax() const { return m_nodeMax; }

MdoWrkRimBloom *DrMdlObj::getRimBloomWrk(u32 bufferIndex) {
  if (m_matRes == nullptr) {
    return nullptr;
  }
  if (m_matRes->rimBlooms == nullptr) {
    return nullptr;
  }
  return &m_matRes->rimBlooms[bufferIndex];
}

int DrMdlObj::getNodeIdx(const char *name) const { return DrMdoNode::getNodeIdx(name); }

const char *DrMdlObj::getNodeName(int index) const { return DrMdoNode::getNodeName(index); }

void DrMdlObj::setResBoneMat(int index, const mm::Mat44 &matrix) { setNodeMatrix(index, matrix); }

const mm::Mat44 &DrMdlObj::getResBoneMat(int index) const { return getNodeMatrix(index); }

mm::Mat44 *DrMdlObj::getResBoneMatPtr(int index) { return getNodeMatrixPtr(index); }

void DrMdlObj::setResBoneExMode(int index, bool isEnable) {}

bool DrMdlObj::getModelTexture(int index, const grlib::CGLibTextureBuffer **texture) {
  if (texture == nullptr) {
    return false;
  }
  MdoWrkMatRes *matRes = m_matRes;
  const MdsMatInfoHeader &matData = matRes->matData[index];
  *texture = matRes->textures[*reinterpret_cast<const u16 *>(matRes->textureIndices + matData.textureIndexOffset)];
  return true;
}

void DrMdlObj::getMaterialHeader(int *count, const MdsMatInfoHeader **header) {
  *header = m_matRes->matData;
  *count = m_matRes->matCount;
}

void DrMdlObj::getCharMkTextureList(int *count, const MdsMatCharMkTexTbl **table) {
  *count = m_charMkTextureCount;
  *table = m_charMkTextures;
}

int DrMdlObj::getTextureResMax() const {
  DrResMdoTexList *textureList = m_matRes->textureList;
  if (textureList == nullptr) {
    return 0;
  }
  return textureList->m_texMax;
}

int DrMdlObj::getTextureResIdx(const char *name) {
  if (m_matRes->textureList != nullptr) {
    for (int i = 0; i < m_matRes->textureList->m_texMax; i++) {
      if (strcmp(m_matRes->textureList->getTexName(i), name) == 0) {
        return i;
      }
    }
  }
  return -1;
}

grlib::CGLibTextureBuffer *DrMdlObj::getTextureRes(const char *name) {
  if (m_matRes->textureList != nullptr) {
    for (int i = 0; i < m_matRes->textureList->m_texMax; i++) {
      if (strcmp(m_matRes->textureList->getTexName(i), name) == 0) {
        return m_matRes->textureList->getTexObj(i);
      }
    }
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrMdlObj::getTextureRes(int index) {
  DrResMdoTexList *textureList = m_matRes->textureList;
  if (textureList == nullptr || index >= textureList->m_texMax) {
    return nullptr;
  }
  return textureList->getTexObj(index);
}

void DrMdlObj::getNowTextureRes(grlib::CGLibTextureBuffer **&textures, int &count) {
  textures = m_matRes->textures;
  count = m_matRes->textureCount;
}

void DrMdlObj::setTextureRes(const char *name, grlib::CGLibTextureBuffer *texture) {
  for (int i = 0; i < m_matRes->textureCount; i++) {
    if (strcmp(m_matRes->textureList->getTexName(i), name) == 0) {
      m_matRes->textures[i] = texture;
      return;
    }
  }
}

void DrMdlObj::setTextureRes(int index, grlib::CGLibTextureBuffer *texture) {
  if (index < m_matRes->textureCount) {
    m_matRes->textures[index] = texture;
  }
}

int DrMdlObj::getMaterialResIdx(const char *name) const {
  for (int i = 0; i < m_matRes->matCount; i++) {
    if (strcmp(m_matRes->matEntries[i].name, name) == 0) {
      return i;
    }
  }
  return -1;
}

const char *DrMdlObj::getMaterialIdxName(int index) const {
  if (index > m_matRes->matCount) {
    return nullptr;
  }
  return m_matRes->matEntries[index].name;
}

MdoWrkMatEntry *DrMdlObj::getMaterialRes(const char *name) {
  for (int i = 0; i < m_matRes->matCount; i++) {
    if (strcmp(m_matRes->matEntries[i].name, name) == 0) {
      return &m_matRes->matEntries[i];
    }
  }
  return nullptr;
}

MdoWrkMatEntry *DrMdlObj::getMaterialRes(int index) { return &m_matRes->matEntries[index]; }

bool DrMdlObj::getVertexInfo(int index, const MdsMdlVertexFmt **format, int *count) { return m_matRes->vertex->getVertexInfo(index, format, count); }

void DrMdlObj::setAlpha(f32 alpha) {
  if (m_alphaFlags & ALPHA_FLAG_SINGLE_BUFFER) {
    m_alpha = alpha;
  } else {
    m_alphaFlags |= ALPHA_FLAG_UPDATED << DrMan::s_nDblStockIdx;
    m_alphas[DrMan::s_nDblStockIdx] = alpha;
  }
}

f32 DrMdlObj::getAlpha() const { return (m_alphaFlags & ALPHA_FLAG_SINGLE_BUFFER) ? m_alpha : m_alphas[DrMan::s_nDblStockIdx]; }

void DrMdlObj::setWriteStencil(bool isEnable) {
  bool isWriteStencil = m_drawFlags & DRAW_FLAG_WRITE_STENCIL;
  if (isEnable) {
    if (!isWriteStencil) {
      m_drawFlags |= DRAW_FLAG_WRITE_STENCIL;
      setCreateDisplayList();
    }
  } else if (isWriteStencil) {
    m_drawFlags &= ~DRAW_FLAG_WRITE_STENCIL;
    setCreateDisplayList();
  }
}

void DrMdlObj::setAlwaysMiddleTexStm(bool isEnable) {
  m_drawFlags = !isEnable ? m_drawFlags & ~DRAW_FLAG_ALWAYS_MIDDLE_TEX_STM : m_drawFlags | DRAW_FLAG_ALWAYS_MIDDLE_TEX_STM;
}

void DrMdlObj::setSpBlurOff(bool isEnable) { m_drawFlags = !isEnable ? m_drawFlags & ~DRAW_FLAG_SP_BLUR_OFF : m_drawFlags | DRAW_FLAG_SP_BLUR_OFF; }

void DrMdlObj::setGpuClip(bool isEnable) { m_drawFlags = !isEnable ? m_drawFlags | DRAW_FLAG_GPU_CLIP_OFF : m_drawFlags & ~DRAW_FLAG_GPU_CLIP_OFF; }

void DrMdlObj::setOcclusionQuery(bool isEnable) {
  m_drawFlags = !isEnable ? m_drawFlags | DRAW_FLAG_OCCLUSION_QUERY_OFF : m_drawFlags & ~DRAW_FLAG_OCCLUSION_QUERY_OFF;
}

void DrMdlObj::setAlwaysTexStm(bool isEnable) {
  m_drawFlags = !isEnable ? m_drawFlags & ~DRAW_FLAG_ALWAYS_TEX_STM : m_drawFlags | DRAW_FLAG_ALWAYS_TEX_STM;
}

bool DrMdlObj::isMdlTexStm() const { return true; }

bool DrMdlObj::isMemTexStm() const { return (m_drawFlags & (0x2000 | 0x2)) != 0x2; }

bool DrMdlObj::isMemMiddleTexStm() const { return (m_drawFlags & (0x20 | 0x2)) != 0x2; }

void DrMdlObj::setCreateDisplayList() { m_updateFlags &= ~0x60; }

void DrMdlObj::setExpressDrawMode(bool isEnable) {
  m_drawFlags = !isEnable ? m_drawFlags & ~DRAW_FLAG_EXPRESS_DRAW_MODE : m_drawFlags | DRAW_FLAG_EXPRESS_DRAW_MODE;
}

const mm::Vec3 &DrMdlObj::getAABBMax() const { return m_aabbMax; }

const mm::Vec3 &DrMdlObj::getAABBMin() const { return m_aabbMin; }

void DrMdlObj::getInitialVertexAABBMax(mm::Vec3 &max, bool isScaled) const {
  const f32 *aabbMax = m_matRes->mdlEntries->aabbMax;
  max = mm::Vec3(aabbMax[0], aabbMax[1], aabbMax[2]);
  if (isScaled) {
    f32 scale = m_scale;
    max.x = scale * max.x;
    max.y = scale * max.y;
    max.z = scale * max.z;
  }
}

void DrMdlObj::getInitialVertexAABBMin(mm::Vec3 &min, bool isScaled) const {
  const f32 *aabbMin = m_matRes->mdlEntries->aabbMin;
  min = mm::Vec3(aabbMin[0], aabbMin[1], aabbMin[2]);
  if (isScaled) {
    f32 scale = m_scale;
    min.x = scale * min.x;
    min.y = scale * min.y;
    min.z = scale * min.z;
  }
}

void DrMdlObj::setSimpleShadow(bool isEnable) {
  m_drawFlags = !isEnable ? m_drawFlags & ~DRAW_FLAG_SIMPLE_SHADOW : m_drawFlags | DRAW_FLAG_SIMPLE_SHADOW;
}

bool DrMdlObj::isGpuRender() const { return m_isGpuRender; }

void DrMdlObj::setSpAlphaMode(bool isEnable) {
  m_drawFlags = !isEnable ? m_drawFlags & ~DRAW_FLAG_SP_ALPHA_MODE : m_drawFlags | DRAW_FLAG_SP_ALPHA_MODE;
}

void DrMdlObj::setCamCheckMode(bool isEnable) {
  m_drawFlags = !isEnable ? m_drawFlags & ~DRAW_FLAG_CAM_CHECK_MODE : m_drawFlags | DRAW_FLAG_CAM_CHECK_MODE;
}

bool DrMdlObj::isCamCheckResl() const { return (m_drawFlags & DRAW_FLAG_CAM_CHECK_RESL) != 0; }

bool DrMdlObj::isAce() const { return m_matRes->shaderParm != nullptr; }

void DrMdlObj::setAceColor(int index, const mm::Col3 &color) {
  if (m_matRes != nullptr && m_matRes->shaderParm != nullptr) {
    m_matRes->shaderParm->colors[index] = color;
  }
}

void DrMdlObj::setAceVal(int index, f32 value) {
  if (m_matRes != nullptr && m_matRes->shaderParm != nullptr) {
    m_matRes->shaderParm->values[index] = value;
  }
}

const mm::Col3 &DrMdlObj::getAceColor(int index) const {
  if (m_matRes->shaderParm != nullptr) {
    return m_matRes->shaderParm->colors[index];
  }
  static mm::Col3 zero(0.0f, 0.0f, 0.0f);
  return zero;
}

f32 DrMdlObj::getAceVal(int index) const {
  if (m_matRes->shaderParm != nullptr) {
    return m_matRes->shaderParm->values[index];
  }
  return 0.0f;
}

void DrMdlObj::setDebugWindow(bool isEnable) {
  m_drawFlags = !isEnable ? m_drawFlags & ~(DRAW_FLAG_DEBUG_WINDOW | DRAW_FLAG_DEBUG_DELETE) : m_drawFlags | DRAW_FLAG_DEBUG_WINDOW;
}

u32 DrMdlObj::isDebugWindow() { return m_drawFlags & DRAW_FLAG_DEBUG_WINDOW; }

u32 DrMdlObj::isDebugDelete() { return m_drawFlags & DRAW_FLAG_DEBUG_DELETE; }

void DrMdlObj::OnCloseAttriMenu() { m_drawFlags |= DRAW_FLAG_DEBUG_DELETE; }

} // namespace ml
