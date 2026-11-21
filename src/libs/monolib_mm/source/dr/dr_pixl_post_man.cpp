#include "dr/dr_pixl_post_man.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_format.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_mem_man.h"
#include "dr/dr_pixl_post_obj.h"
#include "dr/dr_pixl_post_obj_3d_lut.h"
#include "dr/dr_pixl_post_obj_bloom.h"
#include "dr/dr_pixl_post_obj_capture.h"
#include "dr/dr_pixl_post_obj_cube_map_ibl.h"
#include "dr/dr_pixl_post_obj_cube_map_multi_ibl.h"
#include "dr/dr_pixl_post_obj_depthof_field.h"
#include "dr/dr_pixl_post_obj_exp_stencil.h"
#include "dr/dr_pixl_post_obj_fx_aa.h"
#include "dr/dr_pixl_post_obj_glass_br.h"
#include "dr/dr_pixl_post_obj_histgram.h"
#include "dr/dr_pixl_post_obj_motion_blur.h"
#include "dr/dr_pixl_post_obj_motion_blur2.h"
#include "dr/dr_pixl_post_obj_rain_drop.h"
#include "dr/dr_pixl_post_obj_ssr.h"
#include "dr/dr_pixl_post_obj_tmaa.h"
#include "dr/dr_pixl_post_obj_tone_map.h"
#include "dr/dr_pixl_post_obj_tssao.h"
#include "dr/dr_pixl_post_obj_unbranch_to_depth.h"
#include "dr/dr_pixl_post_obj_volume.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_pixl_shadow_raytrace.h"
#include "dr/dr_pixl_sky_dome.h"
#include "dr/dr_pixl_toon_grad.h"
#include "dr/dr_res_use_query_obj.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrPixlPostMan::~DrPixlPostMan() {
  if (unknownf0 != nullptr) {
    delete unknownf0;
    unknownf0 = nullptr;
  }
  if (unknown88 != nullptr) {
    delete unknown88;
    unknown88 = nullptr;
  }
  if (unknown80 != nullptr) {
    delete unknown80;
    unknown80 = nullptr;
  }
  unknown120(unknownc0[0]);
  unknown120(unknownc0[1]);
  unknown120(unknowne0);
  unknown120(unknownd0);
  unknown120(unknownd8);
  unknown120(unknowne8);
  if (unknown98 != nullptr) {
    delete unknown98;
    unknown98 = nullptr;
  }
  if (unknown90 != nullptr) {
    delete unknown90;
    unknown90 = nullptr;
  }
  if (unknowna0 != nullptr) {
    delete unknowna0;
    unknowna0 = nullptr;
  }
  if (unknown38 != nullptr) {
    delete unknown38;
    unknown38 = nullptr;
  }
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  if (unknown20 != nullptr) {
    delete unknown20;
    unknown20 = nullptr;
  }
  if (unknown28 != nullptr) {
    delete unknown28;
    unknown28 = nullptr;
  }
  if (unknown30 != nullptr) {
    delete unknown30;
    unknown30 = nullptr;
  }
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
  if (unknown58 != nullptr) {
    delete unknown58;
    unknown58 = nullptr;
  }
  if (unknown40 != nullptr) {
    delete unknown40;
    unknown40 = nullptr;
  }
  if (unknown48 != nullptr) {
    delete unknown48;
    unknown48 = nullptr;
  }
  if (unknown60 != nullptr) {
    delete unknown60;
    unknown60 = nullptr;
  }
  if (unknown68 != nullptr) {
    delete unknown68;
    unknown68 = nullptr;
  }
  if (unknown70 != nullptr) {
    delete unknown70;
    unknown70 = nullptr;
  }
  if (unknown78 != nullptr) {
    delete unknown78;
    unknown78 = nullptr;
  }
  if (unknowna8 != nullptr) {
    delete unknowna8;
    unknowna8 = nullptr;
  }
  if (unknownb0 != nullptr) {
    delete unknownb0;
    unknownb0 = nullptr;
  }
  if (unknownb8 != nullptr) {
    delete unknownb8;
    unknownb8 = nullptr;
  }
}
void DrPixlPostMan::setupDepthBuff() {
  f32 width = static_cast<f32>(unknown00->unknown5b8->unknown18);
  f32 height = static_cast<f32>(unknown00->unknown5b8->unknown1c);
  f32 halfWidth = width * 0.5f;
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  f32 halfHeight = height * 0.5f;
  if (postParm->unknownfe4 == 3) {
    if (unknownc0[0] != nullptr) {
      unknownc0[0]->setTextureInfo(halfWidth, halfHeight, DrPixlFormat::s_DepthBufferFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0f4[0]);
    }
    if (unknownc0[1] != nullptr) {
      unknownc0[1]->setTextureInfo(halfWidth, halfHeight, DrPixlFormat::s_DepthBufferFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0f4[1]);
    }
  } else {
    // The game indexes the target array with the signed index (ldrsw at 0x710084db70) and the memory area table with its zero extension
    // (and x23, x9, #0xffffffff at 0x710084db98); a signed index on both gives a different code.
    s32 index = DrMan::s_nDblIdx;
    if (unknownc0[index] != nullptr) {
      unknownc0[index]->setTextureInfo(
          halfWidth, halfHeight, DrPixlFormat::s_DepthBufferFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0f4[static_cast<u32>(index)]);
    }
    if (postParm->unknownfe4 == 2) {
      return;
    }
  }
  if (unknowne0 != nullptr) {
    unknowne0->setTextureInfo(width * 0.25f, height * 0.25f, DrPixlFormat::s_QuaterNormalFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown108);
  }
  if (unknownd0 != nullptr) {
    unknownd0->setTextureInfo(static_cast<f32>(unknown00->unknown5b8->unknown18) * 0.5f,
                              static_cast<f32>(unknown00->unknown5b8->unknown1c) * 0.5f,
                              DrPixlFormat::s_MrtFormat[5],
                              true,
                              (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown100);
  }
  if (unknowne8 != nullptr) {
    unknowne8->setTextureInfo(halfWidth, halfHeight, DrPixlFormat::s_DepthBufferFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown10c);
  }
}

void DrPixlPostMan::setReflection(f32 x, f32 y, f32 z, bool isHigh) {
  u32 flags = unknownf8;
  u32 mask = isHigh ? 0x60000 : 0x20000;
  unknownfc = x;
  unknown100 = y;
  unknown104 = z;
  unknownf8 = flags | mask;
}

void DrPixlPostMan::setDownDepth() { unknownf8 |= FLAG_UNKNOWN_19; }

void DrPixlPostMan::renderDeferred() {}

void DrPixlPostMan::renderDeferredLast() {
  if (unknown18 != nullptr) {
    unknown18->fastRender();
  }
  if (unknown60 != nullptr) {
    unknown60->render();
  }
}

DrPixlRenderTarget *DrPixlPostMan::getDownDepth() { return unknownc0[DrMan::s_nDblIdx]; }

void DrPixlPostMan::releaseColorBuff() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (unknown20 != nullptr) {
    unknown20->releaseColorBuff(false);
  }
  if (unknown70 != nullptr) {
    unknown70->releaseColorBuff();
  }
  if (unknown78 != nullptr) {
    unknown78->releaseColorBuff();
  }
  if (unknown68 != nullptr) {
    unknown68->releaseColorBuff();
  }
  if (unknown88 != nullptr) {
    unknown88->releaseColorBuff();
  }
  if (postParm->unknownfe4 == 3) {
    unknownf8 |= FLAG_UNKNOWN_22;
    if (unknownc0[0] != nullptr) {
      unknownc0[0]->releaseTexture();
    }
    if (unknownc0[1] != nullptr) {
      unknownc0[1]->releaseTexture();
    }
  } else {
    if (unknownc0[DrMan::s_nDblIdx] != nullptr) {
      unknownc0[DrMan::s_nDblIdx]->releaseTexture();
    }
    if (postParm->unknownfe4 == 2) {
      return;
    }
  }
  if (unknowne0 != nullptr) {
    unknowne0->releaseTexture();
  }
  if (unknowne8 != nullptr) {
    unknowne8->releaseTexture();
  }
  if (unknown30 != nullptr) {
    unknown30->releaseColorBuff();
  }
  if (unknown50 != nullptr) {
    unknown50->releaseColorBuff();
  }
  if (unknown58 != nullptr) {
    unknown58->releaseColorBuff();
  }
  if (unknown38 != nullptr) {
    unknown38->releaseColorBuff();
  }
  if (unknown28 != nullptr) {
    unknown28->releaseColorBuff();
  }
  if (unknowna0 != nullptr) {
    unknowna0->releaseColorBuff();
  }
  if (unknownd0 != nullptr) {
    unknownd0->releaseTexture();
  }
}

