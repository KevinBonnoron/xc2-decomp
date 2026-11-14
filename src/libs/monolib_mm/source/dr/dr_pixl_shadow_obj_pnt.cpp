#include "dr/dr_pixl_shadow_obj_pnt.h"

#include "dr/dr_light_obj.h"
#include "dr/dr_mdo_shd_pxl_wrk_tex.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"

namespace ml {
class DrMan;

DrPixlShadowObjPnt::DrPixlShadowObjPnt(DrMan *man, int index) : DrPixlShadowObj(man, 2, index) {}

DrPixlShadowObjPnt::~DrPixlShadowObjPnt() {
  unknown08.release();
  delete unknown190;
}

void DrPixlShadowObjPnt::update() {
  DrLightObjPnt *light = static_cast<DrLightObjPnt *>(unknown198);
  unknown50 &= ~(FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1 | FLAG_UNKNOWN_3 | FLAG_UNKNOWN_4 | FLAG_UNKNOWN_5 | FLAG_UNKNOWN_6);
  getLightMatrix(unknown60, light->m_pos, light->m_pos + mm::Vec3(0.0f, 0.0f, 1.0f), mm::Vec3(0.0f, 1.0f, 0.0f));
  f32 offset = 0.5f / unknown40->unknown800 + 0.5f;
  unknown120.rows[0][0] = 0.5f;
  unknown120.rows[0][1] = 0.0f;
  unknown120.rows[0][2] = 0.0f;
  unknown120.rows[0][3] = 0.0f;
  unknown120.rows[1][0] = 0.0f;
  unknown120.rows[1][1] = -0.5f;
  unknown120.rows[1][2] = 0.0f;
  unknown120.rows[1][3] = 0.0f;
  unknown120.rows[2][0] = 0.0f;
  unknown120.rows[2][1] = 0.0f;
  unknown120.rows[2][2] = 0.0f;
  unknown120.rows[2][3] = 0.0f;
  unknown120.rows[3][0] = offset;
  unknown120.rows[3][1] = offset;
  unknown120.rows[3][2] = 0.0f;
  unknown120.rows[3][3] = 1.0f;
  unknowne0 = unknown60;
  unknowna0 = unknown60;
  unknown120 = unknowna0 * unknown120;
  unknown1a0.setSphereWork(light->m_pos, light->m_size, unknown48);
  if (unknown190 != nullptr) {
    unknown190->update();
  }
}

bool DrPixlShadowObjPnt::dispChk() { return !unknown198->isCullON(); }

bool DrPixlShadowObjPnt::clipChk(const mm::Vec3 &position, f32 value, bool flag) { return unknown1a0.clipTest(position, value); }

int DrPixlShadowObjPnt::clipTypeChk(const mm::Vec3 &position, f32 value) { return unknown1a0.clipTypeTest(position, value); }

} // namespace ml
