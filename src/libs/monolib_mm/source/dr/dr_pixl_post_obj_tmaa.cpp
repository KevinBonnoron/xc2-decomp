#include "dr/dr_pixl_post_obj_tmaa.h"

#include "dr/dr_man.h"
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
  unknown001(unknown20);
  unknown001(m_bloomTexture[0]);
  unknown001(unknown28);
  unknown001(m_bloomTexture[1]);
}

void DrPixlPostObjTMAA::update() {}

void DrPixlPostObjTMAA::debugRender() {}

grlib::CGLibTextureBuffer *DrPixlPostObjTMAA::getBloomTexture() { return m_bloomTexture[DrMan::s_nDblIdx]; }

} // namespace ml
