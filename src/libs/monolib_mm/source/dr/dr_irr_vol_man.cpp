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

int DrIrrVolMan::getSectorMax(u32 index) const {
  const unknown036::unknown001 &area = unknown08->unknown28[index];
  f32 width = area.unknown10 - area.unknown00;
  f32 depth = area.unknown18 - area.unknown08;
  return static_cast<u32>(width / area.unknown24 + 0.5f) * static_cast<u32>(depth / area.unknown24 + 0.5f);
}

void DrIrrVolMan::update() {
  if (unknown08 != nullptr && unknown98 == nullptr) {
    createResources();
  }
  updateIrrVol(false);
}

void DrIrrVolMan::tail() {
  unknown1a0 = unknown190;
  unknown1b4 = unknown1b0;
  unknown1bc = unknown1b8;
  unknown1c4 = unknown1c0;
  unknown0b4 ^= 1;
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
