#include "dr/dr_light_man.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_light_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_res_list.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"
#include "ml/critical_section.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {

namespace {

// Inferred role: appends every light of a request list to a light list and empties the request list; original name unknown.
void unknown022(DrLightObj *&first, DrLightObj *&last, DrLightObj **request) {
  DrLightObj *light = request[0];
  while (light != nullptr) {
    DrLightObj *next = light->unknown10;
    unknown100<DrLightObj>(first, last, light);
    light = next;
  }
  request[0] = nullptr;
  request[1] = nullptr;
}

} // namespace

void DrLightMan::render() {}

void DrLightMan::renderDir() {}

void DrLightMan::renderPnt() {}

void DrLightMan::renderSpt() {}

void DrLightMan::renderDebugDir() {}

void DrLightMan::stockBegin() {
  unknown1b8 = false;
  unknown1b9 = false;
  unknown168 = 0;
  unknowne0->unknown80->unknown18->stockBegin();
}

void DrLightMan::stockEnd() {
  updateAfterPnt();
  updateAfterSpt();
  unknowne0->unknown80->unknown18->stockEnd();
}

DrLightMan::~DrLightMan() { releaseAll(); }

void DrLightMan::releaseAll() {
  unknown2100(unknown000, unknown008);
  unknown2100(unknown010, unknown018);
  unknown2100(unknown020, unknown028);
  unknown2100(unknown030, unknown038);
  unknown2100(unknown040[0][0], unknown040[0][1]);
  unknown2100(unknown040[1][0], unknown040[1][1]);
  unknown2100(unknown060[0][0], unknown060[0][1]);
  unknown2100(unknown060[1][0], unknown060[1][1]);
  unknown2100(unknown080[0][0], unknown080[0][1]);
  unknown2100(unknown080[1][0], unknown080[1][1]);
  unknown2100(unknown0c0[0], unknown0c0[1]);
  unknown2100(unknown0a0[0][0], unknown0a0[0][1]);
  unknown2100(unknown0a0[1][0], unknown0a0[1][1]);
  unknown2100(unknown0d0[0], unknown0d0[1]);
  unknown100 = 0;
  unknown104 = 0;
  unknown108 = 0;
  unknown10c = 0;
  unknown0f0 = nullptr;
  unknown0f8 = nullptr;
}

void DrLightMan::renderDebugPnt() {
  DrShdLgtMan *shdLgtMan = unknowne0->unknown80->unknown18;
  DrAPGxType::setupCullingFront();
  DrAPGxType::setupDepthContl(1, 0, 3);
  for (DrLightObj *light = unknown020; light != nullptr; light = light->unknown10) {
    if (!light->isCullON()) {
      shdLgtMan->renderDebugPnt(static_cast<DrLightObjPnt *>(light));
    }
  }
}

void DrLightMan::renderDebugSpt() {
  DrShdLgtMan *shdLgtMan = unknowne0->unknown80->unknown18;
  for (DrLightObj *light = unknown030; light != nullptr; light = light->unknown10) {
    if (!light->isCullON()) {
      shdLgtMan->renderDebugSpt(static_cast<DrLightObjSpt *>(light));
    }
  }
}

void DrLightMan::debugRender() {
  renderDebugPnt();
  renderDebugSpt();
}

DrLightObjDir *DrLightMan::createDirLight() {
  CS lock(DrMan::getCriticalSection());
  DrLightObjDir *light = new (unknowne0->unknown10) DrLightObjDir(unknowne0->unknown78);
  ml::unknown100<DrLightObj>(unknown060[DrMan::s_nDblStockIdx][0], unknown060[DrMan::s_nDblStockIdx][1], light);
  unknown104++;
  return light;
}

void DrLightMan::releaseAmbLight(DrLightObjAmb *light) {
  CS lock(DrMan::getCriticalSection());
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblStockIdx;
  unknown100--;
  if (unknown100 < 0) {
    unknown100 = 0;
  }
}

void DrLightMan::releaseDirLight(DrLightObjDir *light) {
  CS lock(DrMan::getCriticalSection());
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblStockIdx;
  unknown104--;
  if (unknown104 < 0) {
    unknown104 = 0;
  }
}

void DrLightMan::releasePntLight(DrLightObjPnt *light) {
  CS lock(DrMan::getCriticalSection());
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblStockIdx;
  unknown108--;
  if (unknown108 < 0) {
    unknown108 = 0;
  }
}

void DrLightMan::releaseSptLight(DrLightObjSpt *light) {
  CS lock(DrMan::getCriticalSection());
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblStockIdx;
  unknown10c--;
  if (unknown10c < 0) {
    unknown10c = 0;
  }
}

void DrLightMan::releaseFastLight() {
  if (unknown0f0 != nullptr) {
    releaseAmbLight(unknown0f0);
    unknown0f0 = nullptr;
  }
  if (unknown0f8 != nullptr) {
    releaseDirLight(unknown0f8);
    unknown0f8 = nullptr;
  }
}

f32 DrLightMan::getSkyLuminance() const {
  DrPixlPostParm *parm = unknowne0->unknown120[unknowne0->unknown1c98];
  f32 second = parm->unknown46c;
  f32 first = parm->unknown468;
  f32 r = second * unknown12c.r + first * unknown120.r;
  f32 g = second * unknown12c.g + first * unknown120.g;
  f32 b = second * unknown12c.b + first * unknown120.b;
  return r * 0.299f + g * 0.587f + b * 0.114f;
}

void DrLightMan::releaseInstantPntLight(DrLightObjPnt *light) {
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblIdx;
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblStockIdx;
  unknown108--;
  if (unknown108 < 0) {
    unknown108 = 0;
  }
}

void DrLightMan::releaseInstantSptLight(DrLightObjSpt *light) {
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblIdx;
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblStockIdx;
  unknown10c--;
  if (unknown10c < 0) {
    unknown10c = 0;
  }
}

void DrLightMan::updateAmb() {
  int index = DrMan::s_nDblIdx;
  unknown022(unknown000, unknown008, unknown040[index]);
  unknown12c = mm::Col3(0.2f, 0.2f, 0.2f);
  bool isFirst = true;
  DrLightObj *light = unknown000;
  while (light != nullptr) {
    if (light->unknown1c & (DrLightObj::FLAG_UNKNOWN_16 << index)) {
      DrLightObj *next = light->unknown10;
      if (light == unknown0f0) {
        unknown0f0 = nullptr;
      }
      unknown004(unknown000, unknown008, light);
      delete light;
      light = next;
    } else {
      if (isFirst) {
        unknown12c = static_cast<DrLightObjAmb *>(light)->unknown30;
      }
      isFirst = false;
      light = light->unknown10;
    }
  }
}

void DrLightMan::updatePnt() { unknown022(unknown020, unknown028, unknown080[DrMan::s_nDblIdx]); }

void DrLightMan::updateSpt() { unknown022(unknown030, unknown038, unknown0a0[DrMan::s_nDblIdx]); }

} // namespace ml
