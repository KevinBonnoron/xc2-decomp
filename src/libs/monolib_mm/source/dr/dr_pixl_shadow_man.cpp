#include "dr/dr_pixl_shadow_man.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_format.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "dr/dr_pixl_shadow_obj_dir.h"

namespace ml {

// Inferred role: shadow texture sizes by quality level; original name unknown.
static const f32 unknown001[6] = {128.0f, 256.0f, 512.0f, 1024.0f, 1536.0f, 2048.0f};

f32 DrPixlShadowMan::getShadowTexSize(int index) {
  if (index >= 1 && index <= 6) {
    return unknown001[index - 1];
  }
  return 64.0f;
}

void DrPixlShadowMan::beforUpdate() {
  unknown8918 = nullptr;
  for (int i = 0; i < unknown8900; i++) {
    unknown0000[i]->update();
  }
}

void DrPixlShadowMan::afterUpdate() {
  if (unknown8918 != nullptr) {
    unknown8918->calcLgtMat();
  }
  for (int i = 0; i < unknown8900; i++) {
    unknown0000[i]->afterUpdate();
  }
}

bool DrPixlShadowMan::setAddObjPos(const mm::Vec3 &position, f32 value) {
  if (unknown8908->unknown120[unknown8908->unknown1c98]->unknown103e && unknown8918 != nullptr) {
    return unknown8918->setAddObjPos(position, value);
  }
  return false;
}

bool DrPixlShadowMan::setSptCalcPos(const mm::Vec3 &position, f32 value) {
  bool result = false;
  for (int i = 0; i < unknown8900; i++) {
    if (unknown0000[i]->unknown4c != 0) {
      result |= unknown0000[i]->setSptCalcPos(position, value);
    }
  }
  return result;
}

MdoShdPxlWrkTex *DrPixlShadowMan::createShdTexWrk(int index, int type) {
  f32 size = getShadowTexSize(index);
  MdoShdPxlWrkTex *freeWork = nullptr;
  for (int i = 0; i < 16; i++) {
    MdoShdPxlWrkTex *work = &unknown0800[i];
    if (work->unknown804 == 0) {
      if (freeWork == nullptr) {
        freeWork = work;
      }
    } else if (work->unknown808 == type && work->unknown800 == size) {
      work->unknown804++;
      return work;
    }
  }

  if (freeWork != nullptr) {
    if (type == 1) {
      DrMan::getIns();
    }
    freeWork->setTextureInfo(size, size, DrPixlFormat::s_ShadowFormat, false, 0);
    freeWork->unknown800 = size;
    freeWork->unknown808 = type;
    freeWork->unknown80a = index;
    freeWork->unknown804 = 1;
  }
  return freeWork;
}

void DrPixlShadowMan::releaseTexWorkOne(MdoShdPxlWrkTex *work) {
  if (work->unknown804 != 0) {
    work->unknown804--;
    if (work->unknown804 == 0) {
      work->release();
      work->unknown808 = 0;
      work->unknown80a = 0;
      work->unknown800 = 0.0f;
      work->unknown804 = 0;
    }
  }
}

void DrPixlShadowMan::releaseTexWork() {
  for (int i = 0; i < 16; i++) {
    if (unknown0800[i].unknown804 != 0) {
      unknown0800[i].release();
    }
  }
}

void DrPixlShadowMan::releaseShadow(DrPixlShadowObj *shadow) {
  for (int i = 0; i < unknown8900; i++) {
    if (unknown0000[i] == shadow) {
      releaseTexWorkOne(shadow->unknown40);
      delete shadow;
      for (int j = i + 1; j < unknown8900; j++) {
        unknown0000[j - 1] = unknown0000[j];
      }
      unknown8900--;
      return;
    }
  }
}

void DrPixlShadowMan::setAddShadowObj(DrPixlShadowObjDir *shadow) { unknown8918 = shadow; }

} // namespace ml
