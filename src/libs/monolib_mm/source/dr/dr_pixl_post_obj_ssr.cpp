#include "dr/dr_pixl_post_obj_ssr.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"

namespace ml {

// Inferred role: deletes an object and clears the pointer; original name unknown.
template <typename T> inline void unknown001(T *&object) {
  T *deleted = object;
  if (deleted != nullptr) {
    delete deleted;
    object = nullptr;
  }
}

DrPixlPostObjSSR::~DrPixlPostObjSSR() {
  unknown001(m_reflectionTexture[0]);
  unknown001(m_reflectionTexture[1]);
  unknown001(unknown20);
  unknown001(unknown38);
}

void DrPixlPostObjSSR::releaseColorBuff() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
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

void DrPixlPostObjSSR::setClear() { unknown18 |= 1; }

grlib::CGLibTextureBuffer *DrPixlPostObjSSR::getReflectionTexture() const { return m_reflectionTexture[DrMan::s_nDblIdx]; }

} // namespace ml
