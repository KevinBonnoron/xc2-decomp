#include "dr/dr_pixl_post_obj_tmaa.h"

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

void DrPixlPostObjTMAA::update() {}

void DrPixlPostObjTMAA::debugRender() {}

grlib::CGLibTextureBuffer *DrPixlPostObjTMAA::getBloomTexture() { return m_bloomTexture[DrMan::s_nDblIdx]; }

} // namespace ml
