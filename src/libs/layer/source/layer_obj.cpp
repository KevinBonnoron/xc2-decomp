#include "layer/layer_obj.h"

#include <math.h>
#include <string.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "layer/layer_acc_manager.h"
#include "layer/layer_act_base.h"
#include "layer/layer_anime_obj.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_top_mask_obj.h"
#include "layer/layer_res_sec_texture.h"
#include "mtl/alloc_handle.h"

namespace layer {

namespace {

const LayerBasePos *getMatrixParm(const LayerObj *layer, u32 flag) {
  if (layer->getStateFlags(LayerManager::s_nStkIdx) & flag) {
    return &layer->m_layerResParmInfo[LayerManager::s_nStkIdx].m_layerBasePos;
  }

  if (layer->getStateFlags(LayerManager::s_nDebIdx) & flag) {
    return &layer->m_layerResParmInfo[LayerManager::s_nDebIdx].m_layerBasePos;
  }

  return &layer->m_layerResParmInfo[2].m_layerBasePos;
}

const LayerResColor *getColorParm(const LayerObj *layer, u32 flag) {
  if (layer->getStateFlags(LayerManager::s_nStkIdx) & flag) {
    return &layer->m_layerResParmInfo[LayerManager::s_nStkIdx].m_layerResColor;
  }

  if (layer->getStateFlags(LayerManager::s_nDebIdx) & flag) {
    return &layer->m_layerResParmInfo[LayerManager::s_nDebIdx].m_layerResColor;
  }

  return &layer->m_layerResParmInfo[2].m_layerResColor;
}

// Inferred layout of an action command header, followed by its f32 parameters; original type and member names unknown.
struct unknown020 {
  u16 unknown00; // Inferred role: command type; original member name unknown.
  u16 unknown02; // Inferred role: argument; original member name unknown.
};

static_assert(sizeof(unknown020) == 0x04, "");

} // namespace

LayerObj::LayerObj() {
  m_space = 0;
  m_blendType = 5;
  unknownc5 = 5;
  m_texFilterType = 3;
  unknowna8 = 0x80;
  for (s32 i = 0; i < 2; i++) {
    unknowna0[i] = 0;
  }
  m_priority = 0;
  for (s32 i = 0; i < 2; i++) {
    unknown1d8[i] = 0;
  }
  m_resData = nullptr;
  unknown220[0] = unknown220[1] = unknown220[2] = nullptr;
  for (s32 i = 0; i < 3; i++) {
    LayerResParmInfo &parm = m_layerResParmInfo[i];
    parm.m_layerBasePos.unknown00 = parm.m_layerBasePos.unknown04 = 0.0f;
    parm.m_layerBasePos.unknown0c = parm.m_layerBasePos.unknown10 = 1.0f;
    parm.m_layerBasePos.unknown08 = 0.0f;
    parm.m_layerBasePos.unknown14 = parm.m_layerBasePos.unknown18 = 0.0f;
    parm.m_layerResColor.m_mulCol = mm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
    parm.m_layerResColor.m_addCol = mm::Col3(0.0f, 0.0f, 0.0f);
  }
  unknownb0 = 0;
  unknown208[0] = unknown208[1] = unknown208[2] = nullptr;
  m_ctrlSpd = unknown1f8 = 1.0f;
  unknown1fc = 0.0f;
  unknown200 = 0.0f;
  m_layerResRenderInfo.unknown00 = m_layerResRenderInfo.unknown04 = m_layerResRenderInfo.unknown08 = m_layerResRenderInfo.unknown0c = 1.0f;
  m_layerResRenderInfo.m_pixelX = 0;
  m_layerResRenderInfo.m_pixelY = 0;
  m_layerResRenderInfo.m_pixelWidth = m_layerResRenderInfo.m_pixelHeight = 1;
  m_layerResRenderInfo.m_centerType = 0;
  m_layerResDispInfo.unknown00 = 1.0f;
  m_layerResDispInfo.unknown04 = 1.0f;
  m_layerResDispInfo.unknown08 = mm::Pnt<f32>(0.0f, 0.0f);
  unknown20[0] = mm::Mat44::identity;
  unknown20[1] = mm::Mat44::identity;
  unknownc2 = 0;
  m_layerResUvParam.unknown00[2].unknown00 = mm::Pnt<f32>(0.0f, 0.0f);
  m_layerObjTopMaskObj = nullptr;
  m_maskObj = nullptr;
  unknown238 = nullptr;
  m_layerResUvParam.unknown00[2].unknown08 = m_layerResUvParam.unknown00[2].unknown0c = 1.0f;
  m_layerResUvParam.unknown00[2].unknown10 = 0.0f;
}

void LayerObj::resourceInit() {}

void LayerObj::applyPartsSetup() {}

void LayerObj::applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) {}

