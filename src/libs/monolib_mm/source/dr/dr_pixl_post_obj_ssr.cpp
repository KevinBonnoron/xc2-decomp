#include "dr/dr_pixl_post_obj_ssr.h"

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

DrPixlPostObjSSR::DrPixlPostObjSSR(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan) {
  unknown18 = 0;
  unknown20 = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
  for (s32 i = 0; i < 2; i++) {
    m_reflectionTexture[i] = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
  }
  unknown38 = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
  unknown18 |= 3;
  resetColorBuff();
}

DrPixlPostObjSSR::~DrPixlPostObjSSR() {
  unknown001(m_reflectionTexture[0]);
  unknown001(m_reflectionTexture[1]);
  unknown001(unknown20);
  unknown001(unknown38);
}

void DrPixlPostObjSSR::releaseColorBuff() {
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  if (postParm->unknownfe4 == 3) {
    m_reflectionTexture[0]->releaseTexture();
    m_reflectionTexture[1]->releaseTexture();
  } else {
    m_reflectionTexture[DrMan::s_nDblIdx]->releaseTexture();
  }
  if (postParm->unknownfe4 == 2) {
    return;
  }
  unknown20->releaseTexture();
  unknown38->releaseTexture();
}

void DrPixlPostObjSSR::render() {
  if (!m_drMan->unknown120[m_drMan->unknown1c98]->getSSROn()) {
    unknown18 |= 2;
    return;
  }
  if ((unknown18 & 2) != 0) {
    unknown18 &= ~2;
    m_reflectionTexture[0]->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
    m_reflectionTexture[1]->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
  }
  if ((unknown18 & 1) != 0) {
    m_reflectionTexture[DrMan::s_nDblIdx]->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
    unknown18 &= ~1;
    return;
  }
  raymarch2();
  temporalSuperSampling2();
}

void DrPixlPostObjSSR::debugRender() {
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  if (postParm->unknown489) {
    DrPixlRenderTarget *target = m_reflectionTexture[DrMan::s_nDblIdx];
    s32 width = target->unknownbc >> postParm->unknownf78;
    s32 height = target->unknownc0 >> postParm->unknownf78;
    target->debugRender(0, 0, width, height, false, true, 1.0f, true);
    unknown20->debugRender(width + 1, 0, width, height, false, true, 1.0f, true);
    unknown38->debugRender(0, height + 1, width, height, false, true, 1.0f, true);
  }
}

void DrPixlPostObjSSR::setClear() { unknown18 |= 1; }

grlib::CGLibTextureBuffer *DrPixlPostObjSSR::getReflectionTexture() const { return m_reflectionTexture[DrMan::s_nDblIdx]; }

} // namespace ml
