#include "dr/dr_pixl_post_obj_ssr.h"

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

DrPixlPostObjSSR::~DrPixlPostObjSSR() {
  unknown001(m_reflectionTexture[0]);
  unknown001(m_reflectionTexture[1]);
  unknown001(unknown20);
  unknown001(unknown38);
}

void DrPixlPostObjSSR::setClear() { unknown18 |= 1; }

grlib::CGLibTextureBuffer *DrPixlPostObjSSR::getReflectionTexture() const { return m_reflectionTexture[DrMan::s_nDblIdx]; }

} // namespace ml
