#include "dr/dr_pixl_shadow_obj_spt.h"

#include "dr/dr_light_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_shd_lgt_hybrid.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_dbl_uniform_block.h"

namespace ml {

DrPixlShadowObjSpt::DrPixlShadowObjSpt(DrMan *man) : DrPixlShadowObj(man, 1, 0) {
  m_parmTbl[3] = 1.0f;
  m_parmTbl[2] = 1.0f;
  m_parmTbl[1] = 1.0f;
  m_parmTbl[0] = 1.0f;
  unknown220[0] = 1.0f;
  unknown220[1] = 1.0f;
  unknown220[2] = -1.0f;
  unknown22c = {-1.0f, 4.0f};
}

DrPixlShadowObjSpt::~DrPixlShadowObjSpt() {
  unknown08.release();
  delete unknown190;
}

bool DrPixlShadowObjSpt::dispChk() { return (unknown50 & FLAG_UNKNOWN_1) != 0; }

bool DrPixlShadowObjSpt::clipChk(const mm::Vec3 &position, f32 value, bool flag) {
  if (unknown22c.y < value) {
    return false;
  }
  return unknown1a0.clipTest(position, value);
}

int DrPixlShadowObjSpt::clipTypeChk(const mm::Vec3 &position, f32 value) {
  if (unknown22c.y < value) {
    return 0;
  }
  return unknown1a0.clipTypeTest(position, value);
}

void DrPixlShadowObjSpt::renderLight() {}

void DrPixlShadowObjSpt::stockTile() {
  // The local places the load of unknown198 before the load of m_hybridLight, as the game does (0x7100867ce8); in one expression the
  // call target is loaded first (9 instructions).
  DrLightObjSpt *light = static_cast<DrLightObjSpt *>(unknown198);
  unknown178->unknown80->unknown18->m_hybridLight->stockSptList(light);
}

const f32 *DrPixlShadowObjSpt::getParmTbl() const { return m_parmTbl; }

} // namespace ml