void LayerObj::release() {
  onStateFlags(1);
  unknown18 = 0;
  unknown1c = 0x22;
}

void LayerObj::baseRelease() {
  if (unknown238 != nullptr) {
    delete unknown238;
    unknown238 = nullptr;
  }
  for (s32 i = 0; i < 3; i++) {
    if (unknown208[i] != nullptr) {
      delete unknown208[i];
      unknown208[i] = nullptr;
    }
  }
  for (s32 i = 0; i < 3; i++) {
    if (unknown220[i] != nullptr) {
      delete unknown220[i];
      unknown220[i] = nullptr;
    }
  }
}

void LayerObj::setInitPos(f32 x, f32 y) {
  m_layerResParmInfo[1].m_layerBasePos.unknown00 = x;
  m_layerResParmInfo[0].m_layerBasePos.unknown00 = x;
  m_layerResParmInfo[2].m_layerBasePos.unknown00 = x;
  m_layerResParmInfo[1].m_layerBasePos.unknown04 = y;
  m_layerResParmInfo[0].m_layerBasePos.unknown04 = y;
  m_layerResParmInfo[2].m_layerBasePos.unknown04 = y;
}

void LayerObj::setInitRot(f32 rot) {
  m_layerResParmInfo[1].m_layerBasePos.unknown08 = rot;
  m_layerResParmInfo[0].m_layerBasePos.unknown08 = rot;
  m_layerResParmInfo[2].m_layerBasePos.unknown08 = rot;
}

void LayerObj::setInitScl(f32 x, f32 y) {
  m_layerResParmInfo[1].m_layerBasePos.unknown0c = x;
  m_layerResParmInfo[0].m_layerBasePos.unknown0c = x;
  m_layerResParmInfo[2].m_layerBasePos.unknown0c = x;
  m_layerResParmInfo[1].m_layerBasePos.unknown10 = y;
  m_layerResParmInfo[0].m_layerBasePos.unknown10 = y;
  m_layerResParmInfo[2].m_layerBasePos.unknown10 = y;
}

void LayerObj::setInitMulCol(const mm::Col4 &color) {
  m_layerResParmInfo[2].m_layerResColor.m_mulCol = m_layerResParmInfo[0].m_layerResColor.m_mulCol = m_layerResParmInfo[1].m_layerResColor.m_mulCol = color;
}

void LayerObj::setInitAddCol(const mm::Col3 &color) {
  m_layerResParmInfo[2].m_layerResColor.m_addCol = m_layerResParmInfo[0].m_layerResColor.m_addCol = m_layerResParmInfo[1].m_layerResColor.m_addCol = color;
}

void LayerObj::setInitPosScl(f32 x, f32 y, f32 sclX, f32 sclY) {
  if (unknown18 == LAYER_OBJ_TYPE_FONT) {
    setInitPos(x, y);
    return;
  }
  if (!(unknowna8 & 0x2)) {
    setInitPos(x, y);
    if (LayerManager::get()->m_coordinate != LAYER_COORDINATE_PIXEL) {
      setInitScl(sclX / m_layerResRenderInfo.unknown08, sclY / m_layerResRenderInfo.unknown0c);
    } else {
      setInitScl(sclX, sclY);
    }
  } else {
    if (LayerManager::get()->m_coordinate != LAYER_COORDINATE_PIXEL) {
      setInitPos(x + sclX, y);
    } else {
      setInitPos(static_cast<u16>(m_layerResRenderInfo.m_pixelWidth) * sclX + x, y);
    }
    setInitScl(sclY, sclY);
  }
}

void LayerObj::updateCtrlSpd(f32 speed) {
  u32 &flags = unknowna0[static_cast<u32>(LayerManager::s_nDebIdx)];
  if (flags & 0xf000) {
    if (flags & 0x1000) {
      unknowna8 |= 0x200;
    } else if (flags & 0x2000) {
      unknowna8 &= ~0x200;
    }

    if (flags & 0x4000) {
      unknowna8 |= 0x80;
    } else if (flags & 0x8000) {
      unknowna8 &= ~0x80;
    }
  }

  unknown1f8 = m_ctrlSpd * speed;
}

