#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_mat.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_mdo_node.h"
#include "dr/dr_mdo_sml_shadow_man.h"
#include "dr/dr_res_mdo_tex_list.h"
#include "dr/dr_res_mdo_vertex.h"
#include "mm_math/mm_vec3.h"

namespace ml {

void DrMdlObj::setDblBuffAlpha(bool isEnable) {
  if (isEnable) {
    unknown100 &= ~0x40000;
  } else {
    unknown100 |= 0x40000;
  }
}

void DrMdlObj::setClipBoxMode(bool isEnable) {
  if (isEnable) {
    unknownfc &= ~0x8000000;
  } else {
    unknownfc |= 0x8000000;
  }
}

DrMdlObj::DrMdlObj(int viewNum) : DrMdoCtl(viewNum) {}

void DrMdlObj::chageShadowObject(DrMdoSmlShadowMan *shadowMan) {
  if (unknown58 != nullptr) {
    shadowMan->changeViewNum(unknown58, unknown1a);
  }
}

void DrMdlObj::setFrame(f32 frame) { setMatAnmFrme(frame); }

void DrMdlObj::setMatrix(const mm::Mat44 &matrix) { DrMdoCtl::setMatrix(matrix); }

void DrMdlObj::setOffsetPos(const mm::Vec3 &position) { DrMdoCtl::setOffsetPos(position); }

bool DrMdlObj::getModelInfoHeader(int index, const MdsMdlInfoHeader **header) {
  MdoWrkMatRes *res = unknown30;
  if (res->unknown170 == 0) {
    return false;
  }
  int infoIndex = 0;
  u32 i = 0;
  do {
    const unknown026 &entry = res->unknown168[i];
    int j = 0;
    s64 offset = 0;
    while (j < entry.unknown04) {
      if (index - infoIndex == j) {
        *header = reinterpret_cast<const MdsMdlInfoHeader *>(res->unknown18 + entry.unknown00 - offset);
        return true;
      }
      j++;
      offset -= sizeof(MdsMdlInfoHeader);
    }
    infoIndex += j;
    i++;
  } while (i < res->unknown170);
  return false;
}

int DrMdlObj::getNodeMax() const { return m_nodeMax; }

unknown091 *DrMdlObj::getRimBloomWrk(u32 bufferIndex) {
  if (unknown30 == nullptr) {
    return nullptr;
  }
  if (unknown30->unknown158 == nullptr) {
    return nullptr;
  }
  return &unknown30->unknown158[bufferIndex];
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
  MdoWrkMatRes *matRes = unknown30;
  const MdsMatInfoHeader &matData = matRes->unknown28[index];
  *texture = matRes->unknowne8[*reinterpret_cast<const u16 *>(matRes->unknown10 + matData.unknown20)];
  return true;
}

void DrMdlObj::getMaterialHeader(int *count, const MdsMatInfoHeader **header) {
  *header = unknown30->unknown28;
  *count = unknown30->unknown30;
}

void DrMdlObj::getCharMkTextureList(int *count, const MdsMatCharMkTexTbl **table) {
  *count = unknown16a;
  *table = unknown48;
}

int DrMdlObj::getTextureResMax() const {
  DrResMdoTexList *textureList = unknown30->unknownd0;
  if (textureList == nullptr) {
    return 0;
  }
  return textureList->unknown68;
}

int DrMdlObj::getTextureResIdx(const char *name) {
  if (unknown30->unknownd0 != nullptr) {
    for (int i = 0; i < unknown30->unknownd0->unknown68; i++) {
      if (strcmp(unknown30->unknownd0->getTexName(i), name) == 0) {
        return i;
      }
    }
  }
  return -1;
}

grlib::CGLibTextureBuffer *DrMdlObj::getTextureRes(const char *name) {
  if (unknown30->unknownd0 != nullptr) {
    for (int i = 0; i < unknown30->unknownd0->unknown68; i++) {
      if (strcmp(unknown30->unknownd0->getTexName(i), name) == 0) {
        return unknown30->unknownd0->getTexObj(i);
      }
    }
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrMdlObj::getTextureRes(int index) {
  DrResMdoTexList *textureList = unknown30->unknownd0;
  if (textureList == nullptr || index >= textureList->unknown68) {
    return nullptr;
  }
  return textureList->getTexObj(index);
}

void DrMdlObj::getNowTextureRes(grlib::CGLibTextureBuffer **&textures, int &count) {
  textures = unknown30->unknowne8;
  count = unknown30->unknownf0;
}

void DrMdlObj::setTextureRes(const char *name, grlib::CGLibTextureBuffer *texture) {
  for (int i = 0; i < unknown30->unknownf0; i++) {
    if (strcmp(unknown30->unknownd0->getTexName(i), name) == 0) {
      unknown30->unknowne8[i] = texture;
      return;
    }
  }
}

void DrMdlObj::setTextureRes(int index, grlib::CGLibTextureBuffer *texture) {
  if (index < unknown30->unknownf0) {
    unknown30->unknowne8[index] = texture;
  }
}

int DrMdlObj::getMaterialResIdx(const char *name) const {
  for (int i = 0; i < unknown30->unknown30; i++) {
    if (strcmp(unknown30->unknownc0[i].m_name, name) == 0) {
      return i;
    }
  }
  return -1;
}

const char *DrMdlObj::getMaterialIdxName(int index) const {
  if (index > unknown30->unknown30) {
    return nullptr;
  }
  return unknown30->unknownc0[index].m_name;
}

DrResMdoMat *DrMdlObj::getMaterialRes(const char *name) {
  for (int i = 0; i < unknown30->unknown30; i++) {
    if (strcmp(unknown30->unknownc0[i].m_name, name) == 0) {
      return &unknown30->unknownc0[i];
    }
  }
  return nullptr;
}

DrResMdoMat *DrMdlObj::getMaterialRes(int index) { return &unknown30->unknownc0[index]; }

bool DrMdlObj::getVertexInfo(int index, const MdsMdlVertexFmt **format, int *count) { return unknown30->unknownc8->getVertexInfo(index, format, count); }

void DrMdlObj::setAlpha(f32 alpha) {
  if (unknown100 & unknown029_18) {
    unknowne0 = alpha;
  } else {
    unknown100 |= unknown029_16 << DrMan::s_nDblStockIdx;
    unknownd0[DrMan::s_nDblStockIdx] = alpha;
  }
}

f32 DrMdlObj::getAlpha() const { return (unknown100 & unknown029_18) ? unknowne0 : unknownd0[DrMan::s_nDblStockIdx]; }

void DrMdlObj::setWriteStencil(bool isEnable) {
  bool isWriteStencil = unknownfc & unknown027_4;
  if (isEnable) {
    if (!isWriteStencil) {
      unknownfc |= unknown027_4;
      setCreateDisplayList();
    }
  } else if (isWriteStencil) {
    unknownfc &= ~unknown027_4;
    setCreateDisplayList();
  }
}

void DrMdlObj::setAlwaysMiddleTexStm(bool isEnable) { unknownfc = !isEnable ? unknownfc & ~unknown027_17 : unknownfc | unknown027_17; }

void DrMdlObj::setSpBlurOff(bool isEnable) { unknownfc = !isEnable ? unknownfc & ~unknown027_15 : unknownfc | unknown027_15; }

void DrMdlObj::setGpuClip(bool isEnable) { unknownfc = !isEnable ? unknownfc | unknown027_16 : unknownfc & ~unknown027_16; }

void DrMdlObj::setOcclusionQuery(bool isEnable) { unknownfc = !isEnable ? unknownfc | unknown027_18 : unknownfc & ~unknown027_18; }

void DrMdlObj::setAlwaysTexStm(bool isEnable) { unknownfc = !isEnable ? unknownfc & ~unknown027_2 : unknownfc | unknown027_2; }

bool DrMdlObj::isMdlTexStm() const { return true; }

bool DrMdlObj::isMemTexStm() const { return (unknownfc & (0x2000 | 0x2)) != 0x2; }

bool DrMdlObj::isMemMiddleTexStm() const { return (unknownfc & (0x20 | 0x2)) != 0x2; }

void DrMdlObj::setCreateDisplayList() { unknown20 &= ~0x60; }

void DrMdlObj::setExpressDrawMode(bool isEnable) { unknownfc = !isEnable ? unknownfc & ~unknown027_20 : unknownfc | unknown027_20; }

const mm::Vec3 &DrMdlObj::getAABBMax() const { return m_AABBMax; }

const mm::Vec3 &DrMdlObj::getAABBMin() const { return m_AABBMin; }

void DrMdlObj::getInitialVertexAABBMax(mm::Vec3 &max, bool isScaled) const {
  const f32 *aabbMax = unknown30->unknown168->unknown0c;
  max = mm::Vec3(aabbMax[0], aabbMax[1], aabbMax[2]);
  if (isScaled) {
    f32 scale = unknowne8;
    max.x = scale * max.x;
    max.y = scale * max.y;
    max.z = scale * max.z;
  }
}

void DrMdlObj::getInitialVertexAABBMin(mm::Vec3 &min, bool isScaled) const {
  const f32 *aabbMin = unknown30->unknown168->unknown18;
  min = mm::Vec3(aabbMin[0], aabbMin[1], aabbMin[2]);
  if (isScaled) {
    f32 scale = unknowne8;
    min.x = scale * min.x;
    min.y = scale * min.y;
    min.z = scale * min.z;
  }
}

void DrMdlObj::setSimpleShadow(bool isEnable) { unknownfc = !isEnable ? unknownfc & ~unknown027_10 : unknownfc | unknown027_10; }

bool DrMdlObj::isGpuRender() const { return m_gpuRender; }

void DrMdlObj::setSpAlphaMode(bool isEnable) { unknownfc = !isEnable ? unknownfc & ~unknown027_14 : unknownfc | unknown027_14; }

void DrMdlObj::setCamCheckMode(bool isEnable) { unknownfc = !isEnable ? unknownfc & ~unknown027_28 : unknownfc | unknown027_28; }

bool DrMdlObj::isCamCheckResl() const { return (unknownfc & unknown027_29) != 0; }

bool DrMdlObj::isAce() const { return unknown30->unknown118 != nullptr; }

void DrMdlObj::setAceColor(int index, const mm::Col3 &color) {
  if (unknown30 != nullptr && unknown30->unknown118 != nullptr) {
    unknown30->unknown118->unknown00[index] = color;
  }
}

void DrMdlObj::setAceVal(int index, f32 value) {
  if (unknown30 != nullptr && unknown30->unknown118 != nullptr) {
    unknown30->unknown118->unknown30[index] = value;
  }
}

const mm::Col3 &DrMdlObj::getAceColor(int index) const {
  if (unknown30->unknown118 != nullptr) {
    return unknown30->unknown118->unknown00[index];
  }
  static mm::Col3 zero(0.0f, 0.0f, 0.0f);
  return zero;
}

f32 DrMdlObj::getAceVal(int index) const {
  if (unknown30->unknown118 != nullptr) {
    return unknown30->unknown118->unknown30[index];
  }
  return 0.0f;
}

void DrMdlObj::setDebugWindow(bool isEnable) { unknownfc = !isEnable ? unknownfc & ~(unknown027_31 | unknown027_30) : unknownfc | unknown027_31; }

u32 DrMdlObj::isDebugWindow() { return unknownfc & unknown027_31; }

u32 DrMdlObj::isDebugDelete() { return unknownfc & unknown027_30; }

void DrMdlObj::OnCloseAttriMenu() { unknownfc |= unknown027_30; }

} // namespace ml
