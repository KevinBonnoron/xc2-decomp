#include "dr/dr_pixl_shadow_obj.h"

namespace ml {

void DrPixlShadowObj::afterUpdate() {}

bool DrPixlShadowObj::dispChk() { return true; }

void DrPixlShadowObj::renderLight() {}

void DrPixlShadowObj::debugInfo() {}

void DrPixlShadowObj::stockTile() {}

void DrPixlShadowObj::update() {}

bool DrPixlShadowObj::clipChk(const mm::Vec3 &position, f32 value, bool flag) { return true; }

bool DrPixlShadowObj::clipTypeChk(const mm::Vec3 &position, f32 value) { return false; }

bool DrPixlShadowObj::setSptCalcPos(const mm::Vec3 &position, f32 value) { return true; }

void DrPixlShadowObj::releaseWork() { unknown08.release(); }

void DrPixlShadowObj::setInstSelMapShadow(bool value) {
  if (value) {
    unknown50 |= 4;
  } else {
    unknown50 &= ~4;
  }
}

} // namespace ml