void LayerObj::updateAnimObj() {
  if (unknown208[2] != nullptr) {
    f32 frame = unknown1f8 * LayerManager::get()->unknown80;
    if (unknowna8 & 0x200) {
      frame = 0.0f;
    }

    if (unknown208[2]->update(m_layerResParmInfo[2], frame) && unknown208[2] != nullptr) {
      delete unknown208[2];
      unknown208[2] = nullptr;
    }
  }

  if (m_layerResParmInfo[2].m_layerResColor.m_mulCol.a <= 0.0f && unknown18 != LAYER_OBJ_TYPE_MASK) {
    unknowna8 |= 0x80000;
  }
}

void LayerObj::updateSecondTex() {
  if (unknown220[2] != nullptr) {
    unknown220[2]->update();
  }
}

void LayerObj::updateDefSpace(grlib::CGLibDblUniformBlock *&uniform, LAYER_SPACE_TYPE space, const mm::Mat44 &matrix) {
  if (space == LAYER_SPACE_TYPE_UNKNOWN_2) {
    LayerObjUtil::calcMatrixToZBuffPos(unknown200, unknown1fc, matrix);
    unknowna8 |= 0xc00;
    unknowna8 &= ~0x1000;
    LayerObjUtil::createWorldMatrixUniform(uniform, matrix, m_priority * 0.0625f);
    return;
  }
  if (space == LAYER_SPACE_TYPE_UNKNOWN_1) {
    LayerObjUtil::calcMatrixToZBuffPos(unknown200, unknown1fc, matrix);
    unknowna8 |= 0x400;
  } else {
    unknown1fc = 0.0f;
  }
  if (unknowna8 & 0x1000) {
    unknowna8 &= ~0x1000;
    LayerObjUtil::releaseWorldMatrixUniform(uniform);
  } else if (uniform != nullptr) {
    unknowna8 |= 0x1000;
  }
}

void LayerObj::apply(LayerSortMan *sortMan, const LayerRenderView *view) {
  applyPartsSetup();
  updateCtrlSpd(1.0f);
  updateDefPos();
  updateAnimObj();
  if (unknowna8 & 0x10000) {
    unknowna8 |= 0x10000;
    return;
  }
  unknownc5 = m_blendType;
  updateDefSpace(unknown238, static_cast<LAYER_SPACE_TYPE>(m_space), unknown20[unknownc2]);
  LayerResMatrix matrix;
  if (unknowna8 & 0x800) {
    LayerObjUtil::calcLayer3DSpaceTransRotScaleFontMatrix(matrix, m_layerResParmInfo[2].m_layerBasePos, m_layerResRenderInfo);
  } else {
    LayerObjUtil::calcLayerTransRotScaleFontMatrix(matrix, m_layerResParmInfo[2].m_layerBasePos, m_layerResRenderInfo);
  }
  applyParams(view, matrix, m_layerResParmInfo[2].m_layerResColor);
  setDrawList(sortMan, true);
}

void LayerObj::applyBegin(LayerResUpdateInfo &info, const LayerRenderView *view) {
  applyPartsSetup();
  updateCtrlSpd(1.0f);
  updateDefPos();
  updateAnimObj();
  if (!info.unknown50 || (unknowna8 & 0x10000)) {
    unknowna8 |= 0x10000;
    return;
  }
  if (info.unknown54 == LAYER_SPACE_TYPE_UNKNOWN_0) {
    updateDefSpace(unknown238, static_cast<LAYER_SPACE_TYPE>(m_space), unknown20[unknownc2]);
  } else {
    mm::Mat44 matrix;
    matrix.unknown009(unknown20[unknownc2], info.unknown00);
    updateDefSpace(unknown238, info.unknown54, matrix);
  }
  if (m_blendType != 5) {
    unknownc5 = m_blendType;
  } else {
    unknownc5 = info.unknown58;
  }
  if (unknowna8 & 0x800) {
    LayerObjUtil::calcLayer3DSpaceTransRotScaleFontMatrix(m_layerResMatrix, m_layerResParmInfo[2].m_layerBasePos, m_layerResRenderInfo);
  } else {
    LayerObjUtil::calcLayerTransRotScaleFontMatrix(m_layerResMatrix, m_layerResParmInfo[2].m_layerBasePos, m_layerResRenderInfo);
  }
  LayerObjUtil::calcDispInfo(info.m_layerResDispInfo, m_layerResMatrix, m_layerResRenderInfo);
}