bool DrPixlPostMan::isCalcVolume() { return unknownf8 & FLAG_UNKNOWN_16; }

void DrPixlPostMan::update() {
  unknownf8 &= ~(FLAG_UNKNOWN_8 | FLAG_UNKNOWN_15 | FLAG_UNKNOWN_16 | FLAG_UNKNOWN_17 | FLAG_UNKNOWN_18 | FLAG_UNKNOWN_21);
  if (unknownf0 != nullptr) {
    unknownf0->update();
  }
  if (unknown90 != nullptr) {
    unknown90->update();
  }
  if (unknown20 != nullptr) {
    unknown20->update();
  }
  if (unknown18 != nullptr) {
    unknown18->update();
  }
  if (unknown30 != nullptr) {
    unknown30->update();
  }
  if (unknown50 != nullptr) {
    unknown50->update();
  }
  if (unknown58 != nullptr) {
    unknown58->update();
  }
  if (unknown60 != nullptr) {
    unknown60->update();
  }
  if (unknown78 != nullptr) {
    unknown78->update();
  }
  unknown00->unknown120[unknown00->unknown1c98]->update();
  if (unknowna0 != nullptr) {
    unknowna0->update();
  }
  if (unknowna8 != nullptr) {
    unknowna8->update();
  }
  if (unknownb0 != nullptr) {
    unknownb0->update();
  }
  if (unknown70 != nullptr) {
    unknown70->update();
  }
}

