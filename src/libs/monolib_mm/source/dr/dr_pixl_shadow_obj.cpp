#include "dr/dr_pixl_shadow_obj.h"

namespace ml {

void DrPixlShadowObj::afterUpdate() {}

bool DrPixlShadowObj::dispChk() { return true; }

void DrPixlShadowObj::renderLight() {}

void DrPixlShadowObj::debugInfo() {}

void DrPixlShadowObj::stockTile() {}

void DrPixlShadowObj::update() {}

bool DrPixlShadowObj::clipChk(const mm::Vec3 &position, f32 value, bool flag) { return true; }

int DrPixlShadowObj::clipTypeChk(const mm::Vec3 &position, f32 value) { return 0; }

bool DrPixlShadowObj::setSptCalcPos(const mm::Vec3 &position, f32 value) { return true; }

const f32 *DrPixlShadowObj::getParmTbl() const { return unknown60.rows[0]; }

void DrPixlShadowObj::createWork(DrLightObj *light, int index, MdoShdPxlWrkTex *work) {
  unknown40 = work;
  unknown4a = index;
  unknown198 = light;
  unknown08.release();
  if (unknown4c == 1) {
    unknown08.setup(0x50);
  } else {
    unknown08.setup(0x40);
  }
}

void DrPixlShadowObj::releaseWork() { unknown08.release(); }

void DrPixlShadowObj::setInstSelMapShadow(bool value) {
  if (value) {
    unknown50 |= 4;
  } else {
    unknown50 &= ~4;
  }
}

} // namespace ml
