#include "dr/dr_calc_stm_list_obj.h"

#include "dr/dr_calc_tex_stream_man.h"
#include "dr/dr_man.h"
#include "grlib/cglib_texture.h"
#include "grlib/cglib_texture_buffer.h"
#include "ml/critical_section.h"
#include "ml/dev_file_th.h"
#include "mtl/mem_manager.h"

namespace ml {

DrCalcStmListObj::~DrCalcStmListObj() {
  if (unknown40 != nullptr) {
    DevFileTh::cancel(unknown40, false);
  }
  unknown40 = nullptr;
  chacheTexClear();
  unknownb0.workRelease();
  chacheDefClear();
  DrCalcTexStreamMan::get()->releaseFreeObj(unknown48);
  DrCalcTexStreamMan::get()->releaseFreeObj(unknown50);
  unknowna0 = 0;
  if (unknown20 != nullptr) {
    mtl::MemManager::deallocate(unknown20, 0, false);
    unknown20 = nullptr;
  }
}

void DrCalcStmListObj::initInfo() {
  unknown80 = 0;
  unknowncc[1] = 0;
  unknownc8 = 0;
  unknowncc[0] = 0;
  unknownaa = 0;
  unknown58 = 0;
  unknown40 = nullptr;
  unknown70 = 0;
  unknown72 = 0;
  unknown74 = 0;
  unknown76 = 0;
  unknown78 = 0;
  unknown7a = 0;
  unknown7c = 0;
  unknown9c = 0;
  unknowna0 = 0;
  unknowna2 = 0;
  unknowna4 = 0;
  unknowna6 = 0;
  unknown200 = nullptr;
  unknown18 = nullptr;
  unknown20 = nullptr;
  unknown48 = nullptr;
  unknown50 = nullptr;
  unknown1f0 = nullptr;
  unknown1e0 = nullptr;
}

bool DrCalcStmListObj::texstm_size_alloc() {
  unknown88 = 0xe;
  unknown48 = DrCalcTexStreamMan::get()->createSizeModeFreeObj(unknown9c);
  if (unknown48 == nullptr) {
    DrCalcTexStreamMan *man = DrCalcTexStreamMan::get();
    man->unknown2068 |= 0x20;
    man->unknown248c = 0xa0;
    man->unknown248e = 0xa;
    man->unknown2488 += unknown9c;
  } else {
    unknown1e0 = &DrCalcStmListObj::texstm_size_Wait;
    unknown48->unknown24 |= 0x428;
  }
  return 0;
}

void DrCalcStmListObj::chacheTexClear() {
  for (u32 i = unknown7a; i < unknown7c; i++) {
    DrCalcTexStmObj **objects = unknown28;
    DrCalcTexStmObj *object = objects[i];
    if (object != nullptr) {
      DrCalcTexStreamMan::get()->clearMemObj(object);
      objects[i] = nullptr;
    }
  }
  unknownb0.texRelease();
  unknown80 &= ~0x70u;
  unknown98 = 0;
}

void DrCalcStmListObj::release() {
  CS lock(DrCalcTexStreamMan::getCriticalSection());
  unknowna6--;
  if (unknowna6 < 0) {
    unknowna6 = 0;
  }
}

void DrCalcStmListObj::updateHeaderInfo() {
  if (!(unknown80 & (0x10000000 << DrMan::s_nDblStockIdx)) || unknowna6 != 0) {
    if ((unknown80 & 0x10006002) != 0x6000) {
      return;
    }
    setupInfo(unknown50->unknown18, true);
    unknown80 &= ~0x6000u;
  } else {
    unknown80 |= 0x10000000;
  }
}

void DrCalcStmListObj::setHeaderInfo(const u8 *header) {
  if (unknown80 & 0x2000) {
    setupInfo(header, true);
    unknown80 &= ~0x6000;
  }
}

unknown035 *DrCalcStmListObj::getResObj(u32 index) { return unknown30[DrMan::s_nDblStockIdx] + index; }

unknown035 *DrCalcStmListObj::getResVertexObj() { return &unknown30[DrMan::s_nDblStockIdx][unknown74]; }

unknown035 *DrCalcStmListObj::getResShaderObj() { return &unknown30[DrMan::s_nDblStockIdx][unknown76]; }

bool DrCalcStmListObj::isResChange() const { return (unknown80 & (0x400000 << DrMan::s_nDblStockIdx)) != 0; }

bool DrCalcStmListObj::isResSub() const { return (unknown80 & (0x40000 << DrMan::s_nDblStockIdx)) != 0; }

bool DrCalcStmListObj::isResTex() const { return (unknown80 & (0x100000 << DrMan::s_nDblStockIdx)) != 0; }

void DrCalcStmListObj::setUseMode(DrTexUseMode mode) {
  s32 index = DrMan::s_nDblStockIdx;
  if (unknowncc[index] <= mode) {
    unknown80 |= 0x1000000 << index;
    unknowncc[index] = mode;
  }
}

grlib::CGLibTextureBuffer *DrCalcStmListObj::getTexObj(u32 index) { return unknownb0.getTexObj(index); }

void *DrCalcStmListObj::getAdder() {
  if ((unknown80 & 0x10000) == 0) {
    return nullptr;
  }
  if (unknown48 != nullptr) {
    return unknown48->unknown18;
  }
  return nullptr;
}

unknown035 *DrCalcStmListObj::getResLowTexObj() { return &unknown30[DrMan::s_nDblStockIdx][unknown78]; }

bool DrCalcStmListObj::texstm_requestWait() {
  unknown88 = 0x13;
  unknownaa--;
  if (unknownaa < 1) {
    unknown1e0 = unknown200;
  }
  return 0;
}

bool DrCalcStmListObj::texstm_size_Wait() {
  unknown88 = 0xf;
  return 0;
}

void DrCalcStmListObj::setupReadCheck() {
  if (unknown50 != nullptr) {
    DrCalcTexStreamMan::get()->clearMemObj(unknown50);
    unknown50 = nullptr;
  }
  unknown1e0 = unknown1f0;
  unknown80 |= 0x8000;
}

bool DrCalcStmListObj::texstm_notfileWait() {
  unknown88 = 0x13;
  unknown80 |= 0x1000;
  if (!(unknown80 & 0x2000)) {
    setupReadCheck();
  }
  return 0;
}

bool DrCalcStmListObj::texstm_oldVerWait() {
  unknown88 = 4;
  if (!(unknown80 & 0x2000)) {
    setupReadCheck();
  }
  return 0;
}

bool DrCalcStmListObj::texstm_stmchk_setWait() {
  unknown88 = 3;
  if (!(unknown80 & 0x2000)) {
    setupReadCheck();
  }
  return 0;
}

bool DrCalcStmListObj::texstm_defErrWait() {
  unknown88 = 7;
  DrCalcTexStreamMan *man = DrCalcTexStreamMan::get();
  man->unknown2488 += unknown84;
  unknowna8++;
  if (unknowna8 > 0x3b) {
    unknowna8 = 0;
    unknown1e0 = &DrCalcStmListObj::texstm_defRead;
    return 1;
  }
  return 0;
}

void DrCalcStmListObj::chacheDefClear() {
  for (s32 i = 0; i < unknowna2; i++) {
    DrCalcTexStmObj **objects = unknown28;
    DrCalcTexStmObj *object = objects[i];
    if (object != nullptr) {
      DrCalcTexStreamMan::get()->clearMemObj(object);
      objects[i] = nullptr;
    }
  }
  unknown80 &= ~8u;
  unknown94 = 0;
}

void DrCalcStmListObj::update() {
  if (unknown80 & (0x1000000 << DrMan::s_nDblIdx)) {
    s32 index = DrMan::s_nDblIdx;
    s32 mode = unknowncc[index];
    unknown80 &= ~(0x1000000 << index);
    unknownc8 = mode;
    unknowncc[index] = 0;
  }
  if (unknowna6 == 0) {
    unknownc8 = 0;
  }
  while ((this->*unknown1e0)()) {
  }
}

void DrCalcStmListObj::callUpdate(DrStmListAfterArg &arg) {
  if (!(unknown80 & 2) && (unknowna6 == 0 || unknownc8 == 0) && arg.unknown01) {
    if (unknown8c < 0x708) {
      unknown8c = 0x707;
    }
    if (unknown8e < 0xe10) {
      unknown8e = 0xe0f;
    }
    arg.unknown036(unknown98);
    arg.unknown036(unknown94);
  }
}

bool DrCalcStmListObj::texstm_defMidtexErrWait() {
  unknown88 = 10;
  DrCalcTexStreamMan *man = DrCalcTexStreamMan::get();
  man->unknown2488 += unknown84;
  unknowna8++;
  if (unknowna8 > 0x3b) {
    unknowna8 = 0;
    unknown1e0 = &DrCalcStmListObj::texstm_deTexCheck;
    return 1;
  }
  return 0;
}

bool DrCalcStmListObj::texstm_fastErrWait() {
  unknown88 = 0x11;
  DrCalcTexStreamMan *man = DrCalcTexStreamMan::get();
  man->unknown2488 += unknown84;
  unknowna8++;
  if (unknowna8 > 0x3b) {
    unknowna8 = 0;
    unknown1e0 = &DrCalcStmListObj::texstm_checkTexStm;
    return 1;
  }
  return 0;
}

bool DrCalcStmListObj::texstm_defupdate() {
  unknown88 = 0x13;
  if (unknownc8 != 0) {
    unknown8c = 0;
    unknown8e = 0;
  }
  if (!(unknown80 & 0x10)) {
    unknown1e0 = &DrCalcStmListObj::texstm_checkTexStm;
  }
  return 0;
}

bool DrCalcStmListObj::OnFileEvent(EventFileTh *event) {
  if (event->type != EventFileTh::TYPE_UNKNOWN_2) {
    unknown40 = nullptr;
    unknown80 = (unknown80 & ~0x0c000000u) | 0x08000000;
    return 0;
  }
  if (unknown40 != event->unknown08) {
    return 0;
  }
  unknown80 &= ~0x04000000u;
  unknown40 = nullptr;
  return 1;
}

bool DrCalcStmListObj::texstm_defHeightWait() {
  unknown88 = 0xc;
  unknown8c = 0;
  unknown8e = 0;
  DrCalcTexStreamMan *man = DrCalcTexStreamMan::get();
  if (man->unknown2490 > 1) {
    man->unknown2490 = 2;
  }
  unknown58++;
  if (unknown58 > 1) {
    unknown58 = 3;
    man->releaseFreeObj(unknown48);
  }
  if (!(unknown80 & 0x4000000) && unknown58 > 1) {
    unknown58 = 0;
    unknown28[unknown5a]->unknown24 &= ~0xa4u;
    unknown28[unknown5a]->unknown24 |= 0x310;
    unknown1e0 = &DrCalcStmListObj::texstm_defMidTexUpdate;
    unknown90 = 0;
    return 1;
  }
  return 0;
}

void DrCalcStmListObj::apiUpdate() {
  if (unknown80 & 0x10000) {
    return;
  }
  if (!isResTex()) {
    if (!(unknown80 & 0x40)) {
      return;
    }
    unknown80 &= ~0x40u;
    unknownb0.texRelease();
    return;
  }
  if (unknown80 & 0x40) {
    if (!isResChange()) {
      return;
    }
    for (u32 index = unknown7a, i = 0; index < unknown7c; index++, i++) {
      const unknown035 &res = unknown30[DrMan::s_nDblStockIdx][index];
      if (res.unknown10 & 1) {
        if (!(res.unknown10 & 2)) {
          if (res.unknown10 & 4) {
            if (!(res.unknown10 & 8)) {
              grlib::CGLibTexture::changeMixTextureImagePtrs(unknownb0.unknown00[i], res.unknown00, res.unknown0c, res.unknown08 - res.unknown0c);
            } else {
              unknownb0.unknown00[i].delayRelease();
              grlib::CGLibTexture::createMixTextureImagePtrs(unknownb0.unknown00[i], res.unknown00, res.unknown0c, res.unknown08 - res.unknown0c, false, nullptr, false);
            }
            continue;
          }
          grlib::CGLibTexture::changeTextureImagePtrs(unknownb0.unknown00[i], res.unknown00, res.unknown08);
        } else {
          grlib::CGLibTexture::changeTextureImagePtrs(unknownb0.unknown00[i], res.unknown00 + res.unknown0c, res.unknown08 - res.unknown0c);
        }
      }
    }
    return;
  }
  for (u32 index = unknown7a, i = 0; index < unknown7c; index++, i++) {
    const unknown035 &res = unknown30[DrMan::s_nDblStockIdx][index];
    if (!(res.unknown10 & 2)) {
      if (res.unknown10 & 4) {
        grlib::CGLibTexture::createMixTextureImagePtrs(unknownb0.unknown00[i], res.unknown00, res.unknown0c, res.unknown08 - res.unknown0c, false, nullptr, false);
        continue;
      }
      grlib::CGLibTexture::createTextureImagePtrs(unknownb0.unknown00[i], res.unknown00, res.unknown08, false, nullptr, false);
    } else {
      grlib::CGLibTexture::createTextureImagePtrs(unknownb0.unknown00[i], res.unknown00 + res.unknown0c, res.unknown08 - res.unknown0c, false, nullptr, false);
    }
  }
  unknown80 |= 0x40;
}

} // namespace ml