void DrPixlPostMan::setRefRactionMap() { unknownf8 |= FLAG_UNKNOWN_21; }

bool DrPixlPostMan::renderRefractionBegin() {
  if (!(unknownf8 & FLAG_UNKNOWN_21)) {
    return false;
  }
  if (unknownf0 != nullptr) {
    unknownf0->begin(unknown08->unknown7f8);
  }
  return true;
}

void DrPixlPostMan::renderRefractionEnd() {
  if (unknownf0 != nullptr) {
    unknownf0->end();
  }
}

void DrPixlPostMan::renderSkyLuminance() {
  if (unknown90 != nullptr) {
    unknown90->luminanceRender();
  }
}

void DrPixlPostMan::renderSkyDome() {
  if (unknown90 != nullptr) {
    unknown90->baseRender();
  }
}

void DrPixlPostMan::renderSkyGodRay() {
  if (unknown90 != nullptr) {
    unknown90->godRayRender();
  }
}

void DrPixlPostMan::renderRainDrop() {
  if (unknowna0 != nullptr) {
    unknowna0->render();
  }
}

void DrPixlPostMan::renderTMAA() {
  if (unknown00->unknown120[unknown00->unknown1c98]->m_TMAAOn) {
    unknown68->render();
  }
}

void DrPixlPostMan::renderDeferredFast_AfterTemporal() {
  if (unknown78 != nullptr) {
    unknown78->render_afterTemporal();
  }
}

