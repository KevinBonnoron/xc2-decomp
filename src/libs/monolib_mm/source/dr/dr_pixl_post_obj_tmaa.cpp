#include "dr/dr_pixl_post_obj_tmaa.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "grlib/cglib_render_target.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {

// Inferred role: deletes an object and clears the pointer; original name unknown.
template <typename T> inline void unknown001(T *&object) {
  T *deleted = object;
  if (deleted != nullptr) {
    delete deleted;
    object = nullptr;
  }
}

DrPixlPostObjTMAA::DrPixlPostObjTMAA(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan) {
  unknown18 = 0;
  for (int i = 0; i < 2; i++) {
    unknown20[i] = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
    m_bloomTexture[i] = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  }
  unknown18 |= 1;
}

DrPixlPostObjTMAA::~DrPixlPostObjTMAA() {
  unknown001(unknown20[0]);
  unknown001(m_bloomTexture[0]);
  unknown001(unknown20[1]);
  unknown001(m_bloomTexture[1]);
}

void DrPixlPostObjTMAA::releaseColorBuff() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (postParm->unknownfe4 == 3) {
    unknown20[0]->releaseTexture();
    m_bloomTexture[0]->releaseTexture();
    unknown20[1]->releaseTexture();
    m_bloomTexture[1]->releaseTexture();
  } else {
    u32 index = DrMan::s_nDblIdx;
    unknown20[index]->releaseTexture();
    m_bloomTexture[index]->releaseTexture();
  }
}

void DrPixlPostObjTMAA::render() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (postParm->getTMAAOn()) {
    if ((unknown18 & 2) != 0) {
      for (s32 i = 0; i < 2; i++) {
        unknown20[i]->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
        m_bloomTexture[i]->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
      }
      unknown18 &= ~2;
    }
    if (postParm->unknown158) {
      unknown18 |= 1;
      unknown00->unknown120[unknown00->unknown1c98]->unknown158 = false;
    }
    if ((unknown18 & 1) != 0) {
      unknown18 &= ~4;
    } else {
      unknown18 |= 4;
    }
    renderTMAA();
    if ((unknown18 & 1) != 0) {
      unknown18 &= ~1;
    }
  }
}

void DrPixlPostObjTMAA::renderSharpness() {
  if (DrMan::getIns()->unknown1c60 == 0) {
    if ((unknown18 & 4) != 0) {
      renderSharpnessImpl(SHARPNESS_TYPE_UNKNOWN_1);
    }
    renderSharpnessImpl(SHARPNESS_TYPE_UNKNOWN_2);
  } else {
    renderSharpnessImpl(SHARPNESS_TYPE_UNKNOWN_4);
  }
}

void DrPixlPostObjTMAA::update() {}

void DrPixlPostObjTMAA::debugRender() {}

DrPixlRenderTarget *DrPixlPostObjTMAA::getBloomTexture() { return m_bloomTexture[DrMan::s_nDblIdx]; }

} // namespace ml
