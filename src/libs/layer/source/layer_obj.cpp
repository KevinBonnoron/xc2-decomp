#include "layer/layer_obj.h"

#include <string.h>

#include "layer/layer_act_base.h"

#include "layer/layer_anime_obj.h"
#include "layer/layer_manager.h"
#include "layer/layer_res_sec_texture.h"
#include "mtl/alloc_handle.h"

namespace layer {

namespace {

const LayerResMatrix *getMatrixParm(const LayerObj *layer, u32 flag) {
  if (layer->getStateFlags(LayerManager::s_nStkIdx) & flag) {
    return &layer->m_parms[LayerManager::s_nStkIdx].matrix;
  }

  if (layer->getStateFlags(LayerManager::s_nDebIdx) & flag) {
    return &layer->m_parms[LayerManager::s_nDebIdx].matrix;
  }

  return &layer->m_parms[2].matrix;
}

const LayerResColor *getColorParm(const LayerObj *layer, u32 flag) {
  if (layer->getStateFlags(LayerManager::s_nStkIdx) & flag) {
    return &layer->m_parms[LayerManager::s_nStkIdx].color;
  }

  if (layer->getStateFlags(LayerManager::s_nDebIdx) & flag) {
    return &layer->m_parms[LayerManager::s_nDebIdx].color;
  }

  return &layer->m_parms[2].color;
}

} // namespace

void LayerObj::setInitPos(f32 x, f32 y) {
  m_parms[1].matrix.posX = x;
  m_parms[0].matrix.posX = x;
  m_parms[2].matrix.posX = x;
  m_parms[1].matrix.posY = y;
  m_parms[0].matrix.posY = y;
  m_parms[2].matrix.posY = y;
}

void LayerObj::setInitRot(f32 rot) {
  m_parms[1].matrix.rot = rot;
  m_parms[0].matrix.rot = rot;
  m_parms[2].matrix.rot = rot;
}

void LayerObj::setInitScl(f32 x, f32 y) {
  m_parms[1].matrix.sclX = x;
  m_parms[0].matrix.sclX = x;
  m_parms[2].matrix.sclX = x;
  m_parms[1].matrix.sclY = y;
  m_parms[0].matrix.sclY = y;
  m_parms[2].matrix.sclY = y;
}

void LayerObj::updateCtrlSpd(f32 speed) {
  u32 &flags = m_stateFlags[static_cast<u32>(LayerManager::s_nDebIdx)];
  if (flags & 0xf000) {
    if (flags & 0x1000) {
      m_flags |= 0x200;
    } else if (flags & 0x2000) {
      m_flags &= ~0x200;
    }

    if (flags & 0x4000) {
      m_flags |= 0x80;
    } else if (flags & 0x8000) {
      m_flags &= ~0x80;
    }
  }

  m_frameCtrlSpd = m_ctrlSpd * speed;
}

void LayerObj::updateSecondTex() {
  if (m_secondTexs[2] != nullptr) {
    m_secondTexs[2]->update();
  }
}

void LayerObj::setPos(f32 x, f32 y) {
  LayerResMatrix &matrix = m_parms[LayerManager::s_nStkIdx].matrix;
  matrix.posX = x;
  matrix.posY = y;
  onStateFlags(0x2);
}

void LayerObj::setRot(f32 rot) {
  m_parms[LayerManager::s_nStkIdx].matrix.rot = rot;
  onStateFlags(0x8);
}

void LayerObj::setScale(f32 x, f32 y) {
  LayerResMatrix &matrix = m_parms[LayerManager::s_nStkIdx].matrix;
  matrix.sclX = x;
  matrix.sclY = y;
  onStateFlags(0x4);
}

void LayerObj::setAnchor(f32 x, f32 y) {
  LayerResMatrix &matrix = m_parms[LayerManager::s_nStkIdx].matrix;
  matrix.anchorX = x;
  matrix.anchorY = y;
  onStateFlags(0x10);
}

void LayerObj::setMulCol(const mm::Col4 &color) {
  m_parms[LayerManager::s_nStkIdx].color.mulCol = color;
  onStateFlags(0x20);
}

void LayerObj::setAddCol(const mm::Col3 &color) {
  m_parms[LayerManager::s_nStkIdx].color.addCol = color;
  onStateFlags(0x40);
}

void LayerObj::setMatrix(const mm::Mat44 &matrix) {
  if (m_matrixIdx) {
    memcpy(&m_matrices[0], &matrix, sizeof(mm::Mat44));
  } else {
    memcpy(&m_matrices[1], &matrix, sizeof(mm::Mat44));
  }

  onStateFlags(0x40000);
}

void LayerObj::setUVParams(f32 u, f32 v, f32 scaleU, f32 scaleV, f32 rot) {
  LayerResUvParam &uvParam = m_uvParams[LayerManager::s_nStkIdx];
  uvParam.u = u;
  uvParam.v = v;
  uvParam.scaleU = scaleU;
  uvParam.scaleV = scaleV;
  uvParam.rot = rot;
  onStateFlags(0x400);
}

void LayerObj::getPos(f32 &x, f32 &y) const {
  const LayerResMatrix *matrix = getMatrixParm(this, 0x2);
  x = matrix->posX;
  y = matrix->posY;
}

void LayerObj::getRot(f32 &rot) const { rot = getMatrixParm(this, 0x8)->rot; }

void LayerObj::getScale(f32 &x, f32 &y) const {
  const LayerResMatrix *matrix = getMatrixParm(this, 0x4);
  x = matrix->sclX;
  y = matrix->sclY;
}

void LayerObj::getAnchor(f32 &x, f32 &y) const {
  const LayerResMatrix *matrix = getMatrixParm(this, 0x10);
  x = matrix->anchorX;
  y = matrix->anchorY;
}

const mm::Col4 *LayerObj::getMulCol() const { return &getColorParm(this, 0x20)->mulCol; }

const mm::Col3 *LayerObj::getAddCol() const { return &getColorParm(this, 0x40)->addCol; }

void LayerObj::setDisp(bool disp) {
  if (disp) {
    onStateFlags(0x80);
    offStateFlags(0x100);
  } else {
    onStateFlags(0x100);
    offStateFlags(0x80);
  }
}

bool LayerObj::isDisp() const { return (m_flags & 0x20000) != 0; }

void LayerObj::setFlip(LayerFlipType type, bool flip) {
  if (flip) {
    onStateFlags(0x80000 << type);
    offStateFlags(0x200000 << type);
  } else {
    onStateFlags(0x200000 << type);
    offStateFlags(0x80000 << type);
  }
}

bool LayerObj::isFlip(LayerFlipType type) const { return (m_flags & (0x100000 << type)) != 0; }

void LayerObj::createAnimObj(u32 id) {
  if (m_animObjs[LayerManager::s_nStkIdx] != nullptr) {
    delete m_animObjs[LayerManager::s_nStkIdx];
    m_animObjs[LayerManager::s_nStkIdx] = nullptr;
  }

  m_animObjs[LayerManager::s_nStkIdx] = LayerAnimeObj::createAnimObj(id);
}

void LayerObj::endAnime() { onStateFlags(0x200); }

void LayerObj::createSecondTex(const void *data) {
  onStateFlags(0x1000000);
  m_secondTexs[LayerManager::s_nStkIdx] = new (LayerManager::get()->m_workMem) LayerResSecTexture(data);
}

void LayerObj::releaseSecondTex() { onStateFlags(0x1000000); }

const LayerResSecTexture *LayerObj::getSecondTexObj() const {
  LayerResSecTexture *const *secondTex;
  if (m_secondTexs[LayerManager::s_nStkIdx] != nullptr) {
    secondTex = &m_secondTexs[LayerManager::s_nStkIdx];
  } else if (m_secondTexs[LayerManager::s_nDebIdx] != nullptr) {
    secondTex = &m_secondTexs[LayerManager::s_nDebIdx];
  } else {
    secondTex = &m_secondTexs[2];
  }

  return *secondTex;
}

u16 LayerObj::getSecondTexIconMax() const {
  const LayerResSecTexture *secondTex = getSecondTexObj();
  if (secondTex != nullptr) {
    return secondTex->m_iconMax;
  }

  return 0;
}

void LayerObj::setSecondTexIconNum(u32 num) {
  LayerResSecTexture *secondTex = const_cast<LayerResSecTexture *>(getSecondTexObj());
  if (secondTex != nullptr) {
    secondTex->m_iconNum = num;
  }
}

u16 LayerObj::getSecondTexIconNum() const {
  const LayerResSecTexture *secondTex = getSecondTexObj();
  if (secondTex != nullptr) {
    return secondTex->m_iconNum;
  }

  return 0;
}

void LayerObj::setSecondTexBlend(f32 blend) {
  LayerResSecTexture *secondTex = const_cast<LayerResSecTexture *>(getSecondTexObj());
  if (secondTex != nullptr) {
    secondTex->m_blend = blend;
  }
}

f32 LayerObj::getSecondTexBlend() const {
  const LayerResSecTexture *secondTex = getSecondTexObj();
  if (secondTex != nullptr) {
    return secondTex->m_blend;
  }

  return 0.0f;
}

void LayerActBase::startSetupAction() {
  m_actWork->flags |= 1;
  m_actWork->sec = 0.0f;
  const LyrActionData &action = *(m_actWork->actions + m_actWork->actionIdx);
  if ((action.flags & 0x7e) == 0) {
    return;
  }
  if (action.flags & 0x2) {
    m_flags |= 0x80;
  } else if (action.flags & 0x4) {
    m_flags &= ~0x80;
  }
  if (action.flags & 0x8) {
    m_flags |= 0x20000;
  } else if (action.flags & 0x10) {
    m_flags &= ~0x20000;
  }
  if (action.flags & 0x20) {
    m_flags |= 0x200;
  } else if (action.flags & 0x40) {
    m_flags &= ~0x200;
  }
}

void LayerActBase::checkActionEnd(const LyrActionData *action, bool isCmdEnd) {
  if (m_actWork->deltaSec == 0.0f) {
    return;
  }
  const LyrActionData *actions = m_actWork->actions;
  u32 index = m_actWork->actionIdx;
  const LyrActionData &current = actions[index];
  if (!(this->*s_pCallActEnd[current.endType])(&current, isCmdEnd)) {
    return;
  }
  if (!(current.flags & 1)) {
    m_flags &= ~0x40;
    return;
  }
  m_actWork->sec = 0.0f;
  m_actWork->actionIdx = actions[index].nextIdx;
}

u32 LayerActBase::calcActionWorkSize(const u8 *data) {
  return sizeof(LayerActWork) + reinterpret_cast<const LyrActionHeader *>(data)->actionNum * sizeof(u32);
}

void LayerActBase::actionIdx(u32 index) {
  onStateFlags(0x10000);
  m_actionIdx[LayerManager::s_nStkIdx] = index;
}

void LayerActBase::actionEnd() { onStateFlags(0x20000); }

bool LayerActBase::actcmd_no(const u8 *&cmd) {
  cmd += 4;
  return false;
}

bool LayerActBase::actcmd_priority(const u8 *&cmd) {
  m_priority = *reinterpret_cast<const u16 *>(cmd + 2);
  cmd += 4;
  return false;
}

bool LayerActBase::actcmd_wait(const u8 *&cmd) {
  const u8 *data = cmd;
  cmd += 8;
  return !(*reinterpret_cast<const f32 *>(data + 4) <= m_actWork->sec);
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