void DrPixlPostMan::renderDeferredFast() {
  bool isTemporal = unknown00->isTemporalUPSToGlobalIBL() || unknown00->unknown120[unknown00->unknown1c98]->m_TMAAOn;
  if (getDownDepth() != nullptr) {
    renderDownDepth(true, isTemporal, true);
  }
  if (unknownb8 != nullptr) {
    unknownb8->render();
  }
  if (unknown80 != nullptr) {
    unknown80->render();
  }
  if (unknown78 != nullptr) {
    unknown78->render_beforeTemporal();
  }
  if (unknown88 != nullptr) {
    unknown88->render_beforeTemporal();
  }
  if (unknown70 != nullptr) {
    unknown70->render();
  }
}

void DrPixlPostMan::fastRender() {
  if (unknown40 != nullptr) {
    unknown40->render();
  }
  if (unknown48 != nullptr) {
    unknown48->render();
  }
  if (unknown98 != nullptr) {
    unknown98->render();
  }
}

void DrPixlPostMan::capRender() {
  if (unknownb0 != nullptr) {
    unknownb0->render();
  }
}

void DrPixlPostMan::setGlassBreak(bool isGlassBreak) {
  DrPixlPostObjGlassBr *glassBreak = unknowna8;
  if (glassBreak == nullptr) {
    if (isGlassBreak) {
      unknowna8 = new (unknown00->unknown0c) DrPixlPostObjGlassBr(unknown00, unknown08, this);
    }
  } else if ((glassBreak->unknown508 & DrPixlPostObjGlassBr::FLAG_UNKNOWN_3) == 0) {
    if (!isGlassBreak) {
      glassBreak->unknown508 |= DrPixlPostObjGlassBr::FLAG_UNKNOWN_2;
    }
  } else {
    delete glassBreak;
    unknowna8 = nullptr;
  }
}

void DrPixlPostMan::setCaputureMode(bool isCapture) {
  DrPixlPostObjCapture *capture = unknownb0;
  if (capture == nullptr) {
    if (isCapture) {
      unknownb0 = new (unknown00->unknown0c) DrPixlPostObjCapture(unknown00, unknown08, this);
    }
  } else if ((capture->unknown3e0 & DrPixlPostObjCapture::FLAG_UNKNOWN_3) == 0) {
    if (!isCapture) {
      capture->unknown3e0 |= DrPixlPostObjCapture::FLAG_UNKNOWN_2;
    }
  } else {
    delete capture;
    unknownb0 = nullptr;
  }
}

void DrPixlPostMan::setBloom(bool isBloom) { unknownf8 = !isBloom ? unknownf8 & ~(FLAG_UNKNOWN_2 | FLAG_UNKNOWN_3) : unknownf8 | (FLAG_UNKNOWN_2 | FLAG_UNKNOWN_3); }

void DrPixlPostMan::setSSAO(bool isSSAO) {
  if (isSSAO) {
    unknownf8 |= FLAG_UNKNOWN_4;
  } else if (unknownf8 & FLAG_UNKNOWN_4) {
    unknownf8 &= ~FLAG_UNKNOWN_4;
  }
}

void DrPixlPostMan::setBlur(bool isBlur) {
  if (isBlur) {
    unknownf8 |= FLAG_UNKNOWN_6 | FLAG_UNKNOWN_19;
    if (unknown58 == nullptr) {
      unknown58 = new (unknown00->unknown0c) DrPixlPostObjMotionBlur2(unknown00, unknown08, this);
    }
  } else if (unknownf8 & FLAG_UNKNOWN_6) {
    if (unknown50 != nullptr) {
      delete unknown50;
      unknown50 = nullptr;
    }
    if (unknown58 != nullptr) {
      delete unknown58;
      unknown58 = nullptr;
    }
    unknownf8 &= ~FLAG_UNKNOWN_6;
  }
}