void LayerObj::applyEnd(LayerResUpdateInfo &info, const LayerRenderView *view) {
  if (unknowna8 & 0x10000) {
    return;
  }
  LayerResMatrix matrix;
  LayerObjUtil::calcLayerMatrix(matrix, m_layerResMatrix, *info.m_layerResMatrix);
  LayerResColor color;
  LayerObjUtil::calcLayerColor(color, m_layerResParmInfo[2].m_layerResColor, *info.m_layerResColor);
  applyParams(view, matrix, color);
  const LayerObjTopMaskObj *mask = static_cast<const LayerObjTopMaskObj *>(m_maskObj);
  if (mask == nullptr) {
    mask = info.m_layerObjTopMaskObj;
  }
  m_layerObjTopMaskObj = mask;
}

void LayerObj::setPos(f32 x, f32 y) {
  LayerBasePos &pos = m_layerResParmInfo[LayerManager::s_nStkIdx].m_layerBasePos;
  pos.unknown00 = x;
  pos.unknown04 = y;
  onStateFlags(0x2);
}

void LayerObj::setRot(f32 rot) {
  m_layerResParmInfo[LayerManager::s_nStkIdx].m_layerBasePos.unknown08 = rot;
  onStateFlags(0x8);
}

void LayerObj::setScale(f32 x, f32 y) {
  LayerBasePos &pos = m_layerResParmInfo[LayerManager::s_nStkIdx].m_layerBasePos;
  pos.unknown0c = x;
  pos.unknown10 = y;
  onStateFlags(0x4);
}

void LayerObj::setAnchor(f32 x, f32 y) {
  LayerBasePos &pos = m_layerResParmInfo[LayerManager::s_nStkIdx].m_layerBasePos;
  pos.unknown14 = x;
  pos.unknown18 = y;
  onStateFlags(0x10);
}

void LayerObj::setMulCol(const mm::Col4 &color) {
  m_layerResParmInfo[LayerManager::s_nStkIdx].m_layerResColor.m_mulCol = color;
  onStateFlags(0x20);
}

void LayerObj::setAddCol(const mm::Col3 &color) {
  m_layerResParmInfo[LayerManager::s_nStkIdx].m_layerResColor.m_addCol = color;
  onStateFlags(0x40);
}

void LayerObj::setMatrix(const mm::Mat44 &matrix) {
  if (unknownc2) {
    memcpy(&unknown20[0], &matrix, sizeof(mm::Mat44));
  } else {
    memcpy(&unknown20[1], &matrix, sizeof(mm::Mat44));
  }

  onStateFlags(0x40000);
}

void LayerObj::setUVParams(f32 u, f32 v, f32 scaleU, f32 scaleV, f32 rot) {
  unknown023 &uvParam = m_layerResUvParam.unknown00[LayerManager::s_nStkIdx];
  uvParam.unknown00.x = u;
  uvParam.unknown00.y = v;
  uvParam.unknown08 = scaleU;
  uvParam.unknown0c = scaleV;
  uvParam.unknown10 = rot;
  onStateFlags(0x400);
}

void LayerObj::getPos(f32 &x, f32 &y) const {
  const LayerBasePos *pos = getMatrixParm(this, 0x2);
  x = pos->unknown00;
  y = pos->unknown04;
}

void LayerObj::getRot(f32 &rot) const { rot = getMatrixParm(this, 0x8)->unknown08; }

void LayerObj::getScale(f32 &x, f32 &y) const {
  const LayerBasePos *pos = getMatrixParm(this, 0x4);
  x = pos->unknown0c;
  y = pos->unknown10;
}

void LayerObj::getAnchor(f32 &x, f32 &y) const {
  const LayerBasePos *pos = getMatrixParm(this, 0x10);
  x = pos->unknown14;
  y = pos->unknown18;
}

const mm::Mat44 *LayerObj::getMatrix() const {
  if (getStateFlags(LayerManager::s_nStkIdx) & 0x40000) {
    if (unknownc2) {
      return &unknown20[0];
    }
    return &unknown20[1];
  }

  if (unknownc2) {
    return &unknown20[1];
  }
  return &unknown20[0];
}

