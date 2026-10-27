#include "layer/layer_obj.h"

#include <string.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "layer/layer_act_base.h"
#include "layer/layer_anime_obj.h"
#include "layer/layer_manager.h"
#include "layer/layer_res_sec_texture.h"
#include "mtl/alloc_handle.h"

namespace layer {

namespace {

const LayerResMatrix *getMatrixParm(const LayerObj *layer, u32 flag) {
  if (layer->getStateFlags(LayerManager::s_nStkIdx) & flag) {
    return &layer->unknownc8[LayerManager::s_nStkIdx].unknown00;
  }

  if (layer->getStateFlags(LayerManager::s_nDebIdx) & flag) {
    return &layer->unknownc8[LayerManager::s_nDebIdx].unknown00;
  }

  return &layer->unknownc8[2].unknown00;
}

const LayerResColor *getColorParm(const LayerObj *layer, u32 flag) {
  if (layer->getStateFlags(LayerManager::s_nStkIdx) & flag) {
    return &layer->unknownc8[LayerManager::s_nStkIdx].unknown1c;
  }

  if (layer->getStateFlags(LayerManager::s_nDebIdx) & flag) {
    return &layer->unknownc8[LayerManager::s_nDebIdx].unknown1c;
  }

  return &layer->unknownc8[2].unknown1c;
}

} // namespace

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
  unknownc8[1].unknown00.unknown00 = x;
  unknownc8[0].unknown00.unknown00 = x;
  unknownc8[2].unknown00.unknown00 = x;
  unknownc8[1].unknown00.unknown04 = y;
  unknownc8[0].unknown00.unknown04 = y;
  unknownc8[2].unknown00.unknown04 = y;
}

void LayerObj::setInitRot(f32 rot) {
  unknownc8[1].unknown00.unknown08 = rot;
  unknownc8[0].unknown00.unknown08 = rot;
  unknownc8[2].unknown00.unknown08 = rot;
}

void LayerObj::setInitScl(f32 x, f32 y) {
  unknownc8[1].unknown00.unknown0c = x;
  unknownc8[0].unknown00.unknown0c = x;
  unknownc8[2].unknown00.unknown0c = x;
  unknownc8[1].unknown00.unknown10 = y;
  unknownc8[0].unknown00.unknown10 = y;
  unknownc8[2].unknown00.unknown10 = y;
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

  unknown1f8 = unknown1f4 * speed;
}

void LayerObj::updateAnimObj() {
  if (unknown208[2] != nullptr) {
    f32 frame = unknown1f8 * LayerManager::get()->unknown80;
    if (unknowna8 & 0x200) {
      frame = 0.0f;
    }

    if (unknown208[2]->update(unknownc8[2], frame) && unknown208[2] != nullptr) {
      delete unknown208[2];
      unknown208[2] = nullptr;
    }
  }

  if (unknownc8[2].unknown1c.unknown00.a <= 0.0f && unknown18 != LAYER_OBJ_TYPE_MASK) {
    unknowna8 |= 0x80000;
  }
}

void LayerObj::updateSecondTex() {
  if (unknown220[2] != nullptr) {
    unknown220[2]->update();
  }
}

void LayerObj::setPos(f32 x, f32 y) {
  LayerResMatrix &matrix = unknownc8[LayerManager::s_nStkIdx].unknown00;
  matrix.unknown00 = x;
  matrix.unknown04 = y;
  onStateFlags(0x2);
}

void LayerObj::setRot(f32 rot) {
  unknownc8[LayerManager::s_nStkIdx].unknown00.unknown08 = rot;
  onStateFlags(0x8);
}

void LayerObj::setScale(f32 x, f32 y) {
  LayerResMatrix &matrix = unknownc8[LayerManager::s_nStkIdx].unknown00;
  matrix.unknown0c = x;
  matrix.unknown10 = y;
  onStateFlags(0x4);
}

void LayerObj::setAnchor(f32 x, f32 y) {
  LayerResMatrix &matrix = unknownc8[LayerManager::s_nStkIdx].unknown00;
  matrix.unknown14 = x;
  matrix.unknown18 = y;
  onStateFlags(0x10);
}

