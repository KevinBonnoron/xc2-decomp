#include "dr/dr_fog_man.h"

#include <math.h>
#include <string.h>

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_draw_work_info.h"
#include "dr/dr_fog_obj.h"
#include "dr/dr_fog_obj_gbl.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_res_list.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrFogMan::DrFogMan(DrMan *man)
    : unknown00(man), unknown08(nullptr), unknown10(nullptr), unknown18(0.5f, 0.5f, 0.5f), unknown24(0.0f, 0.0f, 0.0f), unknown30(0.0f, 0.0f, 0.0f), unknown3c(0.1f), unknown40(10000.0f),
      unknown44(1.0f), unknown48(1.0f), unknown4c(1.0f), unknown50(1.0f), unknown54(1.0f), unknown58(0.0f), unknown5c(1.0f), m_fogOn(false), unknownd1(true) {}

DrFogMan::~DrFogMan() { releaseAll(); }

void DrFogMan::releaseAll() {
  DrFogObj *fog = unknown08;
  while (fog != nullptr) {
    DrFogObj *next = fog->unknown10;
    delete fog;
    fog = next;
  }
  unknown08 = nullptr;
  unknown10 = nullptr;
}

void DrFogMan::update() {
  m_fogOn = false;
  unknown18.r = 0.0f;
  unknown18.g = 0.0f;
  unknown18.b = 0.0f;
  unknown24.r = 0.0f;
  unknown24.g = 0.0f;
  unknown24.b = 0.0f;
  unknown30.r = 0.0f;
  unknown30.g = 0.0f;
  unknown30.b = 0.0f;
  unknown3c = 10000.0f;
  unknown40 = 1000000.0f;
  unknown44 = 1.0f;
  unknown48 = 1.0f;
  unknown4c = 1.0f;
  unknown50 = 1.0f;
  unknown54 = 1.0f;
  unknown58 = 0.0f;
  unknown5c = 1.0f;
  DrFogObj *fog = unknown08;
  if (fog != nullptr) {
    bool isFirst = true;
    do {
      fog->update();
      if (isFirst) {
        unknown18 = fog->unknown20;
        unknown24 = fog->unknown2c;
        unknown30 = fog->unknown38;
        unknown3c = fog->unknown44;
        unknown40 = fog->unknown48;
        unknown44 = fog->unknown4c;
        unknown48 = fog->unknown50;
        unknown4c = fog->unknown54;
        unknown50 = fog->unknown58;
        unknown54 = fog->unknown5c;
        unknown58 = fog->unknown60;
        unknown5c = fog->unknown64;
      }
      fog = fog->unknown10;
      isFirst = false;
    } while (fog != nullptr);
    m_fogOn = true;
  }
}

void DrFogMan::updateGbl() { update(); }

void DrFogMan::calcTbl() {
  const mm::Mat44 &view = unknown00->unknown580->unknown10->unknown40;
  DrLightMan *lightMan = unknown00->unknown588;
  f32 gamma = unknown00->unknown78->unknown00;
  f32 power = DrMan::isFogSRGB() ? 1.0f : gamma;
  mm::Vec3 up(view.rows[0][0] * 0.0f + view.rows[1][0] + view.rows[2][0] * 0.0f,
              view.rows[0][1] * 0.0f + view.rows[1][1] + view.rows[2][1] * 0.0f,
              view.rows[0][2] * 0.0f + view.rows[1][2] + view.rows[2][2] * 0.0f);
  up.unknown001();
  if (unknown00->unknown1d71) {
    unknown18.r = 0.0f;
    unknown18.g = 0.0f;
    unknown18.b = 0.0f;
    unknown24.r = 0.0f;
    unknown24.g = 0.0f;
    unknown24.b = 0.0f;
    unknown30.r = 0.0f;
    unknown30.g = 0.0f;
    unknown30.b = 0.0f;
    unknown3c = 10000.0f;
    unknown40 = 1000000.0f;
    unknown44 = 1.0f;
    unknown48 = 1.0f;
    unknown4c = 1.0f;
    unknown50 = 1.0f;
    unknown54 = 1.0f;
    unknown58 = 0.0f;
    unknown5c = 1.0f;
    m_fogOn = false;
  }
  unknown60[0] = up.x;
  unknown60[1] = up.y;
  unknown60[2] = up.z;
  unknown60[3] = unknown48;
  unknown60[4] = lightMan->unknown140.r;
  unknown60[5] = lightMan->unknown140.g;
  unknown60[6] = lightMan->unknown140.b;
  unknown60[7] = 0.0f;
  unknown60[8] = powf(unknown18.r, power);
  unknown60[9] = powf(unknown18.g, power);
  unknown60[10] = powf(unknown18.b, power);
  unknown60[11] = 0.0f;
  unknown60[12] = powf(unknown24.r, power);
  unknown60[13] = powf(unknown24.g, power);
  unknown60[14] = powf(unknown24.b, power);
  unknown60[15] = unknown50;
  unknown60[16] = powf(unknown30.r, power);
  unknown60[17] = powf(unknown30.g, power);
  unknown60[18] = powf(unknown30.b, power);
  unknown60[19] = unknown54;
  unknown60[20] = unknown3c;
  unknown60[21] = 1.0f / (unknown40 - unknown3c);
  unknown60[22] = unknown4c;
  unknown60[23] = unknown44;
  unknown60[24] = unknown30.r * unknown58;
  unknown60[25] = unknown58 * unknown30.g;
  unknown60[26] = unknown30.b * unknown58;
  unknown60[27] = unknown5c;
  memcpy(unknown00->unknown660[unknown00->unknown1c98].m_fogTbl, unknown60, sizeof(f32) * 27);
}

void DrFogMan::createGblFog() {
  DrFogObj *fog = new (unknown00->unknown10) DrFogObjGbl(unknown00);
  unknown100(unknown08, unknown10, fog);
}

void DrFogMan::releaseGblFog(DrFogObj *fog) {
  unknown004(unknown08, unknown10, fog);
  delete fog;
}

bool DrFogMan::isFogOn() const { return m_fogOn; }

DrFogObj::DrFogObj(DrMan *man)
    : unknown08(nullptr), unknown10(nullptr), unknown18(man), unknown20(0.5f, 0.5f, 0.5f), unknown2c(0.0f, 0.0f, 0.0f), unknown38(0.0f, 0.0f, 0.0f), unknown44(0.1f), unknown48(10000.0f),
      unknown4c(1.0f), unknown50(1.0f), unknown54(1.0f), unknown58(1.0f), unknown5c(1.0f), unknown60(0.0f), unknown64(1.0f) {}

DrFogObjGbl::DrFogObjGbl(DrMan *man) : DrFogObj(man) {}

DrFogObjGbl::~DrFogObjGbl() {}

void DrFogObjGbl::update() {}

} // namespace ml
