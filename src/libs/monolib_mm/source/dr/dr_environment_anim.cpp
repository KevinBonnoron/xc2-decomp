#include "dr/dr_environment_anim.h"

#include "dr/dr_fog_obj_gbl.h"
#include "dr/dr_light_obj.h"

namespace ml {

DrEnvironmentAnim::DrEnvironmentAnim() {
  unknown30 = nullptr;
  unknown28 = 0;
}

u32 DrEnvironmentAnim::getAnimWork(const u8 *data, u32 offset) {
  if (offset != 0) {
    return *reinterpret_cast<const u32 *>(data + offset) * 4;
  }
  return 0;
}

f32 DrEnvironmentAnim::setupAnim(void *frames, const u8 *data, u32 offset) {
  const u32 *header = reinterpret_cast<const u32 *>(data + offset);
  unknown30 = static_cast<f32 *>(frames);
  unknown00 = reinterpret_cast<const unknown001 *>(data + header[1]);
  unknown08 = data + header[3];
  unknown10 = reinterpret_cast<const unknown086 *>(data + header[5]);
  unknown18 = reinterpret_cast<const unknown087 *>(data + header[7]);
  unknown20 = data + header[9];
  unknown28 = static_cast<int>(header[0]);
  f32 maxFrame = 0.0f;
  for (int i = 0; i < unknown28; i++) {
    if (maxFrame < unknown00[i].unknown0c) {
      maxFrame = unknown00[i].unknown0c;
    }
  }
  return maxFrame;
}

void DrEnvironmentAnim::changeMemAnim(const u8 *data, u32 offset) {
  const u32 *header = reinterpret_cast<const u32 *>(data + offset);
  unknown00 = reinterpret_cast<const unknown001 *>(data + header[1]);
  unknown08 = data + header[3];
  unknown10 = reinterpret_cast<const unknown086 *>(data + header[5]);
  unknown18 = reinterpret_cast<const unknown087 *>(data + header[7]);
  unknown20 = data + header[9];
}

void DrEnvironmentAnim::setFrame(f32 frame) {
  for (int i = 0; i < unknown28; i++) {
    unknown30[i] = unknown00[i].unknown0c < frame ? unknown00[i].unknown0c : frame;
  }
}

void DrEnvironmentAnim::calcFrameUpdate(const LgtObjData *obj, f32 frame) {
  u64 index = obj->unknown28;
  f32 *frames = unknown30;
  const unknown001 *range = &unknown00[index];
  f32 current = frames[index] + frame;
  frames[index] = current;
  if (current > range->unknown0c) {
    frames[index] = range->unknown0c - current + range->unknown08;
  }
}

void DrEnvironmentAnim::calcFogFrameUpdate(const LgtGlbFogObj *obj, f32 frame) {
  u64 index = obj->unknown44;
  f32 *frames = unknown30;
  const unknown001 *range = &unknown00[index];
  f32 current = frames[index] + frame;
  frames[index] = current;
  if (current > range->unknown0c) {
    frames[index] = range->unknown0c - current + range->unknown08;
  }
}

void DrEnvironmentAnim::setupAnmVal(const f32 *values) {
  unknown60[2] = values[0];
  unknown60[1] = values[1];
  unknown60[0] = values[2];
}

void DrEnvironmentAnim::envlgt_amb_color_R(const LgtAnimInf *inf, f32 frame) { unknown38.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_amb_color_G(const LgtAnimInf *inf, f32 frame) { unknown38.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_amb_color_B(const LgtAnimInf *inf, f32 frame) { unknown38.b = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_amb_color_Intensity(const LgtAnimInf *inf, f32 frame) { unknown5c = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_amb_non(const LgtAnimInf *inf, f32 frame) {}

inline f32 DrEnvironmentAnim::getHermiteAttr(const LgtAnimInf *inf, f32 frame) {
  if (inf->unknown04 >= frame) {
    return unknown10[inf->unknown00].unknown08;
  }
  if (inf->unknown08 <= frame) {
    return unknown10[inf->unknown00 + inf->unknown0e - 1].unknown08;
  }
  const unknown086 *key = &unknown10[inf->unknown00 + 1];
  for (int i = 1; i < inf->unknown0e; i++, key++) {
    f32 keyFrame = key->unknown0c;
    if (frame < keyFrame) {
      const unknown086 *prev = key - 1;
      f32 prevFrame = prev->unknown0c;
      f32 length = keyFrame - prevFrame;
      f32 t = (frame - prevFrame) / length;
      f32 t2 = t * t;
      f32 t3 = t * t2;
      f32 h00 = 2.0f * t3 - 3.0f * t2 + 1.0f;
      f32 h10 = t3 - 2.0f * t2 + t;
      f32 h01 = 3.0f * t2 - 2.0f * t3;
      f32 h11 = t3 - t2;
      return prev->unknown08 * h00 + prev->unknown00 * h10 + key->unknown08 * h01 + key->unknown04 * h11;
    }
  }
  return 0.0f;
}

void DrEnvironmentAnim::envlgt_dir_color_R(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) { unknown38.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_dir_color_G(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) { unknown38.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_dir_color_B(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) { unknown38.b = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_dir_color_Intensity(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) { unknown5c = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_dir_spe_Intensity(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_dir_non(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_dir_texonoff(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_dir_texofsX(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_dir_texofsY(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_dir_size(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_dir_rotz(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) { unknown60[2] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_dir_roty(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) { unknown60[1] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_dir_rotx(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) { unknown60[0] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_color_R(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { unknown38.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_color_G(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { unknown38.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_color_B(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { unknown38.b = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_color_Intensity(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { unknown5c = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_spe_Intensity(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { light->unknownb0 = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_non(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_pnt_texonoff(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_pnt_texofsX(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_pnt_texofsY(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_pnt_size(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { light->m_size = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_rotz(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { unknown60[2] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_roty(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { unknown60[1] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_rotx(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { unknown60[0] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_color_R(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { unknown38.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_color_G(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { unknown38.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_color_B(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { unknown38.b = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_color_Intensity(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { unknown5c = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_spe_Intensity(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { light->unknownd4 = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_angle(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { light->unknownbc = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_texonoff(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_spt_texofsX(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_spt_texofsY(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_spt_size(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { light->m_size = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_rotz(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { unknown60[2] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_roty(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { unknown60[1] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_rotx(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { unknown60[0] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_trans_posx(const LgtAnimInf *inf, f32 frame) { unknown60[0] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_trans_posy(const LgtAnimInf *inf, f32 frame) { unknown60[1] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_trans_posz(const LgtAnimInf *inf, f32 frame) { unknown60[2] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_R(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { unknown38.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_G(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { unknown38.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_B(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { unknown38.b = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_sideR(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { unknown44.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_sideG(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { unknown44.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_sideB(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { unknown44.b = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_near(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { fog->unknown44 = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_far(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { fog->unknown48 = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_str(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { fog->unknown4c = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_pow(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { fog->unknown54 = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_sunR(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { unknown50.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_sunG(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { unknown50.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_sunB(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { unknown50.b = getHermiteAttr(inf, frame); }

u16 DrEnvironmentAnim::getBitAttr(const LgtAnimInf *inf, f32 frame) {
  if (inf->unknown04 >= frame) {
    return unknown18[inf->unknown00].value;
  }
  if (inf->unknown08 <= frame) {
    return unknown18[inf->unknown00 + inf->unknown0e - 1].value;
  }
  const unknown087 *key = &unknown18[inf->unknown00 + 1];
  for (int i = 1; i < inf->unknown0e; i++, key++) {
    f32 keyFrame = key->frame;
    if (frame < keyFrame) {
      return key[-1].value;
    }
  }
  return 0;
}

} // namespace ml
