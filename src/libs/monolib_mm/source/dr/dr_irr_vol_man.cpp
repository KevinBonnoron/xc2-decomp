#include "dr/dr_irr_vol_man.h"

#include "dr/dr_irr_vol_cascade.h"
#include "grlib/cglib_texture_buffer.h"
#include "mm_math/mm_aabb.h"

namespace ml {

bool DrIrrVolMan::isValid() const {
  if (unknown08 == nullptr) {
    return false;
  }
  return unknown98 != nullptr;
}

void DrIrrVolMan::getVolumeArea(u32 cascade, mm::Aabb &area) const {
  irrvol::DrIrrVolCascade *irrVolCascade = unknown98[cascade];
  area = irrVolCascade->unknown560[irrVolCascade->unknown5e0];
}

void DrIrrVolMan::debugRender() {}

grlib::CGLibTextureBuffer *DrIrrVolMan::getIrrVolTex(u32 cascade, u32 index) const {
  irrvol::DrIrrVolCascade *irrVolCascade = unknown98[cascade];
  return &irrVolCascade->unknown5e8[irrVolCascade->unknown5e0][index];
}

const mm::Vec3 &DrIrrVolMan::getIrrVolUVScale(u32 cascade) const { return unknown98[cascade]->unknown5d0; }

const mm::Vec3 &DrIrrVolMan::getUVPerPixl(u32 cascade) const { return unknown98[cascade]->unknown5b0; }

const mm::Vec3 &DrIrrVolMan::getIrrVolEyeOffset(u32 cascade) const { return unknown98[cascade]->unknown8e0; }

const mm::Vec3 &DrIrrVolMan::getIrrVolUVOffset(u32 cascade) const { return unknown98[cascade]->unknown8f0; }

} // namespace ml