const mm::Col4 *LayerObj::getMulCol() const { return &getColorParm(this, 0x20)->m_mulCol; }

const mm::Col3 *LayerObj::getAddCol() const { return &getColorParm(this, 0x40)->m_addCol; }

void LayerObj::setDisp(bool disp) {
  if (disp) {
    onStateFlags(0x80);
    offStateFlags(0x100);
  } else {
    onStateFlags(0x100);
    offStateFlags(0x80);
  }
}

bool LayerObj::isClip() const {
  if (m_layerResDispInfo.unknown00 <= 0.0f) {
    return true;
  }
  if (m_layerResDispInfo.unknown04 <= 0.0f) {
    return true;
  }
  if (m_layerResDispInfo.unknown08.x >= 1.0f) {
    return true;
  }
  return m_layerResDispInfo.unknown08.y >= 1.0f;
}

bool LayerObj::isDisp() const { return (unknowna8 & 0x20000) != 0; }

void LayerObj::setFlip(LayerFlipType type, bool flip) {
  if (flip) {
    onStateFlags(0x80000 << type);
    offStateFlags(0x200000 << type);
  } else {
    onStateFlags(0x200000 << type);
    offStateFlags(0x80000 << type);
  }
}

bool LayerObj::isFlip(LayerFlipType type) const { return (unknowna8 & (0x100000 << type)) != 0; }

void LayerObj::createAnimObj(u32 id) {
  if (unknown208[LayerManager::s_nStkIdx] != nullptr) {
    delete unknown208[LayerManager::s_nStkIdx];
    unknown208[LayerManager::s_nStkIdx] = nullptr;
  }

  unknown208[LayerManager::s_nStkIdx] = LayerAnimeObj::createAnimObj(id);
}

void LayerObj::endAnime() { onStateFlags(0x200); }

void LayerObj::createSecondTex(const void *data) {
  onStateFlags(0x1000000);
  unknown220[LayerManager::s_nStkIdx] = new (LayerManager::get()->unknown28) LayerResSecTexture(data);
}

void LayerObj::releaseSecondTex() { onStateFlags(0x1000000); }

const LayerResSecTexture *LayerObj::getSecondTexObj() const {
  LayerResSecTexture *const *secondTex;
  if (unknown220[LayerManager::s_nStkIdx] != nullptr) {
    secondTex = &unknown220[LayerManager::s_nStkIdx];
  } else if (unknown220[LayerManager::s_nDebIdx] != nullptr) {
    secondTex = &unknown220[LayerManager::s_nDebIdx];
  } else {
    secondTex = &unknown220[2];
  }

  return *secondTex;
}

u16 LayerObj::getSecondTexIconMax() const {
  const LayerResSecTexture *secondTex = getSecondTexObj();
  if (secondTex != nullptr) {
    return secondTex->unknown12;
  }

  return 0;
}

void LayerObj::setSecondTexIconNum(u32 num) {
  LayerResSecTexture *secondTex = const_cast<LayerResSecTexture *>(getSecondTexObj());
  if (secondTex != nullptr) {
    secondTex->unknown10 = num;
  }
}

u16 LayerObj::getSecondTexIconNum() const {
  const LayerResSecTexture *secondTex = getSecondTexObj();
  if (secondTex != nullptr) {
    return secondTex->unknown10;
  }

  return 0;
}

void LayerObj::setSecondTexBlend(f32 blend) {
  LayerResSecTexture *secondTex = const_cast<LayerResSecTexture *>(getSecondTexObj());
  if (secondTex != nullptr) {
    secondTex->unknown14 = blend;
  }
}

f32 LayerObj::getSecondTexBlend() const {
  const LayerResSecTexture *secondTex = getSecondTexObj();
  if (secondTex != nullptr) {
    return secondTex->unknown14;
  }

  return 0.0f;
}

LayerActBase::LayerActBase() : unknown250(nullptr) {}

void LayerActBase::updatePartsAction(const LyrActionData *action) {}