void LayerObj::setMulCol(const mm::Col4 &color) {
  unknownc8[LayerManager::s_nStkIdx].unknown1c.unknown00 = color;
  onStateFlags(0x20);
}

void LayerObj::setAddCol(const mm::Col3 &color) {
  unknownc8[LayerManager::s_nStkIdx].unknown1c.unknown10 = color;
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
  LayerResUvParam &uvParam = unknown19c[LayerManager::s_nStkIdx];
  uvParam.unknown00 = u;
  uvParam.unknown04 = v;
  uvParam.unknown08 = scaleU;
  uvParam.unknown0c = scaleV;
  uvParam.unknown10 = rot;
  onStateFlags(0x400);
}

void LayerObj::getPos(f32 &x, f32 &y) const {
  const LayerResMatrix *matrix = getMatrixParm(this, 0x2);
  x = matrix->unknown00;
  y = matrix->unknown04;
}

void LayerObj::getRot(f32 &rot) const { rot = getMatrixParm(this, 0x8)->unknown08; }

void LayerObj::getScale(f32 &x, f32 &y) const {
  const LayerResMatrix *matrix = getMatrixParm(this, 0x4);
  x = matrix->unknown0c;
  y = matrix->unknown10;
}

void LayerObj::getAnchor(f32 &x, f32 &y) const {
  const LayerResMatrix *matrix = getMatrixParm(this, 0x10);
  x = matrix->unknown14;
  y = matrix->unknown18;
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

const mm::Col4 *LayerObj::getMulCol() const { return &getColorParm(this, 0x20)->unknown00; }

const mm::Col3 *LayerObj::getAddCol() const { return &getColorParm(this, 0x40)->unknown10; }

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
  if (unknown170 <= 0.0f) {
    return true;
  }
  if (unknown174 <= 0.0f) {
    return true;
  }
  if (unknown178 >= 1.0f) {
    return true;
  }
  return unknown17c >= 1.0f;
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

void LayerActBase::updatePartsAction(const LyrActionData *action) {}

void LayerActBase::setupAction(u8 *work, const u8 *data) {
  const LyrActionHeader *header = reinterpret_cast<const LyrActionHeader *>(data);
  unknown250 = reinterpret_cast<LayerActWork *>(work);
  unknown250->unknown00 = data;
  unknown250->unknown28 = reinterpret_cast<u32 *>(work + sizeof(LayerActWork));
  unknown250->unknown10 = header->unknown08;
  unknown250->unknown08 = reinterpret_cast<const LyrActionData *>(data + header->unknown04);
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
  const LyrActionData &action = *(unknown250->unknown08 + unknown250->unknown20);
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
  const LyrActionData &action = *(unknown250->unknown08 + unknown250->unknown20);
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
  const LyrActionData *actions = unknown250->unknown08;
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

u32 LayerActBase::calcActionWorkSize(const u8 *data) { return sizeof(LayerActWork) + reinterpret_cast<const LyrActionHeader *>(data)->actionNum * sizeof(u32); }

void LayerActBase::actionIdx(u32 index) {
  onStateFlags(0x10000);
  unknown1d8[LayerManager::s_nStkIdx] = index;
}

void LayerActBase::actionEnd() { onStateFlags(0x20000); }

bool LayerActBase::actcmd_no(const u8 *&cmd) {
  cmd += 4;
  return false;
}

bool LayerActBase::actcmd_priority(const u8 *&cmd) {
  unknownc0 = *reinterpret_cast<const u16 *>(cmd + 2);
  cmd += 4;
  return false;
}

bool LayerActBase::actcmd_wait(const u8 *&cmd) {
  const u8 *data = cmd;
  cmd += 8;
  return !(*reinterpret_cast<const f32 *>(data + 4) <= unknown250->unknown14);
}

bool LayerActBase::actcmd_ctrlspd(const u8 *&cmd) {
  unknown1f4 = *reinterpret_cast<const f32 *>(cmd + 4);
  cmd += 8;
  return false;
}

bool LayerActBase::actend_no(const LyrActionData *action, bool isCmdEnd) { return false; }

bool LayerActBase::actend_cmdend(const LyrActionData *action, bool isCmdEnd) { return !isCmdEnd; }

bool LayerActBase::actend_on(const LyrActionData *action, bool isCmdEnd) { return true; }

} // namespace layer