void DrPixlPostMan::setDepthField(bool isDepthField) {
  if (isDepthField) {
    unknownf8 |= FLAG_UNKNOWN_5 | FLAG_UNKNOWN_19;
    if (unknown30 == nullptr) {
      unknown30 = new (unknown00->unknown0c) DrPixlPostObjDepthofField(unknown00, unknown08, this);
    }
  } else if (unknownf8 & FLAG_UNKNOWN_5) {
    unknownf8 &= ~FLAG_UNKNOWN_5;
    if (unknown30 != nullptr) {
      delete unknown30;
      unknown30 = nullptr;
    }
  }
}

DrPixlRenderTarget *DrPixlPostMan::getOldDownDepth() { return unknownc0[DrMan::s_nDblStockIdx]; }

void DrPixlPostMan::setToneMaping(bool isToneMaping) { unknownf8 = !isToneMaping ? unknownf8 & ~FLAG_UNKNOWN_1 : unknownf8 | FLAG_UNKNOWN_1; }

void DrPixlPostMan::setVolume(bool isVolume) { unknownf8 = !isVolume ? unknownf8 & ~FLAG_UNKNOWN_3 : unknownf8 | FLAG_UNKNOWN_3; }

void DrPixlPostMan::set3DLut(bool is3DLut) { unknownf8 = !is3DLut ? unknownf8 & ~FLAG_UNKNOWN_0 : unknownf8 | FLAG_UNKNOWN_0; }

void DrPixlPostMan::setSSAOAv(bool isSSAO) {
  if (isSSAO) {
    unknownf8 |= FLAG_UNKNOWN_4;
  } else if (unknownf8 & FLAG_UNKNOWN_4) {
    unknownf8 &= ~FLAG_UNKNOWN_4;
  }
}

void DrPixlPostMan::setVolumePos(const mm::Vec3 &pos) {
  if (unknown28 != nullptr) {
    unknown28->unknown30 = pos;
  }
}

void DrPixlPostMan::setDepthFieldParm(f32 distance, f32 range, f32 strength) {}

void DrPixlPostMan::setBlurParm(f32 strength, f32 sub) {}

bool DrPixlPostMan::isToneMaping() { return unknownf8 & FLAG_UNKNOWN_1; }

bool DrPixlPostMan::isBloom() { return unknownf8 & FLAG_UNKNOWN_2; }

bool DrPixlPostMan::isCalcBloom() { return unknownf8 & FLAG_UNKNOWN_15; }

bool DrPixlPostMan::is3DLut() { return unknownf8 & FLAG_UNKNOWN_0; }

bool DrPixlPostMan::isVolume() { return unknownf8 & FLAG_UNKNOWN_3; }

bool DrPixlPostMan::isBluer() { return unknownf8 & FLAG_UNKNOWN_6; }

bool DrPixlPostMan::isDepthField() { return unknownf8 & FLAG_UNKNOWN_5; }

bool DrPixlPostMan::isSSAO() { return unknownf8 & FLAG_UNKNOWN_4; }

bool DrPixlPostMan::isSSS() { return unknownf8 & FLAG_UNKNOWN_9; }

bool DrPixlPostMan::isReflection() { return unknownf8 & FLAG_UNKNOWN_7; }

bool DrPixlPostMan::isChgShader() { return unknownf8 & FLAG_UNKNOWN_8; }

bool DrPixlPostMan::isDepthDown() { return unknownf8 & FLAG_UNKNOWN_19; }

const grlib::CGLibTextureBuffer *DrPixlPostMan::getToonGradTex() const {
  if (unknown98 != nullptr) {
    return &unknown98->getGradTex();
  }
  return nullptr;
}

const grlib::CGLibTextureBuffer *DrPixlPostMan::getToonDarkGradTex() const {
  if (unknown98 != nullptr) {
    return &unknown98->getDarkGradTex();
  }
  return nullptr;
}

} // namespace ml