void LayerActBase::updateAction() {
  if (unknown250 == nullptr) {
    return;
  }
  if (getStateFlags(LayerManager::s_nDebIdx) & 0x30000) {
    if (getStateFlags(LayerManager::s_nDebIdx) & 0x10000) {
      unknown250->unknown20 = unknown1d8[LayerManager::s_nDebIdx];
      if (static_cast<s32>(unknown250->unknown20) >= unknown250->unknown10) {
        unknowna8 &= ~0x40;
        return;
      }
      startSetupAction();
      unknowna8 |= 0x40;
    } else if (getStateFlags(LayerManager::s_nDebIdx) & 0x20000) {
      unknowna8 &= ~0x40;
      return;
    }
  }
  if (unknowna8 & 0x40) {
    f32 delta = LayerManager::get()->unknown80 * unknown1f8;
    if (unknowna8 & 0x200) {
      delta = 0.0f;
    }
    const LyrActionData *action = unknown250->m_lyrActionData + unknown250->unknown20;
    unknown250->unknown18 = delta;
    if (delta > 0.0001f) {
      unknown250->unknown1c = 1.0f / delta;
    } else {
      unknown250->unknown1c = 0.0f;
    }
    updatePartsAction(action);
    if (unknown250->unknown14 > action->unknown18) {
      unknown250->unknown14 = action->unknown18;
    }
    if (unknown1f8 != 0.0f) {
      unknown250->unknown14 = delta + unknown250->unknown14;
    }
    unknown250->unknown24 &= ~1;
  }
}

void LayerActBase::setupAction(u8 *work, const u8 *data) {
  const unknown083 *header = reinterpret_cast<const unknown083 *>(data);
  unknown250 = reinterpret_cast<unknown084 *>(work);
  unknown250->unknown00 = data;
  unknown250->unknown28 = reinterpret_cast<u32 *>(work + sizeof(unknown084));
  unknown250->unknown10 = header->unknown08;
  unknown250->m_lyrActionData = reinterpret_cast<const LyrActionData *>(data + header->unknown04);
  unknown250->unknown14 = 0.0f;
  unknown250->unknown20 = 0;
  unknown250->unknown24 = 0;
  if (header->actionNum != 0) {
    memset(unknown250->unknown28, 0, header->actionNum * sizeof(u32));
  }
  if (!(header->unknown00 & 1)) {
    return;
  }
  unknown250->unknown24 |= 1;
  unknown250->unknown14 = 0.0f;
  const LyrActionData &action = *(unknown250->m_lyrActionData + unknown250->unknown20);
  if (action.unknown00 & 0x7e) {
    if (action.unknown00 & 0x2) {
      unknowna8 |= 0x80;
    } else if (action.unknown00 & 0x4) {
      unknowna8 &= ~0x80;
    }
    if (action.unknown00 & 0x8) {
      unknowna8 |= 0x20000;
    } else if (action.unknown00 & 0x10) {
      unknowna8 &= ~0x20000;
    }
    if (action.unknown00 & 0x20) {
      unknowna8 |= 0x200;
    } else if (action.unknown00 & 0x40) {
      unknowna8 &= ~0x200;
    }
  }
  unknowna8 |= 0x40;
  unknown250->unknown20 = header->unknown10;
  unknown250->unknown24 |= 1;
  unknown250->unknown14 = 0.0f;
}

void LayerActBase::startSetupAction() {
  unknown250->unknown24 |= 1;
  unknown250->unknown14 = 0.0f;
  const LyrActionData &action = *(unknown250->m_lyrActionData + unknown250->unknown20);
  if ((action.unknown00 & 0x7e) == 0) {
    return;
  }
  if (action.unknown00 & 0x2) {
    unknowna8 |= 0x80;
  } else if (action.unknown00 & 0x4) {
    unknowna8 &= ~0x80;
  }
  if (action.unknown00 & 0x8) {
    unknowna8 |= 0x20000;
  } else if (action.unknown00 & 0x10) {
    unknowna8 &= ~0x20000;
  }
  if (action.unknown00 & 0x20) {
    unknowna8 |= 0x200;
  } else if (action.unknown00 & 0x40) {
    unknowna8 &= ~0x200;
  }
}

void LayerActBase::checkActionEnd(const LyrActionData *action, bool isCmdEnd) {
  if (unknown250->unknown18 == 0.0f) {
    return;
  }
  const LyrActionData *actions = unknown250->m_lyrActionData;
  u32 index = unknown250->unknown20;
  const LyrActionData &current = actions[index];
  if (!(this->*s_pCallActEnd[current.unknown06])(&current, isCmdEnd)) {
    return;
  }
  if (!(current.unknown00 & 1)) {
    unknowna8 &= ~0x40;
    return;
  }
  unknown250->unknown14 = 0.0f;
  unknown250->unknown20 = actions[index].unknown04;
}

