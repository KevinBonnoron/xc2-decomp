#include "dr/dr_irr_vol_man.h"

#include "bin/bin_binary_resolver.h"
#include "dr/dr_irr_vol_cascade.h"
#include "dr/dr_irr_vol_sector.h"
#include "grlib/cglib_texture_buffer.h"
#include "ml/ml_mem.h"
#include "mm_math/mm_aabb.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrIrrVolMan::DrIrrVolMan(DrMan *drMan)
    : unknown00(drMan), unknown08(nullptr), unknown98(nullptr), unknown0a0(MlMem::getProductMem()), unknown0b0(0.0f), unknown0b4(0), unknown1c8(true), unknown1c9(false) {
  mm::Vec3 pos = mm::Vec3::zero;
  unknown190 = pos;
  unknown1b0 = 1.0f;
  unknown1b8 = 0.0f;
  unknown1c0 = 2;
  unknown1a0 = unknown190;
  unknown1b4 = unknown1b0;
  unknown1bc = unknown1b8;
  unknown1c4 = unknown1c0;
}

DrIrrVolMan::~DrIrrVolMan() { release(); }

void DrIrrVolMan::release() {
  if (unknown08 == nullptr) {
    return;
  }
  for (u32 i = 0; i < unknown08->unknown20; i++) {
    if (unknown98[i] != nullptr) {
      delete unknown98[i];
      unknown98[i] = nullptr;
    }
  }
  if (unknown98 != nullptr) {
    delete[] unknown98;
    unknown98 = nullptr;
  }
  unknown08 = nullptr;
}

void DrIrrVolMan::create(void *data, const char *name) {
  unknown08 = static_cast<irrvol::SGlobalInfo *>(bin::BinaryResolver::resolve(data));
  unknown10 = name;
}

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
  const irrvol::SCascadeInfo &area = unknown08->unknown28[index];
  mm::Vec3 size = area.unknown00.max - area.unknown00.min;
  return static_cast<u32>(size.x / area.unknown24 + 0.5f) * static_cast<u32>(size.z / area.unknown24 + 0.5f);
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
