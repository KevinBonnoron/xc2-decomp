#include "dr/dr_pixl_post_obj_cube_map_multi_ibl.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_cube_map_mip_map.h"
#include "dr/dr_shd_cube_cap_filter.h"
#include "dr/dr_shd_lgt_global_ibl.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"
#include "mm_mtl/fixed_array.h"

// Spherical harmonics helpers of the unit (second order, 9 coefficients). The game keeps them in the namespace
// _cubemap_multi_ibl_ (_ZN19_cubemap_multi_ibl_5shMulEPff).
namespace _cubemap_multi_ibl_ {

void shMul(f32 *sh, f32 scale) {
  for (int i = 0; i < 9; i++) {
    sh[i] = sh[i] * scale;
  }
}

void shMulAdd(f32 *sh, const f32 *add, f32 scale) {
  for (u32 i = 0; i < 9; i++) {
    sh[i] += add[i] * scale;
  }
}

void shLerp(f32 *sh, const f32 *a, const f32 *b, f32 t) {
  f32 inverse = 1.0f - t;
  for (int i = 0; i < 9; i++) {
    sh[i] = inverse * a[i] + b[i] * t;
  }
}

} // namespace _cubemap_multi_ibl_

namespace ml {

DrPixlPostObjCubeMapMultiIBL::~DrPixlPostObjCubeMapMultiIBL() {
  if (unknown6e8 != nullptr) {
    delete unknown6e8;
    unknown6e8 = nullptr;
  }
  unknown678[0].release();
  unknown678[1].release();
  unknown6c8.release();
  unknown650.release();
  for (s32 i = 0; i < 2; i++) {
    if (unknown5c8[i] != nullptr) {
      delete unknown5c8[i];
      unknown5c8[i] = nullptr;
    }
  }
}

void DrPixlPostObjCubeMapMultiIBL::render() {
  for (mm::mtl::FixedQueue<DrRequetIBL, 30>::iterator it = unknown18.begin(); it != unknown18.end();) {
    u8 state = *(*it).unknown28;
    if (state == 0 || state == 2 || state == 3) {
      it = unknown18.erase(it);
    } else {
      ++it;
    }
  }
  if (unknown00->isIBLSkip() || !unknown00->unknown120[unknown00->unknown1c98]->unknown269) {
    return;
  }
  for (mm::mtl::FixedQueue<DrRequetIBL, 30>::iterator it = unknown18.begin(); it != unknown18.end(); ++it) {
    DrRequetIBL &request = *it;
    if (*request.unknown28 == 1 && request.getVersion() == 2) {
      relightCubeMap2(request);
      generateSH2(request);
      (*request.unknown28)++;
    }
  }
  unknown6d8 ^= 1;
  unknown00->unknown80->unknown18->unknown58->updateUniformBlock(unknown00->unknown1c98);
}

bool DrPixlPostObjCubeMapMultiIBL::requestIBL(DrRequetIBL &request) {
  if (!unknown00->unknown120[unknown00->unknown1c98]->unknown269 || unknown18.full()) {
    return false;
  }

  int count = 0;
  for (mm::mtl::FixedQueue<DrRequetIBL, 30>::iterator it = unknown18.begin(); it != unknown18.end(); ++it) {
    if ((*it).unknown20 == request.unknown20) {
      if (*(*it).unknown28 == 1) {
        return false;
      }
      if (++count == 4) {
        return false;
      }
    }
  }

  *request.unknown28 = 1;
  unknown18.push(request);
  return true;
}

void DrPixlPostObjCubeMapMultiIBL::cancelIBL(u64 id) {
  for (mm::mtl::FixedQueue<DrRequetIBL, 30>::iterator it = unknown18.begin(); it != unknown18.end(); ++it) {
    if ((*it).unknown20 == id) {
      *(*it).unknown28 = 3;
    }
  }
}

void DrPixlPostObjCubeMapMultiIBL::outputPremToDDS() {}

void DrPixlPostObjCubeMapMultiIBL::update() {}

void DrPixlPostObjCubeMapMultiIBL::debugRender() const {}

u32 DrPixlPostObjCubeMapMultiIBL::getPremMipCount() const { return m_premMipCount; }

} // namespace ml
