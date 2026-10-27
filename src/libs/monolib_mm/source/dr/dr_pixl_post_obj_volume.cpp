#include "dr/dr_pixl_post_obj_volume.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "grlib/cglib_render_target.h"

namespace ml {

// Inferred role: releases and deletes a render target; original name unknown.
inline void unknown001(grlib::CGLibRenderTarget *&target) {
  grlib::CGLibRenderTarget *renderTarget = target;
  if (renderTarget != nullptr) {
    renderTarget->releaseWork();
    delete renderTarget;
    target = nullptr;
  }
}

void DrPixlPostObjVolume::calculateSclDown() {
  if (unknown00->unknown120[unknown00->unknown1c98]->m_TMAAOn) {
    calculateSclDown_Temporal();
  } else {
    calculateSclDown_NonTemporal();
  }
}

DrPixlPostObjVolume::~DrPixlPostObjVolume() {
  unknown001(unknown18);
  unknown001(unknown20);
  unknown001(unknown28);
}

void DrPixlPostObjVolume::resetColorBuff() { calcColorBuff(); }

void DrPixlPostObjVolume::update() {}

void DrPixlPostObjVolume::releaseColorBuff() {
  if (unknown18 != nullptr) {
    unknown18->releaseTexture();
  }
  if (unknown20 != nullptr) {
    unknown20->releaseTexture();
  }
  unknown28->releaseTexture();
}

} // namespace ml