u32 LayerActBase::calcActionWorkSize(const u8 *data) { return sizeof(unknown084) + reinterpret_cast<const unknown083 *>(data)->actionNum * sizeof(u32); }

void LayerActBase::actionIdx(u32 index) {
  onStateFlags(0x10000);
  unknown1d8[LayerManager::s_nStkIdx] = index;
}

void LayerActBase::actionEnd() { onStateFlags(0x20000); }

bool LayerActBase::actcmd_no(const u8 *&cmd) {
  cmd += 4;
  return false;
}

bool LayerActBase::actcmd_rot(const u8 *&cmd) {
  bool result = true;
  if (unknown250->unknown18 != 0.0f) {
    const f32 *parm = reinterpret_cast<const f32 *>(reinterpret_cast<const unknown020 *>(cmd) + 1);
    f32 rot;
    if (parm[1] <= unknown250->unknown14) {
      rot = parm[0];
      result = false;
    } else {
      f32 rate = 1.0f / ((parm[1] - unknown250->unknown14) * unknown250->unknown1c);
      if (rate > 1.0f) {
        rate = 1.0f;
      }
      rot = m_layerResParmInfo[2].m_layerBasePos.unknown08 + (parm[0] - m_layerResParmInfo[2].m_layerBasePos.unknown08) * rate;
    }
    setInitRot(rot);
  }
  cmd += sizeof(unknown020) + 2 * sizeof(f32);
  return result;
}

bool LayerActBase::actcmd_numrot(const u8 *&cmd) {
  bool result = true;
  f32 delta = unknown250->unknown18;
  if (delta != 0.0f) {
    const f32 *parm = reinterpret_cast<const f32 *>(reinterpret_cast<const unknown020 *>(cmd) + 1);
    result = !(parm[1] <= unknown250->unknown14);
    setInitRot(fmodf(m_layerResParmInfo[2].m_layerBasePos.unknown08 + delta * parm[0], 6.2831855f));
  }
  cmd += sizeof(unknown020) + 2 * sizeof(f32);
  return result;
}

bool LayerActBase::actcmd_priority(const u8 *&cmd) {
  m_priority = *reinterpret_cast<const u16 *>(cmd + 2);
  cmd += 4;
  return false;
}

bool LayerActBase::actcmd_wait(const u8 *&cmd) {
  const u8 *data = cmd;
  cmd += 8;
  return !(*reinterpret_cast<const f32 *>(data + 4) <= unknown250->unknown14);
}

bool LayerActBase::actcmd_ctrlspd(const u8 *&cmd) {
  m_ctrlSpd = *reinterpret_cast<const f32 *>(cmd + 4);
  cmd += 8;
  return false;
}

bool LayerActBase::actend_no(const LyrActionData *action, bool isCmdEnd) { return false; }

bool LayerActBase::actend_cmdend(const LyrActionData *action, bool isCmdEnd) { return !isCmdEnd; }

bool LayerActBase::actend_on(const LyrActionData *action, bool isCmdEnd) { return true; }

} // namespace layer

// The game builds these files in one unit with this one, in this order.
// clang-format off
#include "layer_act_def.cpp"
#include "layer_act_layout.cpp"
#include "layer_obj_draw.cpp"
#include "layer_obj_font.cpp"
#include "layer_obj_layout.cpp"
#include "layer_obj_list.cpp"
#include "layer_obj_manager.cpp"
#include "layer_obj_mesh.cpp"
#include "layer_obj_place.cpp"
#include "layer_obj_top_def.cpp"
#include "layer_obj_top_font.cpp"
#include "layer_obj_top_layout.cpp"
#include "layer_obj_top_mem_obj.cpp"
#include "layer_obj_top_tex_obj.cpp"
#include "layer_obj_top_poly_obj.cpp"
#include "layer_obj_top_filter.cpp"
#include "layer_obj_top_mask_obj.cpp"
#include "layer_obj_sort.cpp"
#include "layer_obj_util.cpp"
#include "layer_obj_res_tex.cpp"
#include "layer_obj_work.cpp"
// clang-format on
