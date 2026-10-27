#include "dr/dr_pixl_post_obj_motion_blur2.h"

#include "dr/dr_pixl_render_target.h"
#include "grlib/cglib_vtx_vertex.h"

namespace ml {

// Inferred role: deletes an object and clears the pointer; original name unknown.
template <typename T> inline void unknown001(T *&object) {
  T *deleted = object;
  if (deleted != nullptr) {
    delete deleted;
    object = nullptr;
  }
}

DrPixlPostObjMotionBlur2::~DrPixlPostObjMotionBlur2() {
  unknown001(unknown50);
  unknown001(unknown58);
  unknown001(unknown28);
  unknown001(unknown30);
  unknown001(unknown38);
  unknown001(unknown48);
  unknown001(unknown40);
  unknown001(unknown20);
}

void DrPixlPostObjMotionBlur2::resetColorBuff() { calcBludBuffColorBuff(); }

void DrPixlPostObjMotionBlur2::update() {}

void DrPixlPostObjMotionBlur2::releaseColorBuff() {
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown20->releaseTexture();
  unknown38->releaseTexture();
  unknown40->releaseTexture();
  unknown48->releaseTexture();
}

} // namespace ml
